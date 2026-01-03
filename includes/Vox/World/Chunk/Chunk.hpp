/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:47 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/04 00:24:27 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <Math.hpp>
#include <Shader.hpp>
#include <MeshCache.hpp>

# define CHUNK_SIZE 16
# define CHUNK_VOLUME CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE
# define BLOCK bool

namespace Cube
{
	const Vec3	V1(0, 1, 1);
	const Vec3	V2(1, 1, 1);
	const Vec3	V3(1, 1, 0);
	const Vec3	V4(0, 1, 0);
	const Vec3	V5(0, 0, 1);
	const Vec3	V6(1, 0, 1);
	const Vec3	V7(1, 0, 0);
	const Vec3	V8(0, 0, 0);

	enum class Direction
	{
		NORTH,
		SOUTH,
		EAST,
		WEST,
		TOP,
		BOTTOM
	};

	void	addFace(std::shared_ptr<Mesh> mesh, Vec3 pos, Direction dir);
}

class	Chunk
{
	public:
		Chunk(Vec3 pos) : _pos(pos) {}
		~Chunk() {}

		Vec3	worldPos(Vec3 pos)
		{
			return (pos + _pos * CHUNK_SIZE);
		}
		void	generate(MeshCache &meshCache)
		{
			_blocks.resize(CHUNK_VOLUME);

			for (int x = 0; x < CHUNK_SIZE; x++)
				for (int y = 0; y < CHUNK_SIZE; y++)
					for (int z = 0; z < CHUNK_SIZE; z++)
						if (worldPos(Vec3(x, y, z)).y < 10)
							setBlock(Vec3(x, y, z), true);
			_mesh = meshCache.gen();
			genMesh();
		}
		void	genMesh()
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
				for (int y = 0; y < CHUNK_SIZE; y++)
					for (int z = 0; z < CHUNK_SIZE; z++)
					{
						if (getBlock(Vec3(x, y, z)))
						{
							if (!getBlock(Vec3(x, y + 1, z)))
								Cube::addFace(_mesh, Vec3(x, y, z), Cube::Direction::TOP);
							if (!getBlock(Vec3(x, y - 1, z)))
								Cube::addFace(_mesh, Vec3(x, y, z), Cube::Direction::BOTTOM);
							if (!getBlock(Vec3(x + 1, y, z)))
								Cube::addFace(_mesh, Vec3(x, y, z), Cube::Direction::EAST);
							if (!getBlock(Vec3(x - 1, y, z)))
								Cube::addFace(_mesh, Vec3(x, y, z), Cube::Direction::WEST);
							if (!getBlock(Vec3(x, y, z + 1)))
								Cube::addFace(_mesh, Vec3(x, y, z), Cube::Direction::NORTH);
							if (!getBlock(Vec3(x, y, z - 1)))
								Cube::addFace(_mesh, Vec3(x, y, z), Cube::Direction::SOUTH);
						}
					}
			_mesh->upload();
		}
		void	draw(std::shared_ptr<Shader> shader)
		{
			_mesh->draw(shader);
		}
		BLOCK	getBlock(Vec3 pos)
		{
			if (!isInBounds(pos))
				return (false);
			int index = pos.x + pos.y * CHUNK_SIZE + pos.z * CHUNK_SIZE * CHUNK_SIZE;
			return (_blocks[index]);
		}
		void	setBlock(Vec3 pos, BLOCK block)
		{
			if (!isInBounds(pos))
				return ;
			int index = pos.x + pos.y * CHUNK_SIZE + pos.z * CHUNK_SIZE * CHUNK_SIZE;
			_blocks[index] = block;
		}

		bool	isInBounds(Vec3 pos)
		{
			if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE || pos.z >= CHUNK_SIZE)
				return (false);
			return (true);
		}
	// private:
		std::vector<BLOCK>	_blocks;
		Vec3				_pos;
		std::shared_ptr<Mesh>	_mesh;
};
