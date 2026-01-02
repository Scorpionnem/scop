/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:04:06 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 17:23:07 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Math.hpp"

class	Camera
{
	public:
		Camera() : Camera(Vec3(0)) {}
		Camera(Vec3 pos)
		{
			this->pos = pos;
			front = Vec3(0.0f, 0.0f, -1.0f);
			up = Vec3(0.0f, 1.0f, 0.0f);
		}
		Mat4	getViewMatrix()
		{
			return (lookAt(pos, pos + front, up));
		}
		void	update()
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			_direction.x = cos(radians(yaw)) * cos(radians(pitch));
			_direction.y = sin(radians(pitch));
			_direction.z = sin(radians(yaw)) * cos(radians(pitch));
			front = normalize(_direction);
		}
		float	yaw = -90;
		float	pitch = 0;
		Vec3	pos;
		Vec3	front;
		Vec3	up;
	private:
		Vec3	_direction;
};
