/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 22:22:50 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 15:57:54 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstdint>
#include "SDL2/SDL.h"
#include <glad/glad.h>

#include "Math.hpp"

class	Mesh
{
	public:
		Mesh() {}
		~Mesh() {}

		void	load(const std::string &path);
		void	upload()
		{
			glGenVertexArrays(1, &_VAO);
			glGenBuffers(1, &_VBO);

			glBindVertexArray(_VAO);

			glBindBuffer(GL_ARRAY_BUFFER, _VBO);
			glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
			glEnableVertexAttribArray(2);

			glBindVertexArray(0);
		}
		void	draw()
		{
			glBindVertexArray(_VAO);
			glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
		}
	private:
		struct	Face
		{
			Face() {}
			Vec3	pos1;
			Vec3	pos2;
			Vec3	pos3;
			Vec2	uv1;
			Vec2	uv2;
			Vec2	uv3;
			Vec3	normal1;
			Vec3	normal2;
			Vec3	normal3;
		};
		struct Vertex
		{
			Vec3 pos;
			Vec3 normal;
			Vec2 uv;
		};
		struct	FaceVertex
		{
			FaceVertex(int pos, int uv, int normal)
			{
				this->pos = pos;
				this->uv = uv;
				this->normal = normal;
			}
			int	pos;
			int	uv;
			int	normal;
		};
		void		_parseFace(std::istringstream &iss);
		Vec3		_parseVec3(std::istringstream &iss);
		Vec2		_parseVec2(std::istringstream &iss);
		std::string	_preprocessLine(const std::string &line);
		uint32_t	_VAO;
		uint32_t	_VBO;

		uint32_t	_lineNumber = 0;
		uint32_t	_triangleCount = 0;

		std::vector<Vertex>	_vertices;

		std::vector<Vec3>	_positionVertices;
		std::vector<Vec3>	_normalVertices;
		std::vector<Vec2>	_textureVertices;
};
