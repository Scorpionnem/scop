/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:38:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 17:41:06 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include <ctime>

class	Scene
{
	public:
		virtual ~Scene() {}
		virtual void build() = 0;
		virtual void update(float delta, const Window::Events &events) = 0;
		virtual void display() = 0;
};

class	RenderScene : public Scene
{
	public:
		RenderScene(const std::string &model) {_modelPath = model;}
		~RenderScene() {}
		void build()
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
		void update(float delta, const Window::Events &events)
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
		void display()
		{
			Mat4	projection = perspective(70, 1, 0.01, 1000);

			_shader.use();
			_shader.setMat4("uModel", _model);
			_shader.setMat4("uView", _camera.getViewMatrix());
			_shader.setMat4("uProjection", projection);

			_mesh.draw();
		}
	private:
		std::string	_modelPath;

		Mat4	_model;

		Shader	_shader;
		Mesh	_mesh;
		Camera	_camera;
};

class	Engine
{
	public:
		void	start(Scene *scene)
		{
			clock_gettime(CLOCK_MONOTONIC, &_lastFrame);

			_window.open(800, 800, "scop");

			_scene = scene;
			_scene->build();
			_loop();
		}
	private:
		void	_loop()
		{
			while (_window.running())
			{
				struct timespec	currentFrame;
				double			deltaTime;

				clock_gettime(CLOCK_MONOTONIC, &currentFrame);
				deltaTime = (currentFrame.tv_sec - _lastFrame.tv_sec) + (currentFrame.tv_nsec - _lastFrame.tv_nsec) * 1e-9;
				_lastFrame = currentFrame;

				_window.pollEvents();

				_window.setMousePos(400, 400);

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

		struct timespec	_lastFrame = {0, 0};
};

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	Engine	engine;

	engine.start(new RenderScene(av[1]));
}
