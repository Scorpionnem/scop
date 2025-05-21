/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:41:21 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/21 21:32:15 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_HPP
# define LIGHT_HPP

# include "libs.hpp"
# include "Mesh.hpp"
# include "Shader.hpp"
# include "Camera.hpp"

class	Light
{
	public:
		Light();
		glm::vec3	pos;
		glm::vec3	color;
		Mesh		mesh;
		void	update(Shader &shader);
		void	draw(Shader &shader, Camera &camera);
};

#endif