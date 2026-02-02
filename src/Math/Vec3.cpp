/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:07:20 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/02 14:08:51 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec3.hpp"
#include <cmath>

Vec3 Vec3::operator+(const Vec3 &v) const
{
	return (Vec3(x + v.x, y + v.y, z + v.z));
}

Vec3 Vec3::operator-(const Vec3 &v) const
{
	return (Vec3(x - v.x, y - v.y, z - v.z));
}

Vec3 Vec3::operator*(const Vec3 &v) const
{
	return (Vec3(x * v.x, y * v.y, z * v.z));
}

Vec3 Vec3::operator/(const Vec3 &v) const
{
	return (Vec3(x / v.x, y / v.y, z / v.z));
}

float	dot(const Vec3 &v1, const Vec3 &v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	length(const Vec3 &v)
{
	return (std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

Vec3	cross(const Vec3 &v1, const Vec3 &v2)
{
	return (Vec3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	));
}

Vec3	normalize(const Vec3 &v)
{
	float	len = length(v);
	return (len > 0.0f ? v / len : Vec3(0));
}
