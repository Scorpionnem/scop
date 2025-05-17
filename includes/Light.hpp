/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:41:21 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/17 11:51:13 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class	Light
{
	public:
		Light();
		glm::vec3	pos;
		glm::vec3	color;
		Mesh		mesh;
		void	update(Shader &shader);
		void	draw(Shader &shader, Camera &camera);
};
