/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:13:53 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 13:55:47 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>

struct Mat4
{
	double	data[16];

	Mat4(double val)
	{
		std::fill(data, data + 16, 0.0f);
		this->data[0] = this->data[5] = this->data[10] = this->data[15] = val;
	}
	Mat4(const Mat4 &cpy)
	{
		*this = cpy;
	}
	Mat4 &operator=(const Mat4 &cpy)
	{
		for (int i = 0; i < 16; i++)
			this->data[i] = cpy.data[i];
		return (*this);
	}
};
