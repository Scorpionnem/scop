/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:59:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/02 14:32:14 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cmath>
#include <algorithm>

struct	Vec3
{
	Vec3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec3(float xyz)
	{
		this->x = xyz;
		this->y = xyz;
		this->z = xyz;
	}
	Vec3 operator+(const Vec3 &v) const;
	Vec3 operator-(const Vec3 &v) const;
	Vec3 operator*(const Vec3 &v) const;
	Vec3 operator/(const Vec3 &v) const;
	bool operator>(const Vec3 &v) const;
	bool operator<(const Vec3 &v) const;
	float	x, y, z;
};

float	dot(const Vec3 &v1, const Vec3 &v2);
float	length(const Vec3 &v);
Vec3	cross(const Vec3 &v1, const Vec3 &v2);
Vec3	normalize(const Vec3 &v);

inline float smoothstep(float edge0, float edge1, float x)
{
	float t = (x - edge0) / (edge1 - edge0);
	t = std::clamp(t, 0.0f, 1.0f);
	return t * t * (3.0f - 2.0f * t);
}

inline float frac(float v)
{
	return (v - std::floor(v));
}

inline Vec3	abs(const Vec3 &v)
{
	return (Vec3(std::abs(v.x), std::abs(v.y), std::abs(v.z)));
}

inline Vec3	sin(const Vec3 &v)
{
	return (Vec3(std::sin(v.x), std::sin(v.y), std::sin(v.z)));
}

inline int	sign(float v)
{
	if (v >= 0)
		return (1);
	return (-1);
}

inline Vec3	sign(const Vec3 &v)
{
	return (Vec3(sign(v.x), sign(v.y), sign(v.z)));
}

inline float	dist(Vec3 p1, Vec3 p2)
{
	return (length(p1 - p2));
}
