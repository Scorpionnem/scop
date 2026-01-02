/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:00:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 13:13:47 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Vec3.hpp"
#include "Vec2.hpp"
#include <cmath>

// Vec3

double	dot(const Vec3 &v1, const Vec3 &v2);
double	length(const Vec3 &v);
Vec3	cross(const Vec3 &v1, const Vec3 &v2);
Vec3	normalize(const Vec3 &v);

// Vec2

