/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderCache.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:06:14 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/02 12:22:11 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"

std::shared_ptr<Shader>	ShaderCache::get(const std::string &path)
{
	auto	[it, inserted] = _shaders.try_emplace(path);

	if (inserted)
	{
		std::shared_ptr<Shader>	shared = std::make_shared<Shader>();
		shared->load(GL_VERTEX_SHADER , path + ".vs");
		shared->load(GL_FRAGMENT_SHADER , path + ".fs");
		shared->link();

		it->second = shared;
		return (shared);
	}

	if (it->second.expired())
	{
		_shaders.erase(path);
		return (get(path));
	}
	return (std::shared_ptr<Shader>(it->second));
}
