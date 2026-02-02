/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderScene.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:48:09 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 16:26:07 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Scene.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Engine.hpp"
#include "LightCache.hpp"

class	RenderScene : public Scene
{
	public:
		RenderScene(const Engine &engine, const std::string &model) : Scene(engine) {_modelPath = model;}
		~RenderScene() {}
		void	build();
		void	update(float delta, const Window::Events &events);
		void	display();
	private:
		void	_updateCamera(float delta, const Window::Events &events);

		std::string	_modelPath;

		Mat4	_model;

		std::shared_ptr<Shader>	_shader;
		std::shared_ptr<Mesh>	_mesh;
		Camera	_camera;
};
