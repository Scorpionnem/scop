/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:55:06 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/12 20:55:42 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"

extern glm::vec3 pos;
extern glm::vec3 front;
extern glm::vec3 up;

extern float	deltaTime;
extern float	lastFrame;

extern float yaw;
extern float pitch;

class Camera
{
	public:
		Camera();
		void	update();
		glm::mat4	getViewMatrix();
		glm::vec3 direction;
		
};
