/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:47:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/26 14:20:34 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_HPP
# define MESH_HPP

# include "libs.hpp"
# include "Shader.hpp"
# include "Texture.hpp"

struct Vertex
{
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 texture;
};

struct	MaterialGroup
{
	std::vector<Vertex>	vertices;
	std::vector<unsigned int> indices;
	Texture	*texture;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
};

class Mesh
{
	public:
		vec3	pos;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::map<std::string, MaterialGroup> materialGroups;
		vec3	center;

		float	rotateX = 0.0;
		float	rotateY = 1.0;
		float	rotateZ = 0.0;
	
		~Mesh();
	
		void addTriangle(const vec3& p1, vec2& uv1,
                       const vec3& p2, vec2& uv2,
                       const vec3& p3, vec2& uv3,
                       const vec3& color, const std::string& mtl);
		void upload();
		void	draw(Shader &shader);
		
		Mesh(const std::string &filename, const std::string &baseTexture);
		int loadOBJ(const std::string &filename, const std::string &baseTexture);
};

#endif