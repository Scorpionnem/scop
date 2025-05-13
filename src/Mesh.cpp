/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:45:14 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/13 15:59:34 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"

Mesh::Mesh()
{
	this->pos = glm::vec3(0.0);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);			
	glGenBuffers(1, &EBO);
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
	model = glm::rotate(model, glm::radians(20.0f * (float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void	Mesh::loadOBJ(const std::string &filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open OBJ file: " << filename << std::endl;
		return;
	}

	std::vector<glm::vec3> positions;

	std::string line;
	float	color = 0.5f;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v")
		{
			float x, y, z;
			iss >> x >> y >> z;
			positions.push_back(glm::vec3(x, y, z));
		}
		else if (prefix == "f")
		{
			std::vector<int> vertexIndices;
			std::string token;
			while (iss >> token)
			{
				std::istringstream ss(token);
				std::string indexStr;
				std::getline(ss, indexStr, '/');
				int posIndex = std::stoi(indexStr);
				vertexIndices.push_back(posIndex - 1);
			}
			for (size_t i = 1; i + 1 < vertexIndices.size(); ++i)
			{
				glm::vec3 v1 = positions[vertexIndices[0]];
				glm::vec3 v2 = positions[vertexIndices[i]];
				glm::vec3 v3 = positions[vertexIndices[i + 1]];
				this->addTriangle(v1, v2, v3, glm::vec3(color, color, color));
				color += 0.05f;
				if (color > 1.0)
					color = 0.5;
			}
		}
	}
	this->upload();
}