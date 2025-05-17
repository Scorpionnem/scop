/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:04:30 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/17 15:25:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"
#include "Shader.hpp"

static GLuint buttonVAO = 0, buttonVBO = 0;

class   Button
{
    public:
    Button(float width, float height, glm::vec2 pos, std::function<void()> function)
    {
        this->pos = pos;
        this->width = width;
        this->height = height;
        onClick = function;
    }
    void draw(Shader& shader)
    {
        initButtonModel();
        shader.use();
        
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
        model = glm::scale(model, glm::vec3(width, height, 1.0f));
        
        shader.setMat4("model", model);
        shader.setVec3("color", glm::vec3(1.0, 0.0, 0.0));
        
        glBindVertexArray(buttonVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
    void initButtonModel()
    {
        if (buttonVAO != 0) return;
        
        float vertices[] = {
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
    		0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f
        };
    
        glGenVertexArrays(1, &buttonVAO);
        glGenBuffers(1, &buttonVBO);
    
        glBindVertexArray(buttonVAO);
        glBindBuffer(GL_ARRAY_BUFFER, buttonVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    
        glBindVertexArray(0);
    }
    float       width;
    float       height;
    glm::vec2   pos;
    std::function<void()>   onClick;
    private:
};
