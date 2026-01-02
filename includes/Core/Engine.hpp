/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:42:51 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 23:51:55 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ctime>
#include "Scene.hpp"

class	Engine
{
	public:
		void	start(Scene *scene)
		{
			clock_gettime(CLOCK_MONOTONIC, &_lastFrame);
			_time = 0;

			_window.open(800, 800, "scop");

			_scene = scene;
			_scene->build();
			_loop();
		}
		const Window	&getWindow() const
		{
			return (_window);
		}
		// Time since engine.start was called
		double getTime() const
		{
			return (_time);
		}
	private:
		void	_loop()
		{
			while (_window.running())
			{
				if (_scene && _scene->requestedStop())
					break ;

				struct timespec	currentFrame;
				double			deltaTime;

				clock_gettime(CLOCK_MONOTONIC, &currentFrame);
				deltaTime = (currentFrame.tv_sec - _lastFrame.tv_sec) + (currentFrame.tv_nsec - _lastFrame.tv_nsec) * 1e-9;
				_time += deltaTime;
				_lastFrame = currentFrame;

				_window.pollEvents();

				if (_scene)
				{
					_scene->update(deltaTime, _window.getEvents());
					_scene->display();
				}

				_window.display();
			}
		}
		Scene	*_scene;
		Window	_window;
		double	_time;

		struct timespec	_lastFrame = {0, 0};
};
