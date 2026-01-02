/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec2.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:59:53 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 13:13:41 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

struct	Vec2
{
	Vec2()
	{
		this->x = 0;
		this->y = 0;
	}
	Vec2(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	Vec2(double xy)
	{
		this->x = xy;
		this->y = xy;
	}
	double	x, y;
};
