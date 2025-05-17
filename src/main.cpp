/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/17 13:57:17 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

#include "Camera.hpp"
#include "Shader.hpp"

#include "Mesh.hpp"
#include "Light.hpp"
#include "Terminal.hpp"

float	SCREEN_WIDTH = 800;
float	SCREEN_HEIGHT = 800;
float	FOV = 70;

int	interpolate = 0;

bool	lock_fps = true;

bool	camera_toggle = false;
glm::vec3	mesh_pos;
float	mesh_roll;

void	interpolateTo(float &float1, float &float2, float deltaTime)
{
	float1 += (1.0f - float1) * 2.0f * deltaTime;
	if (float1 > 0.99f)
		float1 = 1.0f;

	float2 = 1.0f - float1;
}

void	frame_key_hook(Window &window)
{
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window.getWindowData(), true);
	
	if (isTerminalOn)
		return ;
	
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_C) == GLFW_PRESS)
		window.center();

	float cameraSpeed = 15.0f * window.getDeltaTime();

	if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		cameraSpeed *= 20;
	
	if (camera_toggle)
	{
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
	}
	else
	{
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_A) == GLFW_PRESS)
			mesh_pos.x -= cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_D) == GLFW_PRESS)
			mesh_pos.x += cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_SPACE) == GLFW_PRESS)
			mesh_pos.y += cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			mesh_pos.y -= cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_W) == GLFW_PRESS)
			mesh_pos.z -= cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_S) == GLFW_PRESS)
			mesh_pos.z += cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_UP) == GLFW_PRESS)
			mesh_roll -= cameraSpeed * 4;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_DOWN) == GLFW_PRESS)
			mesh_roll += cameraSpeed * 4;
	}

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;
}

void	key_hook(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;(void)key;(void)scancode;(void)action;(void)mods;

	terminal_special_keys(window, key, scancode, action, mods);
	if (isTerminalOn)
		return ;

	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		interpolate = !interpolate;

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		lock_fps = !lock_fps;
		if (lock_fps)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		camera_toggle = !camera_toggle;
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Wrong argument count." << std::endl;
		return (1);
	}
	try {
		Window		window;
		Camera		camera;
		Shader		shader("shaders/vertex_shader.vs", "shaders/fragment_shader.fs");
		Shader		fb_shader("shaders/vertex_shader.vs", "shaders/full_bright.fs");
		Texture		texture(av[2]);
	
		Mesh		mesh(av[1]);
		Light		light;
		
		pos = glm::vec3(mesh.center.x, mesh.center.y, mesh.center.z + 5.0f);
	
		shader.setInt("tex0", 0);
	
		float	texIntensity = 0.0;
		float	colorIntensity = 1.0;
	
		while (window.up())
		{
			window.loopStart();
	
			camera.update();
			camera.setViewMatrix(shader);
			light.update(shader);
	
			if (interpolate)
				interpolateTo(texIntensity, colorIntensity, window.getDeltaTime());	
			else
				interpolateTo(colorIntensity, texIntensity, window.getDeltaTime());	
			
			shader.use();
			shader.setFloat("texIntensity", texIntensity);
			shader.setFloat("colorIntensity", colorIntensity);
			
			texture.use();
			mesh.pos = mesh_pos;
			mesh.roll = mesh_roll;
			mesh.draw(shader);
			light.draw(fb_shader, camera);
	
			frame_key_hook(window);
			window.loopEnd();
		}
	} catch (const std::exception& e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
		return (1);
	}
}
