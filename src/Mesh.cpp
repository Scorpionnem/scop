/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:45:14 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/27 13:03:51 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"

static	bool countInfos = true;

Mesh::Mesh(const std::string &filename, const std::string &baseTexture)
{
	this->pos = vec3(0.0);
	this->loadOBJ(filename, baseTexture);
}

Mesh::~Mesh()
{
	for (auto it = materialGroups.begin(); it != materialGroups.end(); it++)
	{
		delete it->second.texture;
		glDeleteBuffers(1, &it->second.VBO);
		glDeleteBuffers(1, &it->second.EBO);
		glDeleteVertexArrays(1, &it->second.VAO);
	}
}

void Mesh::addTriangle(const vec3& p1, vec2& uv1,
                       const vec3& p2, vec2& uv2,
                       const vec3& p3, vec2& uv3,
                       const vec3& color, const std::string& mtl)
{
	vec3 normal = (p2 - p1).cross(p3 - p1).normalize();
	unsigned int startIndex = materialGroups[mtl].vertices.size();

	vec3 absNormal = vec3(std::abs(normal.x), std::abs(normal.y), std::abs(normal.z));

	if (absNormal.x > absNormal.y && absNormal.x > absNormal.z)
	{
		if (uv1.x == -1 && uv1.y == -1)
			uv1 = vec2(p1.z, p1.y);
		if (uv2.x == -1 && uv2.y == -1)
			uv2 = vec2(p2.z, p2.y);
		if (uv3.x == -1 && uv3.y == -1)
			uv3 = vec2(p3.z, p3.y);
	}
	else if (absNormal.y > absNormal.z)
	{
		if (uv1.x == -1 && uv1.y == -1)
			uv1 = vec2(p1.x, p1.z);
		if (uv2.x == -1 && uv2.y == -1)
			uv2 = vec2(p2.x, p2.z);
		if (uv3.x == -1 && uv3.y == -1)
			uv3 = vec2(p3.x, p3.z);
	}
	else
	{
		if (uv1.x == -1 && uv1.y == -1)
			uv1 = vec2(p1.x, p1.y);
		if (uv2.x == -1 && uv2.y == -1)
			uv2 = vec2(p2.x, p2.y);
		if (uv3.x == -1 && uv3.y == -1)
			uv3 = vec2(p3.x, p3.y);
	}

	materialGroups[mtl].vertices.push_back({ p1, normal, color, uv1 });
	materialGroups[mtl].vertices.push_back({ p2, normal, color, uv2 });
	materialGroups[mtl].vertices.push_back({ p3, normal, color, uv3 });

	materialGroups[mtl].indices.push_back(startIndex);
	materialGroups[mtl].indices.push_back(startIndex + 1);
	materialGroups[mtl].indices.push_back(startIndex + 2);
}

void	Mesh::upload()
{
	for (auto it = materialGroups.begin(); it != materialGroups.end(); it++)
	{
		it->second.texture = new Texture(it->first.c_str());
		glGenVertexArrays(1, &it->second.VAO);
		glGenBuffers(1, &it->second.VBO);			
		glGenBuffers(1, &it->second.EBO);
		glBindVertexArray(it->second.VAO);
	
		glBindBuffer(GL_ARRAY_BUFFER, it->second.VBO);
		glBufferData(GL_ARRAY_BUFFER, it->second.vertices.size() * sizeof(Vertex), it->second.vertices.data(), GL_STATIC_DRAW);
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, it->second.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, it->second.indices.size() * sizeof(unsigned int), it->second.indices.data(), GL_STATIC_DRAW);
	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
	
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(1);
	
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(2);
	
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
		glEnableVertexAttribArray(3);
	
		glBindVertexArray(0);
	}
}

void	Mesh::draw(Shader &shader)
{
	shader.use();
	mat4	model(1.0f);
	model = translate(model, pos);
	model = translate(model, center);
	if (mesh_spin)
		model = rotate(model, toRadians(20.0f * (float)glfwGetTime()), vec3(0.0, 1.0, 0.0));
	
	model = rotate(model, toRadians(rotateX), vec3(1.0f, 0.0f, 0.0f));
	model = rotate(model, toRadians(rotateY), vec3(0.0f, 1.0f, 0.0f));
	model = rotate(model, toRadians(rotateZ), vec3(0.0f, 0.0f, 1.0f));
	
	model = translate(model, center * -1);

	shader.setMat4("model", model);
	
	for (auto it = materialGroups.begin(); it != materialGroups.end(); it++)
	{
		it->second.texture->use();
		glBindVertexArray(it->second.VAO);
		glDrawElements(GL_TRIANGLES, it->second.indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void	Mesh::calcMeshCenter(void)
{
	vec3 min = materialGroups.begin()->second.vertices[0].position;
	vec3 max = materialGroups.begin()->second.vertices[0].position;

	for (auto it = materialGroups.begin(); it != materialGroups.end(); it++)
	{
		for (std::vector<Vertex>::iterator itt = it->second.vertices.begin(); itt != it->second.vertices.end(); itt++)
		{
			min = minvec3(min, itt->position);
			max = maxvec3(max, itt->position);
		}
	}
	center = (min + max) / 2;
}

void	loadMTL(MTLMap &mtl, const std::string &filename, const std::string currentDir)
{
	std::ifstream file(filename);
	std::string line;
	std::string currentKey;

	if (!file.is_open())
	{
		if (countInfos)
			std::cout << "Failed to open mtl file " << filename << std::endl;
		return ;
	}

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "newmtl")
		{
			if (!(iss >> currentKey))
				throw std::runtime_error("Invalid newmtl");
			mtl[currentKey].texPath = "textures/mbatty.bmp";
		}
		else if (prefix == "map_Kd")
		{
			std::string	texPath;
			if (!(iss >> texPath))
				throw std::runtime_error("Invalid map_Kd");
			
			texPath = currentDir + texPath;
			mtl[currentKey].texPath = texPath;
		}
	}
}

int Mesh::loadOBJ(const std::string &filename, const std::string &baseTexture)
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Failed to open model");

	std::vector<vec3> positions;
	std::vector<vec2> texPositions;

	std::string line;
	std::string	stdFilename = filename;
	std::string	objPath = filename.substr(0, filename.find_last_of("/"));
	
	float colorOffset = 0.5f;
	
	bool addedAnyFace = false;
	int lineNumber = 0;

	MTLMap mtl;
	MTL	currentMTL = {baseTexture};
	
	while (std::getline(file, line))
	{
		lineNumber++;
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "vt")
		{			
			float u, v;
			if (!(iss >> u >> v))
				throw std::runtime_error("Invalid texture vertex");
			texPositions.push_back(vec2(u, v));
		}
		else if (prefix == "v")
		{
			if (countInfos)
				TOTAL_VERTICES++;
			float x, y, z;
			if (!(iss >> x >> y >> z))
				throw std::runtime_error("Invalid vertex");
			positions.push_back(vec3(x, y, z));
		}
		else if (prefix == "mtllib")
		{
			std::string	mtlFilename;

			if (!(iss >> mtlFilename))
				throw std::runtime_error("Invalid mtllib");

			std::string currentDir;
			if (objPath.size())
				currentDir = objPath + "/";
			else
				currentDir = "";
			
			mtlFilename = currentDir + mtlFilename;
			loadMTL(mtl, mtlFilename, objPath + "/");
		}
		else if (prefix == "usemtl")
		{
			std::string	mtlKey;
			
			if (!(iss >> mtlKey))
				throw std::runtime_error("Invalid mtlkey");
			auto finder = mtl.find(mtlKey);
			if (finder == mtl.end())
				throw std::runtime_error("Invalid mtlkey, not set");

			currentMTL = finder->second;
		}
		else if (prefix == "f")
		{
			std::vector<FaceVertex> faceVertices;
			
			std::string token;
			while (iss >> token)
			{
				std::istringstream ss(token);
				std::string posStr, texStr;
			
				std::getline(ss, posStr, '/');
				std::getline(ss, texStr, '/');
			
				FaceVertex fv = { -1, -1 };

				try {
					fv.posIndex = std::stoi(posStr) - 1;
					if (!texStr.empty())
						fv.texIndex = std::stoi(texStr) - 1;
				}
				catch (...) {
					throw std::runtime_error("Invalid face entry on line " + toString(lineNumber));
				}

				faceVertices.push_back(fv);
			}

			if (faceVertices.size() < 3)
				throw std::runtime_error("Invalid face (less than 3 vertices) on line " + toString(lineNumber));

			for (size_t i = 1; i + 1 < faceVertices.size(); ++i)
			{
				if (countInfos)
					TOTAL_TRIANGLES++;
				const FaceVertex& fv1 = faceVertices[0];
				const FaceVertex& fv2 = faceVertices[i];
				const FaceVertex& fv3 = faceVertices[i + 1];

				vec3 v1 = positions[fv1.posIndex];
				vec3 v2 = positions[fv2.posIndex];
				vec3 v3 = positions[fv3.posIndex];
				
				vec2 uv1 = (fv1.texIndex >= 0 && fv1.texIndex < (int)texPositions.size()) ? vec2(texPositions[fv1.texIndex].x, texPositions[fv1.texIndex].y) : vec2(-1);
				vec2 uv2 = (fv2.texIndex >= 0 && fv2.texIndex < (int)texPositions.size()) ? vec2(texPositions[fv2.texIndex].x, texPositions[fv2.texIndex].y) : vec2(-1);
				vec2 uv3 = (fv3.texIndex >= 0 && fv3.texIndex < (int)texPositions.size()) ? vec2(texPositions[fv3.texIndex].x, texPositions[fv3.texIndex].y) : vec2(-1);

				this->addTriangle(v1, uv1, v2, uv2, v3, uv3, vec3(colorOffset), currentMTL.texPath);
				addedAnyFace = true;

				colorOffset += 0.05f;
				if (colorOffset > 0.7f)
					colorOffset = 0.5f;
			}
		}
	}

	if (positions.empty())
		throw std::runtime_error("No vertices found in " + filename);
	if (!addedAnyFace)
		throw std::runtime_error("No faces found in " + filename);

	this->calcMeshCenter();
	this->upload();
	countInfos = false;
	return (1);
}
