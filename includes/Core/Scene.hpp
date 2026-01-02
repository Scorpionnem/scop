/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:43:28 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 17:49:10 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Window.hpp"

class	Scene
{
	public:
		virtual ~Scene() {}
		virtual void build() = 0;
		virtual void update(float delta, const Window::Events &events) = 0;
		virtual void display() = 0;
};
