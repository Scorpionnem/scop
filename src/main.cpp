/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/14 14:03:57 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

#include "Camera.hpp"
#include "Shader.hpp"

#include "Mesh.hpp"

float	SCREEN_WIDTH = 400;
float	SCREEN_HEIGHT = 400;

int	interpolate = 0;

void	key_hook(Window &window)
{
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window.getWindowData(), true);
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_C) == GLFW_PRESS)
		window.center();

	float cameraSpeed = 15.0f * window.getDeltaTime();

	if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		cameraSpeed *= 20;
		
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_W) == GLFW_PRESS)
		pos += cameraSpeed * front;
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_S) == GLFW_PRESS)
		pos -= cameraSpeed * front;
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_SPACE) == GLFW_PRESS)
		pos += cameraSpeed * up;
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		pos -= cameraSpeed * up;
		
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_A) == GLFW_PRESS)
		pos -=  glm::normalize(glm::cross(front, up)) * cameraSpeed;
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_D) == GLFW_PRESS)
		pos +=  glm::normalize(glm::cross(front, up)) * cameraSpeed;
		
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT) == GLFW_PRESS)
		yaw -= (10.0f * cameraSpeed) * 1.f;
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		yaw += (10.0f * cameraSpeed) * 1.f;
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_UP) == GLFW_PRESS)
		pitch += (10.0f * cameraSpeed) * 1.f;
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_DOWN) == GLFW_PRESS)
		pitch -= (10.0f * cameraSpeed) * 1.f;

	if (glfwGetKey(window.getWindowData(), GLFW_KEY_Q) == GLFW_PRESS)
		interpolate = !interpolate;	

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;
}

void	interpolateTo(float &float1, float &float2, float deltaTime)
{
	float1 += (1.0f - float1) * 2.0f * deltaTime;
	if (float1 > 0.99f)
		float1 = 1.0f;

	float2 = 1.0f - float1;
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Wrong argument count." << std::endl;
		return (1);
	}
	Window		window;
	Camera		camera;
	Shader		shader("shaders/vertex_shader.vs", "shaders/fragment_shader.fs");
	Texture		texture("textures/texture.png");

	// glfwSwapInterval(0);

	window.setIcon("textures/icon.png");

	Mesh		mesh;
	mesh.loadOBJ(av[1]);

	pos = mesh.center;
	pos.z += 5.0f;

	shader.setInt("tex0", 0);

	float	texIntensity = 0.0;
	float	colorIntensity = 1.0;

	while (window.up())
	{
		window.loopStart();

		camera.update();
		camera.setViewMatrix(shader);

		if (interpolate)
			interpolateTo(texIntensity, colorIntensity, window.getDeltaTime());	
		else
			interpolateTo(colorIntensity, texIntensity, window.getDeltaTime());	

		shader.setFloat("texIntensity", texIntensity);
		shader.setFloat("colorIntensity", colorIntensity);

		texture.use();

		mesh.draw(shader);

		Texture::reset();
		
		key_hook(window);
		window.loopEnd();
	}
}
