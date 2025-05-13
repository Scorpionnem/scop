/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:16:19 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/12 22:14:56 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"

class Shader
{
	public:
		unsigned int	ID;

		Shader(unsigned int ID);
		Shader(const char *vertexPath, const char *fragmentPath);

		void	use();
		void	setBool(const std::string &name, bool value) const;
		void	setInt(const std::string &name, int value) const;
		void	setFloat(const std::string &name, float value) const;
		void	setMat4(const std::string &name, glm::mat4 value) const;
		void	setVec3(const std::string &name, glm::vec3 value) const;
};
