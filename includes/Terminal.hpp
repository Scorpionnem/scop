/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Terminal.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:24:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/17 12:16:26 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"

void	terminal_special_keys(GLFWwindow *window, int key, int scancode, int action, int mods);
void	terminal_keyboard_input(GLFWwindow *window, unsigned int key);

extern bool			isTerminalOn;
extern std::string	terminalInput;
