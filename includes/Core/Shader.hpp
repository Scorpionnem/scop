/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:58:29 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 15:30:49 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include "SDL2/SDL.h"
#include <glad/glad.h>
#include <string>
#include "Math.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>

class	Shader
{
	public:
		Shader()
		{

		}

		void	use();
		void	load(GLenum type, const std::string &path);
		void	link();
		void	setFloat(const std::string &name, float val);
		void	setVec3(const std::string &name, Vec3 val);
		void	setMat4(const std::string &name, Mat4 val);
	private:
		std::string	_readShader(const std::string &path);
		uint32_t	_id = 0;
};
