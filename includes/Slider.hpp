/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Slider.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:25:11 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/21 22:43:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLIDER_HPP
# define SLIDER_HPP

# include "Button.hpp"

extern GLuint sliderVAO;
extern GLuint sliderVBO;

class Slider
{
    public:
        Slider(std::string str, float width, float height, glm::vec2 pos, Texture &sliderTexture, Texture &sliderPressedTexture, Texture &backgroundTexture)
        : backgroundTexture(backgroundTexture), sliderTexture(sliderTexture), sliderPressedTexture(sliderPressedTexture)
        {
            this->str = str;
            this->pos = pos;
            this->width = width;
            this->height = height;

            this->sliderWidth = width / 4;
            this->sliderHeight = height;
            this->sliderPos = glm::vec2(pos.x + width / 2, pos.y);
            this->minCenter = pos.x + sliderWidth * 0.5f;
            this->maxCenter = pos.x + width - sliderWidth * 0.5f;
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
                
			glDisable(GL_DEPTH_TEST);
            glBindVertexArray(sliderVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
			glEnable(GL_DEPTH_TEST);
        }
        void    drawStr(Font &font, Shader &textShader)
        {
            font.putString(this->str, textShader, glm::vec2(this->pos.x, this->pos.y - height / 8), glm::vec2(width, height));
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

            float sliderCenter = sliderPos.x + (sliderWidth / 2);
            float normalizedValue = (sliderCenter - minCenter) / (maxCenter - minCenter);
            normalizedValue = glm::clamp(normalizedValue, 0.0f, 1.0f);
                    
            value = normalizedValue;
        }
        void    setSlider(float value)
        {
            value = glm::clamp(value, 0.0f, 1.0f);
            this->value = value;
            
            float minCenter = pos.x + (sliderWidth / 2);
            float maxCenter = pos.x + width - (sliderWidth / 2);
            float centerX = minCenter + value * (maxCenter - minCenter);
        
            sliderPos.x = centerX - (sliderWidth / 2);
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
        float   minCenter;
        float   maxCenter;
        glm::vec2   pos;
        glm::vec2   sliderPos;
        std::string str;
};

#endif