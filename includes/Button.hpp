/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:04:30 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/18 13:09:38 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"
#include "Shader.hpp"

extern GLuint buttonVAO;
extern GLuint buttonVBO;

bool isInside(glm::vec2 buttonPos, glm::vec2 mousePos, float width, float height);

class   Button
{
    public:
        Button(float width, float height, glm::vec2 pos, std::function<void()> function, Texture &texture, Texture &pressedTexture);
        void draw(Shader& shader);
        void initButtonModel();
        void    checkClick(glm::vec2 mousePos, bool mousePressed);
        
        float       width;
        float       height;
        glm::vec2   pos;
        std::function<void()>   onClick;
        Texture &texture;
        Texture &pressedTexture;
        float   wasPressedInside = false;
    private:
};
