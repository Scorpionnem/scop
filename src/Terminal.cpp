/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Terminal.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:19:57 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/16 20:47:08 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Terminal.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

bool		isTerminalOn = false;
std::string	terminalInput;

bool		_terminalIgnoreNext = false;

void	terminal_setting_command(std::istringstream	&iss)
{
	std::string	arg;

	if (iss >> arg)
	{
	}
	else
		std::cout << "setting: Not enough arguments.";
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
		if (arg == "help")
		{
			std::cout << "/culling help | off | clockwise | counter_clockwise" << std::endl;
		}
	}
	else
		std::cout << "setting: Not enough arguments.";
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
	else
		std::cout << "Command not found." << std::endl;
}

void	terminal_special_keys(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;(void)key;(void)scancode;(void)action;(void)mods;
	if (action == GLFW_PRESS)
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
			_terminalIgnoreNext = true;
		}
	}
}

void	terminal_keyboard_input(GLFWwindow *window, unsigned int key)
{
	(void)window;
	if (isTerminalOn && !_terminalIgnoreNext)
	{
		if (key >= 32 && key <= 126)
			terminalInput += (char)key;
		std::cout << "\033c\r" << terminalInput << "_" << std::endl;
	}
	_terminalIgnoreNext = false;
}
