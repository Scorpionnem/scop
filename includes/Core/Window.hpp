/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:44:54 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 17:32:56 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "SDL2/SDL.h"
#include <glad/glad.h>
#include <stdint.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>

class	Window
{
	public:
		class	Events
		{
			public:
				Events() {}
				~Events() {}

				bool	getInput(int key) const
				{
					auto find = _inputs.find(key);
					if (find == _inputs.end())
						return (false);
					return (find->second);
				}
				void	setInput(int key, bool state)
				{
					_inputs[key] = state;
				}
				float	getMouseDeltaX() const {return (_mouseDeltaX);}
				float	getMouseDeltaY() const {return (_mouseDeltaY);}
				void	setMouseDeltaX(float val) {_mouseDeltaX = val;}
				void	setMouseDeltaY(float val) {_mouseDeltaY = val;}
				void	reset()
				{
					_mouseDeltaX = 0;
					_mouseDeltaY = 0;
				}
			private:
				float	_mouseDeltaX = 0;
				float	_mouseDeltaY = 0;
				std::map<int, bool>	_inputs;
		};
		void	setMousePos(int x, int y)
		{
			SDL_WarpMouseInWindow(_window, x, y);
		}
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
		const Events	&getEvents() {return (_events);}
	private:
		Events			_events;
		SDL_Window		*_window = NULL;
		SDL_GLContext	_GLContext;

		bool			_running = true;

		uint32_t			_width = 0;
		uint32_t			_height = 0;

		std::string		_title;
};
