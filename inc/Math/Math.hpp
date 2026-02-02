/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:00:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/02 14:09:42 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Vec3.hpp"
#include "Vec2.hpp"
#include "Mat4.hpp"
#include <cmath>

// Vec2

inline Mat4 rotate(Mat4 &mat, float angleRad, const Vec3 &axis)
{
	return (mat * rotate(angleRad, axis));
}

inline float radians(float deg)
{
	return (deg * M_PI / 180.0f);
}

