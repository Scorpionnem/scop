/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:11:18 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/03 16:49:53 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"

class	Window
{
	public:
		Window();
		~Window();
		bool	up(void);
		GLFWwindow	*getWindowData(void);
		void		loopStart(void);
		void		loopEnd(void);
		void		setIcon(const char *path);
		void		center();
	private:
		GLFWwindow	*_windowData;
		float		_deltaTime;
		float		_lastFrame;
		float		_currentFrame;
		void 		displayFPS();
};
