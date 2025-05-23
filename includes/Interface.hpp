/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interface.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:21:35 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/23 16:23:45 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_HPP
# define INTERFACE_HPP

# include "Slider.hpp"

class	Interface
{
	public:
		Interface(){}
		void	update(GLFWwindow *window, Shader &guiShader, Font &font, Shader &textShader)
		{
			double mouseX, mouseY;
			bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
				
			glfwGetCursorPos(window, &mouseX, &mouseY);
		
			guiShader.use();
			glm::mat4 projection = glm::ortho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			guiShader.setMat4("projection", projection);
				
			for (std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); it++)
			{
				it->texture.use();
				it->checkClick(glm::vec2(mouseX, mouseY), mousePressed);
				it->draw(guiShader, font, textShader);
			}
			for (std::vector<Slider>::iterator it = sliders.begin(); it != sliders.end(); it++)
			{
				it->checkClick(glm::vec2(mouseX, mouseY), mousePressed);
				it->drawBackground(guiShader);
				it->drawSlider(guiShader);
				it->drawStr(font, textShader);
			}
		}
		std::vector<Slider>	sliders;
		std::vector<Button>	buttons;
};

#endif