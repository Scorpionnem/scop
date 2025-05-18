/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Slider.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:25:11 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/18 15:16:05 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Button.hpp"

extern GLuint sliderVAO;
extern GLuint sliderVBO;

class Slider
{
    public:
        Slider(float width, float height, glm::vec2 pos, Texture &sliderTexture, Texture &sliderPressedTexture, Texture &backgroundTexture)
        : backgroundTexture(backgroundTexture), sliderTexture(sliderTexture), sliderPressedTexture(sliderPressedTexture)
        {
            this->pos = pos;
            this->width = width;
            this->height = height;

            this->sliderWidth = width / 4;
            this->sliderHeight = height;
            this->sliderPos = glm::vec2(pos.x + width / 2, pos.y);
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
            initSliderModel();
            shader.use();
            if (isSliderClicked)
                sliderPressedTexture.use();
            else
                sliderTexture.use();

            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(sliderPos.x, sliderPos.y, 0.0f));
            model = glm::scale(model, glm::vec3(sliderWidth, sliderHeight, 1.0f));
                
            shader.setMat4("model", model);
                
            glBindVertexArray(sliderVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
        void    checkClick(glm::vec2 mousePos, bool mousePressed)
        {
            bool inside = isInside(this->pos, mousePos, this->width, this->height);
            
            isSliderClicked = false;
            if (inside && mousePressed)
            {
                sliderPos.x = mousePos.x - (sliderWidth / 2);
                isSliderClicked = true;
            }
            if (sliderPos.x > pos.x + width - (sliderWidth))
                sliderPos.x = pos.x + width - (sliderWidth);
            if (sliderPos.x < pos.x)
                sliderPos.x = pos.x;

            float sliderCenter = sliderPos.x + sliderWidth * 0.5f;
            value = (sliderCenter - pos.x) / width;
        }
        void    setSlider(float value)
        {
            sliderPos.x = pos.x + value * width - sliderWidth * 0.5f;
        }

        void initSliderModel();

        Texture &backgroundTexture;
        Texture &sliderTexture;
        Texture &sliderPressedTexture;

        float   width;
        float   height;
        
        float   sliderWidth;
        float   sliderHeight;
        bool    isSliderClicked = false;
        float   value = 0;
        glm::vec2   pos;
        glm::vec2   sliderPos;
};
