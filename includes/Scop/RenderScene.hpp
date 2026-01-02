/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderScene.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:48:09 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 18:00:56 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Scene.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class	RenderScene : public Scene
{
	public:
		RenderScene(const std::string &model) {_modelPath = model;}
		~RenderScene() {}
		void	build();
		void	update(float delta, const Window::Events &events);
		void	display();
	private:
		std::string	_modelPath;

		Mat4	_model;

		Shader	_shader;
		Mesh	_mesh;
		Camera	_camera;
};
