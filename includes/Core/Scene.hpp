/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:43:28 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 20:10:20 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Window.hpp"

class Engine;

class	Scene
{
	public:
		Scene(const Engine &engine) : _engine(engine) {}
		virtual ~Scene() {}
		virtual void build() = 0;
		virtual void update(float delta, const Window::Events &events) = 0;
		virtual void display() = 0;

		bool	requestedStop()
		{
			return (_stopRequest);
		}
	protected:
		void	requestStop()
		{
			_stopRequest = true;
		}
		const Engine &_engine;
	private:
		bool	_stopRequest = false;
};
