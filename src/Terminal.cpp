/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Terminal.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:19:57 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/21 14:35:55 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Terminal.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

bool		isTerminalOn = false;
std::string	terminalInput;

bool		terminalIgnoreNext = false;

void	terminal_setting_command(std::istringstream	&iss)
{
	std::string	arg;

	if (iss >> arg)
	{
	}
	else
		std::cout << "setting: Not enough arguments." << std::endl;
}

void	terminal_culling_command(std::istringstream	&iss)
{
	std::string	arg;

	if (iss >> arg)
	{
		if (arg == "clockwise" || arg == "cw" || arg == "CW")
		{
			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CW);
		}
		if (arg == "counter_clockwise" || arg == "ccw" || arg == "CCW")
		{
			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CCW);
		}
		if (arg == "off")
			glDisable(GL_CULL_FACE);
		else
			std::cout << "/culling help | off | clockwise | counter_clockwise" << std::endl;
	}
	else
		std::cout << "culling: Not enough arguments." << std::endl;
}

void	terminal_background_command(std::istringstream &iss)
{
	std::string	arg;

	if (iss >> arg)
	{
		if (arg == "set")
		{
			float r, g, b;
			if (iss >> r && iss >> g && iss >> b)
				glClearColor(r, g, b, 1.0f);
			else
				std::cout << "Error" << std::endl;
		}
		else
			std::cout << "/background help | set" << std::endl;
	}
	else
		std::cout << "background: Not enough arguments." << std::endl;
}

void	terminal_render_command(std::istringstream &iss)
{
	std::string	arg;

	if (iss >> arg)
	{
		if (arg == "wireframe")
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else if (arg == "normal")
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			std::cout << "/render help | wireframe | normal" << std::endl;
	}
	else
		std::cout << "render: Not enough arguments." << std::endl;
}

void	terminal_execute_command(std::string str)
{
	if (!str.size())
		return ;
	std::istringstream	iss(str);
	std::string	command;

	iss >> command;
	if (command == "setting")
		terminal_setting_command(iss);
	else if (command == "culling")
		terminal_culling_command(iss);
	else if (command == "background")
		terminal_background_command(iss);
	else if (command == "render")
		terminal_render_command(iss);
	else if (command == "help")
	{
		std::cout << "Available commands:" << std::endl;
		std::cout << "- background: edits the background color" << std::endl;
		std::cout << "- culling: changes culling modes" << std::endl;
		std::cout << "- render: changes render modes" << std::endl;
		std::cout << "- help: opens this" << std::endl;

	}
	else
		std::cout << "Command not found." << std::endl;
}

void	terminal_special_keys(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;(void)key;(void)scancode;(void)action;(void)mods;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (isTerminalOn)
		{
			if (key == GLFW_KEY_BACKSPACE && terminalInput.size())
			{
				terminalInput.pop_back();
				std::cout << "\033c\r" << terminalInput << "_" << std::endl;
			}
			if (key == GLFW_KEY_ENTER)
			{
				std::cout << "\033c\r";
				terminal_execute_command(terminalInput);
				isTerminalOn = false;
				terminalInput.clear();
			}
		}
		else if (key == GLFW_KEY_T || key == GLFW_KEY_SLASH)
		{
			isTerminalOn = true;
			terminalIgnoreNext = true;
		}
	}
}

void	terminal_keyboard_input(GLFWwindow *window, unsigned int key)
{
	(void)window;
	if (isTerminalOn && !terminalIgnoreNext)
	{
		if (key >= 32 && key <= 126)
			terminalInput += (char)key;
		std::cout << "\033c\r" << terminalInput << "_" << std::endl;
	}
	terminalIgnoreNext = false;
}
