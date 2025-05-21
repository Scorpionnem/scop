/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:47:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/21 21:33:07 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_HPP
# define MESH_HPP

# include "libs.hpp"
# include "Shader.hpp"

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

		float	rotateX = 0.0;
		float	rotateY = 1.0;
		float	rotateZ = 0.0;
	
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;
	
		~Mesh();
	
		void addTriangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& color);	
		void upload();
		void	draw(Shader &shader);
		
		Mesh(const std::string &filename);
		int loadOBJ(const std::string &filename);
};

#endif