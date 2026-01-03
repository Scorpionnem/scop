/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshCache.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:02:02 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 12:02:03 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unordered_map>
#include <memory>
#include "Mesh.hpp"

class	Engine;

class	MeshCache
{
	public:
		MeshCache(Engine *engine) : _engine(engine) {}
		~MeshCache() {}

		std::shared_ptr<Mesh>	get(const std::string &path);
	private:
		Engine	*_engine;
		std::unordered_map<std::string, std::shared_ptr<Mesh>>	_meshes;
};
