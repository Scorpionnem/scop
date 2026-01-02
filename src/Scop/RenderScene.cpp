/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderScene.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:59:56 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 18:00:52 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RenderScene.hpp"

void	RenderScene::build()
{
	_mesh.load(_modelPath);
	_mesh.upload();

	_camera.pos = Vec3(0, 2, 5);
	_camera.pitch = -20;

	_shader.load(GL_VERTEX_SHADER, "assets/shaders/mesh.vs");
	_shader.load(GL_FRAGMENT_SHADER, "assets/shaders/mesh.fs");
	_shader.link();

	_model = Mat4(1);
}

void	RenderScene::update(float delta, const Window::Events &events)
{
	float	speed = 10 * delta;
	if (events.getInput(SDLK_w))
		_camera.pos = _camera.pos + _camera.front * speed;
	if (events.getInput(SDLK_s))
		_camera.pos = _camera.pos - _camera.front * speed;
	if (events.getInput(SDLK_SPACE))
		_camera.pos = _camera.pos + _camera.up * speed;
	if (events.getInput(SDLK_LSHIFT))
		_camera.pos = _camera.pos - _camera.up * speed;
	if (events.getInput(SDLK_a))
		_camera.pos = _camera.pos - normalize(cross(_camera.front, _camera.up)) * speed;
	if (events.getInput(SDLK_d))
		_camera.pos = _camera.pos + normalize(cross(_camera.front, _camera.up)) * speed;
	_camera.pitch -= events.getMouseDeltaY() * 0.3;
	_camera.yaw += events.getMouseDeltaX() * 0.3;
	_camera.update();
}

void	RenderScene::display()
{
	Mat4	projection = perspective(70, 1, 0.01, 1000);

	_shader.use();
	_shader.setMat4("uModel", _model);
	_shader.setMat4("uView", _camera.getViewMatrix());
	_shader.setMat4("uProjection", projection);

	_mesh.draw();
}
