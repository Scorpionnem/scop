/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VoxScene.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:15:34 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/04 15:24:47 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VoxScene.hpp"
#include "RenderScene.hpp"
#include "Math.hpp"

void	Cube::addFace(std::shared_ptr<Mesh> mesh, Vec3i pos, Direction dir)
	{
		Mesh::Face	Triangle1;
		Mesh::Face	Triangle2;

		switch (dir)
		{
			case Direction::NORTH:
				Triangle1.pos1 = V5;
				Triangle1.pos2 = V2;
				Triangle1.pos3 = V1;
				Triangle1.normal1 = Vec3(0, 0, 1);
				Triangle1.normal2 = Vec3(0, 0, 1);
				Triangle1.normal3 = Vec3(0, 0, 1);
				Triangle2.pos1 = V5;
				Triangle2.pos2 = V6;
				Triangle2.pos3 = V2;
				Triangle2.normal1 = Vec3(0, 0, 1);
				Triangle2.normal2 = Vec3(0, 0, 1);
				Triangle2.normal3 = Vec3(0, 0, 1);
				break ;
			case Direction::SOUTH:
				Triangle1.pos1 = V8;
				Triangle1.pos2 = V4;
				Triangle1.pos3 = V3;
				Triangle1.normal1 = Vec3(0, 0, -1);
				Triangle1.normal2 = Vec3(0, 0, -1);
				Triangle1.normal3 = Vec3(0, 0, -1);
				Triangle2.pos1 = V8;
				Triangle2.pos2 = V3;
				Triangle2.pos3 = V7;
				Triangle2.normal1 = Vec3(0, 0, -1);
				Triangle2.normal2 = Vec3(0, 0, -1);
				Triangle2.normal3 = Vec3(0, 0, -1);
				break ;
			case Direction::EAST:
				Triangle1.pos1 = V3;
				Triangle1.pos2 = V2;
				Triangle1.pos3 = V6;
				Triangle1.normal1 = Vec3(1, 0, 0);
				Triangle1.normal2 = Vec3(1, 0, 0);
				Triangle1.normal3 = Vec3(1, 0, 0);
				Triangle2.pos1 = V3;
				Triangle2.pos2 = V6;
				Triangle2.pos3 = V7;
				Triangle2.normal1 = Vec3(1, 0, 0);
				Triangle2.normal2 = Vec3(1, 0, 0);
				Triangle2.normal3 = Vec3(1, 0, 0);
				break ;
			case Direction::WEST:
				Triangle1.pos1 = V5;
				Triangle1.pos2 = V1;
				Triangle1.pos3 = V4;
				Triangle1.normal1 = Vec3(-1, 0, 0);
				Triangle1.normal2 = Vec3(-1, 0, 0);
				Triangle1.normal3 = Vec3(-1, 0, 0);
				Triangle2.pos1 = V5;
				Triangle2.pos2 = V4;
				Triangle2.pos3 = V8;
				Triangle2.normal1 = Vec3(-1, 0, 0);
				Triangle2.normal2 = Vec3(-1, 0, 0);
				Triangle2.normal3 = Vec3(-1, 0, 0);
				break ;
			case Direction::TOP:
				Triangle1.pos1 = V1;
				Triangle1.pos2 = V2;
				Triangle1.pos3 = V4;
				Triangle1.normal1 = Vec3(0, 1, 0);
				Triangle1.normal2 = Vec3(0, 1, 0);
				Triangle1.normal3 = Vec3(0, 1, 0);
				Triangle2.pos1 = V2;
				Triangle2.pos2 = V3;
				Triangle2.pos3 = V4;
				Triangle2.normal1 = Vec3(0, 1, 0);
				Triangle2.normal2 = Vec3(0, 1, 0);
				Triangle2.normal3 = Vec3(0, 1, 0);
				break ;
			case Direction::BOTTOM:
				Triangle1.pos1 = V8;
				Triangle1.pos2 = V6;
				Triangle1.pos3 = V5;
				Triangle1.normal1 = Vec3(0, -1, 0);
				Triangle1.normal2 = Vec3(0, -1, 0);
				Triangle1.normal3 = Vec3(0, -1, 0);
				Triangle2.pos1 = V8;
				Triangle2.pos2 = V7;
				Triangle2.pos3 = V6;
				Triangle2.normal1 = Vec3(0, -1, 0);
				Triangle2.normal2 = Vec3(0, -1, 0);
				Triangle2.normal3 = Vec3(0, -1, 0);
				break ;
		}
		Triangle1.pos1 = Triangle1.pos1 + pos;
		Triangle1.pos2 = Triangle1.pos2 + pos;
		Triangle1.pos3 = Triangle1.pos3 + pos;

		Triangle2.pos1 = Triangle2.pos1 + pos;
		Triangle2.pos2 = Triangle2.pos2 + pos;
		Triangle2.pos3 = Triangle2.pos3 + pos;
		mesh->addFace("default", Triangle1);
		mesh->addFace("default", Triangle2);
	}

void	VoxScene::build()
{
	_camera.pos = Vec3(-1, 0, -1);
	_camera.pitch = -20;

	_light = _engine.getLightCache().add(Vec3(0), Vec3(1));

	_shader = _engine.loadShader("assets/shaders/core/mesh");
}

void	VoxScene::update(float delta, const Window::Events &events)
{
	int	windowWidth = _engine.getWindow().width();
	int	windowHeight = _engine.getWindow().height();

	if (events.getKeyPressed(SDLK_1))
		requestScene(std::move(std::make_unique<RenderScene>(_engine, "assets/models/miata/miata.obj")));

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

void	VoxScene::_updateCamera(float delta, const Window::Events &events)
{
	float	speed = 50 * delta;
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
	_world.update(_camera);
}

void	VoxScene::display()
{
	Mat4	model(1);
	Mat4	view = _camera.getViewMatrix();
	Mat4	projection = perspective(70, _engine.getWindow().aspectRatio(), 0.01, 1000);

	_engine.getLightCache().setUniforms(_shader);
	// _engine.getLightCache().draw(view, projection);

	_shader->use();
	_shader->setMat4("uView", view);
	_shader->setMat4("uProjection", projection);

	_shader->setFloat("uTime", _engine.getTime());
	_shader->setVec3("uViewPos", _camera.pos);

	_light->setPos(_camera.pos);

	auto chunks = _world.getLoadedChunks();
	for (auto chunk : chunks)
	{
		if (!chunk->_meshed)
			continue ;

		chunk->upload();
		_shader->use();
		_shader->setMat4("uModel", translate(chunk->_pos * CHUNK_SIZE));
		chunk->draw(_shader);
	}
}
