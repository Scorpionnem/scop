/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/12 23:18:49 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

#include "Camera.hpp"
#include "Shader.hpp"

#include "Mesh.hpp"

float	SCREEN_WIDTH = 800;
float	SCREEN_HEIGHT = 800;

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
		yaw -= 1.f;
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		yaw += 1.f;
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_UP) == GLFW_PRESS)
		pitch += 1.f;
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_DOWN) == GLFW_PRESS)
		pitch -= 1.f;

	if (glfwGetKey(window.getWindowData(), GLFW_KEY_C) == GLFW_PRESS)
		glFrontFace(GL_CW);
		
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_V) == GLFW_PRESS)
		glFrontFace(GL_CCW);


	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;
}

void loadOBJ(const std::string& filename, Mesh& mesh) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open OBJ file: " << filename << std::endl;
		return;
	}

	std::vector<glm::vec3> positions;

	std::string line;
	float	color = 0.0f;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v") {
			float x, y, z;
			iss >> x >> y >> z;
			positions.push_back(glm::vec3(x, y, z));
		} else if (prefix == "f") {
			std::vector<int> vertexIndices;
			std::string token;
			while (iss >> token) {
				std::istringstream ss(token);
				std::string indexStr;
				std::getline(ss, indexStr, '/'); // just get the position index before first "/"
				int posIndex = std::stoi(indexStr);
				vertexIndices.push_back(posIndex - 1); // OBJ is 1-indexed
			}
			// Triangulate if more than 3 vertices
			for (size_t i = 1; i + 1 < vertexIndices.size(); ++i) {
				glm::vec3 v1 = positions[vertexIndices[0]];
				glm::vec3 v2 = positions[vertexIndices[i]];
				glm::vec3 v3 = positions[vertexIndices[i + 1]];
				mesh.addTriangle(v1, v2, v3, glm::vec3(color, color, color));
				color += 0.05f;
				if (color > 1.0)
					color = 0.0;
			}
		}
	}
}

int	main(void)
{
	Window		window;
	Camera		camera;
	Shader		shader("shaders/vertex_shader.vs", "shaders/fragment_shader.fs");

	// glfwSwapInterval(0);

	window.setIcon("textures/icon.png");

	Mesh		mesh;

	// mesh.addTriangle(glm::vec3(1,1,-2), glm::vec3(1,0,-2), glm::vec3(0,0,-2));
	// mesh.addTriangle(glm::vec3(-1,-1,2), glm::vec3(-1,0,2), glm::vec3(0,0,2));

	loadOBJ("models/42.obj", mesh);
	mesh.upload();

	pos.x = 1;
	pos.y = 1;
	pos.z = -2;

	while (window.up())
	{
		window.loopStart();

		std::cout << pos.x << " | " << pos.y << " | " << pos.z << " | " << yaw << std::endl;

		camera.update();
		glm::mat4	view = camera.getViewMatrix();
		glm::mat4	projection = glm::perspective(glm::radians(90.0f), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 180.0f);
		glm::mat4	model(1.0f);

		shader.use();
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);
		shader.setMat4("model", model);

		mesh.draw();

		key_hook(window);

		window.loopEnd();
	}
}
