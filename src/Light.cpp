/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:41:09 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/21 16:03:30 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Light.hpp"

Light::Light() : mesh("src/assets/models/sphere.obj")
{
    pos = glm::vec3(0.0f);
    color = glm::vec3(1.0f);
}

void	Light::update(Shader &shader)
{
	pos = glm::vec3(
		15.0f * cos(glfwGetTime()),
		15.0f * sin(glfwGetTime()),
		15.0f * sin(glfwGetTime())
	);
    
	mesh.pos = pos;
	shader.use();
	shader.setVec3("lightPos", pos);
	shader.setVec3("lightColor", color);
}

void	Light::draw(Shader &shader, Camera &camera)
{
	camera.setViewMatrix(shader);
	shader.setVec3("lightColor", color);
	mesh.draw(shader);
}
