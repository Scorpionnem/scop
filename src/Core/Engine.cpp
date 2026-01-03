/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:17:16 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 14:03:10 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"

void	Engine::start(std::unique_ptr<Scene> scene)
{
	try {
		clock_gettime(CLOCK_MONOTONIC, &_lastFrame);
		_time = 0;

		_window.open(800, 800, "scop");

		_scene = std::move(scene);
		_scene->build();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return ;
	}
	_loop();
}

void	Engine::_loop()
{
	while (_window.running())
	{
		if (_scene->requestedScene())
		{
			_scene = std::move(_scene->sceneRequest());
			_scene->build();
		}
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
