/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderScene.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:59:56 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 23:59:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RenderScene.hpp"

void	RenderScene::build()
{
	_mesh.load(_modelPath);
	_mesh.upload();
	std::cout << _mesh.getTriangleCount() << " Triangles" << std::endl;

	_camera.pos = Vec3(0, 2, 5);
	_camera.pitch = -20;

	_shader.load(GL_VERTEX_SHADER, "assets/shaders/mesh.vs");
	_shader.load(GL_FRAGMENT_SHADER, "assets/shaders/mesh.fs");
	_shader.link();

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
		_shader.reload();
	}

	_updateCamera(delta, events);
}

void	RenderScene::_updateCamera(float delta, const Window::Events &events)
{
	float	speed = 10 * delta;

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
	if (events.getMouseBtn(SDL_BUTTON_LEFT))
	{
		_camera.pitch -= events.getMouseDeltaY() * 0.3;
		_camera.yaw += events.getMouseDeltaX() * 0.3;
	}
	_camera.update();
}

void	RenderScene::display()
{
	Mat4	projection = perspective(70, _engine.getWindow().aspectRatio(), 0.01, 1000);

	_shader.use();
	_shader.setMat4("uModel", _model);
	_shader.setMat4("uView", _camera.getViewMatrix());
	_shader.setMat4("uProjection", projection);

	_shader.setFloat("uTime", _engine.getTime());

	_shader.setInt("uTriangleCount", _mesh.getTriangleCount());

	_shader.setVec3("uLightPos", Vec3(3, 10, 3));
	_shader.setVec3("uLightColor", Vec3(1, 1, 1));
	_shader.setVec3("uViewPos", _camera.pos);

	_mesh.draw(_shader);
}
