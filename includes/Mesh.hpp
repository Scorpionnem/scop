/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:47:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/15 15:40:27 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"
#include "Shader.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
};

class Mesh
{
	public:
		glm::vec3	pos;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		glm::vec3	center;
	
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;
	
		Mesh();
	
		void addTriangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& color);	
		void upload();
		void	draw(Shader &shader);
		
		void	loadOBJ(const std::string &filename);
};
