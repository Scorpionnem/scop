/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:21:13 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/22 16:24:10 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Button.hpp"

GLuint buttonVAO = 0, buttonVBO = 0;

bool isInside(glm::vec2 buttonPos, glm::vec2 mousePos, float width, float height)
{
    return mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + width && mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + height;
}

Button::Button(std::string str, float width, float height, glm::vec2 pos, std::function<void()> function, Texture &texture, Texture &pressedTexture)
: texture(texture), pressedTexture(pressedTexture)
{
    this->pos = pos;
    this->width = width;
    this->height = height;
    onClick = function;
    this->str = str;
}

void Button::draw(Shader& shader, Font &font, Shader &textShader)
{
    initButtonModel();
    shader.use();
    
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));
    
    shader.setMat4("model", model);
    
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(buttonVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    font.putString(this->str, textShader, glm::vec2(this->pos.x, this->pos.y - height / 8), glm::vec2(width, height));
    glEnable(GL_DEPTH_TEST);
}

void    Button::checkClick(glm::vec2 mousePos, bool mousePressed)
{
    bool inside = isInside(this->pos, mousePos, this->width, this->height);
    
    if (mousePressed)
    {
    	wasPressedInside = inside;
    	if (inside)
    		this->pressedTexture.use();
    }
    else
    {
    	if (wasPressedInside && inside)
    		this->onClick();
    	wasPressedInside = false;
    }
}

void Button::initButtonModel()
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
