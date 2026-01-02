/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:38:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 17:04:29 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class	Scene
{
	public:
		virtual ~Scene() {}
		virtual void build() = 0;
		virtual void update() = 0;
		virtual void display() = 0;
};

class	RenderScene : public Scene
{
	public:
		RenderScene() {}
		~RenderScene() {}
		void build()
		{
			_mesh.load("models/vroom.obj");
			_mesh.upload();

			_camera.pos = Vec3(0, 2, 5);
			_camera.pitch = -20;

			_shader.load(GL_VERTEX_SHADER, "assets/shaders/mesh.vs");
			_shader.load(GL_FRAGMENT_SHADER, "assets/shaders/mesh.fs");
			_shader.link();

			_model = Mat4(1);
		}
		void update()
		{
			_camera.update();
		}
		void display()
		{
			Mat4	projection = perspective(70, 1, 0.01, 100);

			_shader.use();
			_shader.setMat4("uModel", _model);
			_shader.setMat4("uView", _camera.getViewMatrix());
			_shader.setMat4("uProjection", projection);

			_mesh.draw();
		}
	private:
		Mat4	_model;

		Shader	_shader;
		Mesh	_mesh;
		Camera	_camera;
};

class	Engine
{
	public:
		void	start()
		{
			_window.open(800, 800, "scop");

			_scene = new RenderScene();
			_scene->build();
			_loop();
		}
	private:
		void	_loop()
		{
			while (_window.running())
			{
				_window.pollEvents();

				if (_scene)
				{
					_scene->update();
					_scene->display();
				}

				_window.display();
			}
		}
		Scene	*_scene;
		Window	_window;
};

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	Engine	engine;

	engine.start();
}
