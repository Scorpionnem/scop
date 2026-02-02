/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshCache.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:02:29 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/02 12:19:37 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"

std::shared_ptr<Mesh>	MeshCache::gen()
{
	return (std::make_shared<Mesh>(_engine->getTextureCache()));
}

std::shared_ptr<Mesh>	MeshCache::get(const std::string &path)
{
	auto	[it, inserted] = _meshes.try_emplace(path);

	if (inserted)
	{
		std::shared_ptr<Mesh> shared = std::make_shared<Mesh>(_engine->getTextureCache());
		shared->load(path);
		shared->upload();

		it->second = shared;
		return (shared);
	}

	if (it->second.expired())
	{
		_meshes.erase(path);
		return (get(path));
	}
	return (std::shared_ptr<Mesh>(it->second));
}
