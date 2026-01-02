/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:59:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 13:13:43 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

struct	Vec3
{
	Vec3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Vec3(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec3(double xyz)
	{
		this->x = xyz;
		this->y = xyz;
		this->z = xyz;
	}
	Vec3 operator+(const Vec3 &v) const;
	Vec3 operator-(const Vec3 &v) const;
	Vec3 operator*(const Vec3 &v) const;
	Vec3 operator/(const Vec3 &v) const;
	double	x, y, z;
};
