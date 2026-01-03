/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 22:22:50 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 12:54:58 by mbatty           ###   ########.fr       */
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
#include <map>
#include "SDL2/SDL.h"
#include <glad/glad.h>

#include "Math.hpp"
#include "Shader.hpp"
#include "TextureCache.hpp"

class	Mesh
{
	public:
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
	public:
		Mesh(TextureCache &txm) : _txm(txm) {}
		~Mesh() {}

		void	load(const std::string &path);
		void	upload();
		void	unlink()
		{
			for (auto &pair : _materialGroups)
			{
				MaterialGroup	&mtl = pair.second;

				glDeleteBuffers(1, &mtl.VBO);
				glDeleteVertexArrays(1, &mtl.VAO);
				mtl.VBO = 0;
				mtl.VAO = 0;
			}
		}
		void	draw(std::shared_ptr<Shader> shader)
		{
			for (auto &pair : _materialGroups)
			{
				MaterialGroup	&mtl = pair.second;

				shader->setInt("tex", 0);
				shader->setInt("uMaterial.hasDiffuseTex", 0);
				if (mtl.material.texture)
				{
					shader->setInt("uMaterial.hasDiffuseTex", 1);
					mtl.material.texture->bind(0);
				}

				shader->setFloat("uMaterial.opacity", mtl.material.opacity);
				shader->setFloat("uMaterial.shininess", mtl.material.shininess);
				shader->setVec3("uMaterial.ambient", mtl.material.ambient);
				shader->setVec3("uMaterial.diffuse", mtl.material.diffuse);
				shader->setVec3("uMaterial.specular", mtl.material.specular);

				glBindVertexArray(mtl.VAO);
				glDrawArrays(GL_TRIANGLES, 0, mtl.vertices.size());
			}
		}

		uint32_t	getTriangleCount() {return (_triangleCount);}
		void	addFace(Face face)
		{
			_materialGroups["default"].vertices.push_back({face.pos1, face.normal1, face.uv1});
			_materialGroups["default"].vertices.push_back({face.pos2, face.normal2, face.uv2});
			_materialGroups["default"].vertices.push_back({face.pos3, face.normal3, face.uv3});
			_triangleCount++;
		}
	private:
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
		struct	Material
		{
			Vec3	ambient = Vec3(1); // Ka
			Vec3	diffuse = Vec3(1); // Kd
			Vec3	specular = Vec3(0); // Ks

			float	shininess = 0; // Ns
			float	opacity = 1; // d / Tr

			std::shared_ptr<Texture>	texture;
		};
		struct	MaterialGroup
		{
			Material			material;
			std::vector<Vertex>	vertices;
			uint32_t			VAO;
			uint32_t			VBO;
		};
		void		_parseMtlLib(const std::string &path);
		void		_parseFace(MaterialGroup *mtlGroup, std::istringstream &iss);
		Vec3		_parseVec3(std::istringstream &iss);
		Vec2		_parseVec2(std::istringstream &iss);
		float		_parseFloat(std::istringstream &iss);
		std::string	_preprocessLine(const std::string &line);
		uint32_t	_VAO;
		uint32_t	_VBO;

		uint32_t	_lineNumber = 0;
		uint32_t	_triangleCount = 0;
		bool		uploaded = false;

		std::vector<Vertex>	_vertices;

		std::map<std::string, MaterialGroup>	_materialGroups;

		std::vector<Vec3>	_positionVertices;
		std::vector<Vec3>	_normalVertices;
		std::vector<Vec2>	_textureVertices;

		TextureCache &_txm;
};
