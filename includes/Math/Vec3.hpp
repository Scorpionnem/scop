/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:59:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 20:37:29 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>

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

	uint64_t	hash()
	{
		const uint64_t BITS = 21;
		const uint64_t MASK = (1ULL << BITS) - 1;
		const int64_t  BIAS = 1LL << (BITS - 1);

		int	x = this->x;
		int	y = this->y;
		int	z = this->z;

		uint64_t ux = uint64_t(int64_t(x) + BIAS) & MASK;
		uint64_t uy = uint64_t(int64_t(y) + BIAS) & MASK;
		uint64_t uz = uint64_t(int64_t(z) + BIAS) & MASK;

		return (ux << (BITS * 2)) | (uy << (BITS * 1)) | (uz << (BITS * 0));
	}

	Vec3 operator+(const Vec3 &v) const;
	Vec3 operator-(const Vec3 &v) const;
	Vec3 operator*(const Vec3 &v) const;
	Vec3 operator/(const Vec3 &v) const;
	float	x, y, z;
};
