/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:04:06 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 17:04:10 by mbatty           ###   ########.fr       */
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
			_front = Vec3(0.0f, 0.0f, -1.0f);
			_up = Vec3(0.0f, 1.0f, 0.0f);
		}
		Mat4	getViewMatrix()
		{
			return (lookAt(pos, pos + _front, _up));
		}
		void	update()
		{
			_direction.x = cos(radians(yaw)) * cos(radians(pitch));
			_direction.y = sin(radians(pitch));
			_direction.z = sin(radians(yaw)) * cos(radians(pitch));
			_front = normalize(_direction);
		}
		float	yaw = -90;
		float	pitch = 0;
		Vec3	pos;
	private:

		Vec3	_direction;

		Vec3	_front;
		Vec3	_up;
};
