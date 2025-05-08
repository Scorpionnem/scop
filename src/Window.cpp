/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:11:45 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/05 10:26:01 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include "Terminal.hpp"

static void resize_hook(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

Window::Window() : _lastFrame(0)
{
	//Inits GLFW settings
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Creates and opens window
	_windowData = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WIN_NAME, NULL, NULL);
	if (!_windowData)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(_windowData);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		glfwTerminate();
		return ;
	}
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glfwSetFramebufferSizeCallback(_windowData, resize_hook);
	glfwSetCharCallback(_windowData, terminal_keyboard_input);
	glfwSetKeyCallback(_windowData, terminal_special_keys);
	
	glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	this->center();
}

Window::~Window()
{
	glfwTerminate();
}

GLFWwindow	*Window::getWindowData(void)
{
	return (this->_windowData);
}

void Window::displayFPS()
{
	std::stringstream	strs;
	strs << (int)(1.0f / _deltaTime) << " fps";

	glfwSetWindowTitle(_windowData, strs.str().c_str());
}

void		Window::loopStart(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_currentFrame = glfwGetTime();
	_deltaTime = _currentFrame - _lastFrame;
}

void		Window::loopEnd(void)
{
	glfwSwapBuffers(_windowData);
	glfwPollEvents();
	if ((int)_lastFrame != (int)_currentFrame)
	{
		displayFPS();
	}
	_lastFrame = _currentFrame;
}

bool	Window::up(void)
{
	return (!glfwWindowShouldClose(_windowData));
}

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void		Window::setIcon(const char *path)
{
	GLFWimage	image[1];
	image[0].pixels = stbi_load(path, &image[0].width, &image[0].height, 0, 4);
	if (!image[0].pixels)
	{
		std::cout << "Failed to set window icon" << std::endl;
		return ;
	}
	glfwSetWindowIcon(_windowData, 1, image);
	stbi_image_free(image[0].pixels);
}

void		Window::center()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwSetWindowPos(_windowData, (mode->width / 2) - (SCREEN_WIDTH / 2), (mode->height / 2) - (SCREEN_HEIGHT / 2));
}
