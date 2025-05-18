/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Slider.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:04:21 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/18 13:10:10 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Slider.hpp"

GLuint sliderVAO = 0, sliderVBO = 0;

void Slider::initSliderModel()
{
    if (sliderVAO != 0) return;
    
    float vertices[] = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
		0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    glGenVertexArrays(1, &sliderVAO);
    glGenBuffers(1, &sliderVBO);

    glBindVertexArray(sliderVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sliderVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}
