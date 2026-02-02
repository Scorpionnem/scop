/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:17:16 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/02 14:52:45 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"

void	Engine::start(std::unique_ptr<Scene> scene)
{
	try {
		clock_gettime(CLOCK_MONOTONIC, &_lastFrame);
		_time = 0;

		_window.open(800, 800, "scop");

		_boundingBoxMesh = _meshes.get("assets/models/cube.obj");
		_boundingBoxShader = _shaders.get("assets/shaders/core/bounding");

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

void	Engine::renderBoundingBox(Camera &cam, Mat4 &proj, Vec3 min, Vec3 max, Vec3 color = Vec3(1)) const
{
	Vec3	center = (min + max) / 2;
	Vec3	size   = (max - min);

	Mat4	model(1.0f);
	model = model * translate(center);
	model = model * scale(size / 2);

	_boundingBoxShader->use();
	_boundingBoxShader->setMat4("uModel", model);
	_boundingBoxShader->setMat4("uView", cam.getViewMatrix());
	_boundingBoxShader->setMat4("uProjection", proj);
	
	_boundingBoxShader->setVec3("color", color);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	_boundingBoxMesh->draw(_boundingBoxShader);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
