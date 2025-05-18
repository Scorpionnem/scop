/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:54:38 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/18 14:22:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"
#include "Camera.hpp"

glm::vec3 pos;
glm::vec3 front;
glm::vec3 up;

float	deltaTime = 0.0f;
float	lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;

Camera::Camera()
{
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void	Camera::update()
{
	this->direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->direction.y = sin(glm::radians(pitch));
	this->direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(direction);
}

void	Camera::setViewMatrix(Shader &shader)
{
	glm::mat4	view = this->getViewMatrix();
	glm::mat4	projection = glm::perspective(glm::radians(FOV), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, RENDER_DISTANCE);

	shader.use();
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
}

glm::mat4	Camera::getViewMatrix()
{
	return (glm::lookAt(pos, pos + front, up));
}
