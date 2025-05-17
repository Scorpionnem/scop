/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:41:09 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/17 11:58:41 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Light.hpp"

Light::Light() : mesh("models/sphere.obj")
{
    pos = glm::vec3(0.0f);
    color = glm::vec3(1.0f);
}

void	Light::update(Shader &shader)
{
	pos = glm::vec3(
		10.0f * cos(glfwGetTime()),
		10.0f * sin(glfwGetTime()),
		10.0f * sin(glfwGetTime())
	);
    
	mesh.pos = pos;
	shader.use();
	shader.setVec3("lightPos", pos);
	shader.setVec3("lightColor", color);
	shader.setFloat("ambientStrength", 0.2);
}

void	Light::draw(Shader &shader, Camera &camera)
{
	camera.setViewMatrix(shader);
	shader.setVec3("lightColor", color);
	mesh.draw(shader);
}
        