/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:44:54 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 16:26:33 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "SDL2/SDL.h"
#include <glad/glad.h>
#include <stdint.h>
#include <string>
#include <stdexcept>
#include <iostream>

class	Window
{
	public:
		Window() {}
		~Window() {}

		void	open(uint32_t width, uint32_t height, const std::string &title);
		void	close();
		void	pollEvents();
		void	display();
		bool	running() {return (_running);}
		float	aspectRatio()
		{
			return ((float)_width / (float)_height);
		}
	private:
		SDL_Window		*_window = NULL;
		SDL_GLContext	_GLContext;

		bool			_running = true;

		uint32_t			_width = 0;
		uint32_t			_height = 0;

		std::string		_title;
};
