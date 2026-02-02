/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 22:22:50 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/02 14:40:35 by mbatty           ###   ########.fr       */
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
		struct Vertex
		{
			Vertex(){}
			Vertex(Vec3 pos, Vec3 normal, Vec2 uv)
			{
				this->pos = pos;
				this->normal = normal;
				this->uv = uv;
			}
			Vec3 pos;
			Vec3 normal;
			Vec2 uv;
		};
		struct	Face
		{
			Face(){}
			Face(Vertex v1, Vertex v2, Vertex v3)
			{
				this->v1 = v1;
				this->v2 = v2;
				this->v3 = v3;
			}
			Vertex	v1;
			Vertex	v2;
			Vertex	v3;
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
			shader->use();

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
		void	addFace(const std::string &material, Face face)
		{
			_materialGroups[material].vertices.push_back(face.v1);
			_materialGroups[material].vertices.push_back(face.v2);
			_materialGroups[material].vertices.push_back(face.v3);
			_triangleCount++;
		}
		void	addMaterial(const std::string &id, Material material)
		{
			_materialGroups[id].material = material;
		}
		Vec3	_biggestPoint;
		Vec3	_smallestPoint;
		Vec3	_centerPoint;
		bool	_bigSmallUnset = true;
	private:
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
		void		_addVertex(Mesh::Vertex &v);
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
