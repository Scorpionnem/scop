/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:52 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/04 13:59:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Chunk.hpp"
#include <unordered_map>
#include <memory>
#include <ChunkGenerator.hpp>

struct World
{
	World(MeshCache &cache) : _generator(16, cache) {}
	~World() {}
	ChunkGenerator	_generator;

	std::shared_ptr<Chunk>	getChunk(Vec3i pos)
	{
		auto find = _chunks.find(pos.hash());

		if (find == _chunks.end())
			return (nullptr);
		return (find->second);
	}
	void	genChunk(Vec3i pos)
	{
		std::shared_ptr<Chunk>	chunk = std::make_shared<Chunk>(pos);

		_generator.gen(chunk);
		_chunks.insert(std::make_pair(pos.hash(), chunk));
	}
	std::unordered_map<uint64_t, std::shared_ptr<Chunk>>	_chunks;
};
