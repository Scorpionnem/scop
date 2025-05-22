/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:45:14 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/22 15:31:08 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"

static	bool countInfos = true;

Mesh::Mesh(const std::string &filename)
{
	this->pos = glm::vec3(0.0);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);			
	glGenBuffers(1, &EBO);
	this->loadOBJ(filename);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void	Mesh::addTriangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& color)
{
	glm::vec3 normal = glm::normalize(glm::cross(p2 - p1, p3 - p1));
	unsigned int startIndex = vertices.size();

	vertices.push_back({ p1, normal, color });
	vertices.push_back({ p2, normal, color });
	vertices.push_back({ p3, normal, color });

	indices.push_back(startIndex);
	indices.push_back(startIndex + 1);
	indices.push_back(startIndex + 2);
}

void	Mesh::upload()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void	Mesh::draw(Shader &shader)
{
	shader.use();
	glm::mat4	model(1.0f);
	model = glm::translate(model, pos);
	model = glm::translate(model, center);
	model = glm::rotate(model, glm::radians(20.0f * (float)glfwGetTime()), glm::vec3(0.0, 1.0, 0.0));
	
	model = glm::rotate(model, glm::radians(rotateX), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotateZ), glm::vec3(0.0f, 0.0f, 1.0f));
	
	model = glm::translate(model, -center);

	shader.setMat4("model", model);
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

int Mesh::loadOBJ(const std::string &filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Failed to open model");

	std::vector<glm::vec3> positions;
	std::string line;
	float color = 0.5f;
	bool addedAnyFace = false;

	int lineNumber = 0;
	while (std::getline(file, line))
	{
		lineNumber++;
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v")
		{
			if (countInfos)
				TOTAL_VERTICES++;
			
			float x, y, z;
			if (!(iss >> x >> y >> z))
				throw std::runtime_error("Invalid vertex");
			positions.push_back(glm::vec3(x, y, z));
		}
		else if (prefix == "f")
		{
			if (countInfos)
				TOTAL_FACES++;
			
			std::vector<int> vertexIndices;
			std::string token;
			while (iss >> token)
			{
				std::istringstream ss(token);
				std::string indexStr;
				if (std::getline(ss, indexStr, '/'))
				{
					try {
						int posIndex = std::stoi(indexStr);
						if (posIndex <= 0 || static_cast<size_t>(posIndex) > positions.size()) {
							std::cerr << "Invalid face index on line " << lineNumber << ": " << posIndex << std::endl;
							throw std::runtime_error("Invalid face");
						}
						vertexIndices.push_back(posIndex - 1);
					} catch (...) {
						std::cerr << "Invalid integer in face on line " << lineNumber << std::endl;
						throw std::runtime_error("Invalid face");
					}
				}
			}

			if (vertexIndices.size() < 3)
			{
				std::cerr << "Invalid face (less than 3 vertices) on line " << lineNumber << std::endl;
				throw std::runtime_error("Invalid face");
			}

			for (size_t i = 1; i + 1 < vertexIndices.size(); ++i)
			{
				glm::vec3 v1 = positions[vertexIndices[0]];
				glm::vec3 v2 = positions[vertexIndices[i]];
				glm::vec3 v3 = positions[vertexIndices[i + 1]];
				this->addTriangle(v1, v2, v3, glm::vec3(color));
				addedAnyFace = true;

				color += 0.05f;
				if (color > 0.7f)
					color = 0.5f;
			}
		}
	}

	if (positions.empty())
		throw std::runtime_error("No vertices found in given model");
	if (!addedAnyFace)
		throw std::runtime_error("No faces found in given model");

	glm::vec3 min = vertices[0].position;
	glm::vec3 max = vertices[0].position;

	for (std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		min = glm::min(min, it->position);
		max = glm::max(max, it->position);
	}
	center = (min + max) * 0.5f;

	this->upload();
	countInfos = false;
	return (1);
}
