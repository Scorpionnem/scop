/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderScene.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:59:56 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/03 11:44:52 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RenderScene.hpp"

void	RenderScene::build()
{
	_mesh = _engine.loadMesh(_modelPath);
	_mesh->upload();
	std::cout << _mesh->getTriangleCount() << " Triangles" << std::endl;

	_camera.pos = Vec3(0, 0, 0);

	_engine.getLightCache().add(Vec3(0), Vec3(0, 0.5, 0.8));
	_engine.getLightCache().add(Vec3(-0.4, 3, 1), Vec3(0.9, 0, 0.15));

	_shader = _engine.loadShader("assets/shaders/core/mesh");

	_model = Mat4(1);
}

void	RenderScene::update(float delta, const Window::Events &events)
{
	int	windowWidth = _engine.getWindow().width();
	int	windowHeight = _engine.getWindow().height();

	if (events.getMouseBtn(SDL_BUTTON_LEFT))
		_engine.getWindow().setMousePos(windowWidth / 2, windowHeight / 2);

	if (events.getKey(SDLK_ESCAPE))
		requestStop();

	if (events.getKeyPressed(SDLK_r) && events.getKey(SDLK_LCTRL))
	{
		std::cout << "Reloading shader" << std::endl;
		_shader->reload();
	}

	_updateCamera(delta, events);
}

void	RenderScene::_updateCamera(float delta, const Window::Events &events)
{
	float	speed = 10 * delta;
	float	sensitivity = 0.3;

	if (events.getKey(SDLK_w))
		_camera.pos = _camera.pos + _camera.front * speed;
	if (events.getKey(SDLK_s))
		_camera.pos = _camera.pos - _camera.front * speed;
	if (events.getKey(SDLK_SPACE))
		_camera.pos = _camera.pos + _camera.up * speed;
	if (events.getKey(SDLK_LSHIFT))
		_camera.pos = _camera.pos - _camera.up * speed;
	if (events.getKey(SDLK_a))
		_camera.pos = _camera.pos - normalize(cross(_camera.front, _camera.up)) * speed;
	if (events.getKey(SDLK_d))
		_camera.pos = _camera.pos + normalize(cross(_camera.front, _camera.up)) * speed;
	if (events.getKey(SDLK_UP))
		_camera.pitch += speed * 2;
	if (events.getKey(SDLK_DOWN))
		_camera.pitch -= speed * 2;
	if (events.getKey(SDLK_RIGHT))
		_camera.yaw += speed * 2;
	if (events.getKey(SDLK_LEFT))
		_camera.yaw -= speed * 2;

	if (events.getMouseBtnPressed(SDL_BUTTON_LEFT))
		SDL_ShowCursor(SDL_DISABLE);
	if (events.getMouseBtnLifted(SDL_BUTTON_LEFT))
		SDL_ShowCursor(SDL_ENABLE);
	if (events.getMouseBtn(SDL_BUTTON_LEFT))
	{
		_camera.pitch -= events.getMouseDeltaY() * sensitivity;
		_camera.yaw += events.getMouseDeltaX() * sensitivity;
	}

	_camera.update();
}

void	RenderScene::display()
{
	Mat4	projection = perspective(70, _engine.getWindow().aspectRatio(), 0.01, 1000);

	_shader->use();

	_shader->setFloat("uTime", _engine.getTime());
	_shader->setInt("uTriangleCount", _mesh->getTriangleCount());

	_engine.getLightCache().setUniforms(_shader);

	_engine.getLightCache().draw(_camera, projection);

	_mesh->draw(_camera, projection, _shader);

	_engine.renderBoundingBox(_camera, projection, _mesh->getSmallestPoint(), _mesh->getBiggestPoint(), 1);
}
