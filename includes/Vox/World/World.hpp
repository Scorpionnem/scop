/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:52 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 21:15:25 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Chunk.hpp"
#include <unordered_map>
#include <memory>

struct World
{
	std::shared_ptr<Chunk>	getChunk(Vec3 pos, MeshCache &meshCache)
	{
		auto find = _chunks.find(pos.hash());

		if (find == _chunks.end())
		{
			std::shared_ptr<Chunk>	chunk = std::make_shared<Chunk>(pos);
			chunk->generate(meshCache);
			_chunks.insert(std::make_pair(pos.hash(), chunk));
			return (chunk);
		}
		return (find->second);
	}
	std::unordered_map<uint64_t, std::shared_ptr<Chunk>>	_chunks;
};
