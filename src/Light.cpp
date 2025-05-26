/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:41:09 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/26 13:33:58 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Light.hpp"

Light::Light() : mesh("src/assets/models/sphere.obj", "src/assets/textures/icon.bmp")
{
    pos = vec3(0.0f);
    color = vec3(1.0f);
}

void	Light::update(Shader &shader)
{
	pos = vec3(
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
