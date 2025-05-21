/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:11:45 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/21 22:59:37 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include "Terminal.hpp"
#include "Camera.hpp"

static void resize_hook(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

void	key_hook(GLFWwindow *window, int key, int scancode, int action, int mods);

Window::Window() : _lastFrame(0)
{
	//Inits GLFW settings
	if (!glfwInit())
		throw std::runtime_error("Failed to initialize glfw");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Creates and opens window
	_windowData = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WIN_NAME, NULL, NULL);
	if (!_windowData)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window");
	}
	glfwMakeContextCurrent(_windowData);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		throw std::runtime_error("Failed to init GLAD");
	}
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glfwSetFramebufferSizeCallback(_windowData, resize_hook);
	glfwSetCharCallback(_windowData, terminal_keyboard_input);
	glfwSetKeyCallback(_windowData, key_hook);

	glClearColor(0.03f, 0.03f, 0.03f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	this->center();
	this->setIcon("src/assets/textures/icon.png");
}

Window::~Window()
{
	glfwDestroyWindow(this->_windowData);
	glfwTerminate();
}

GLFWwindow	*Window::getWindowData(void)
{
	return (this->_windowData);
}

std::string Window::displayFPS(Font &font, Shader &textShader)
{
	(void)font;(void)textShader;
	std::stringstream	strs;
	strs << (int)(1.0f / _deltaTime) << " fps";

	std::string	str = strs.str();
	return (str);
}

void		Window::loopStart(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_currentFrame = glfwGetTime();
	_deltaTime = _currentFrame - _lastFrame;
}

void		Window::loopEnd(Font &font, Shader &textShader)
{
	static std::string	str = "0 fps";
	if ((int)_lastFrame != (int)_currentFrame)
		str = displayFPS(font, textShader);
	font.putString(str.c_str(), textShader, glm::vec2(SCREEN_WIDTH - str.length() * (TERMINAL_CHAR_SIZE / 2), (TERMINAL_CHAR_SIZE / 2) * 0), glm::vec2(str.length() * (TERMINAL_CHAR_SIZE / 2), TERMINAL_CHAR_SIZE / 2));

	glfwSwapBuffers(_windowData);
	glfwPollEvents();

	_lastFrame = _currentFrame;
}

bool	Window::up(void)
{
	return (!glfwWindowShouldClose(_windowData));
}

void		Window::setIcon(const char *path)
{
	GLFWimage	image[1];
	stbi_set_flip_vertically_on_load(false);
	image[0].pixels = stbi_load(path, &image[0].width, &image[0].height, 0, 4);
	if (!image[0].pixels)
		throw std::runtime_error("Failed to set window icon");
	glfwSetWindowIcon(_windowData, 1, image);
	stbi_image_free(image[0].pixels);
}

void		Window::center()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwSetWindowPos(_windowData, (mode->width / 2) - (SCREEN_WIDTH / 2), (mode->height / 2) - (SCREEN_HEIGHT / 2));
}

float		Window::getDeltaTime(void)
{
	return (this->_deltaTime);
}
