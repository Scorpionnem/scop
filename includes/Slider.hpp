/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Slider.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:25:11 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/18 13:51:33 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Button.hpp"

extern GLuint sliderVAO;
extern GLuint sliderVBO;

class Slider
{
    public:
        Slider(float width, float height, glm::vec2 pos, std::function<void()> function, Texture &sliderTexture, Texture &sliderPressedTexture, Texture &backgroundTexture)
        :
        slider(width / 4, height, glm::vec2(pos.x + width / 2, pos.y), function, sliderTexture, sliderTexture),
        background(width, height, pos, function, sliderTexture, sliderTexture),
        backgroundTexture(backgroundTexture), sliderTexture(sliderTexture), sliderPressedTexture(sliderPressedTexture)
        {
            this->pos = pos;
            this->width = width;
            this->height = height;
            setSlider(0.5);
        }
        void    drawBackground(Shader &shader)
        {
            initSliderModel();
            shader.use();
            backgroundTexture.use();

            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
            model = glm::scale(model, glm::vec3(width, height, 1.0f));
                
            shader.setMat4("model", model);
                
            glBindVertexArray(sliderVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
        void    drawSlider(Shader &shader)
        {
            if (isSliderClicked)
                sliderPressedTexture.use();
            else
                sliderTexture.use();
            slider.draw(shader);
        }
        void    checkClick(glm::vec2 mousePos, bool mousePressed)
        {
            bool inside = isInside(this->pos, mousePos, this->width, this->height);
            
            isSliderClicked = false;
            if (inside && mousePressed)
            {
                slider.pos.x = mousePos.x - (slider.width / 2);
                isSliderClicked = true;
            }
            if (slider.pos.x > pos.x + width - (slider.width))
                slider.pos.x = pos.x + width - (slider.width);
            if (slider.pos.x < pos.x)
                slider.pos.x = pos.x;

            float sliderCenter = slider.pos.x + slider.width * 0.5f;
            value = (sliderCenter - pos.x) / width;
        }
        void    setSlider(float value)
        {
            slider.pos.x = pos.x + value * width - slider.width * 0.5f;
        }

        void initSliderModel();

        Button  slider;
        Button  background;

        float   width;
        float   height;
        Texture &backgroundTexture;
        Texture &sliderTexture;
        Texture &sliderPressedTexture;
        bool    isSliderClicked = false;

        float   value = 0;

        glm::vec2   pos;
};
