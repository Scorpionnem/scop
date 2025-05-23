/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Font.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:45:03 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/23 16:25:59 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_HPP
# define FONT_HPP

# include "libs.hpp"
# include "Shader.hpp"
# include "Texture.hpp"

extern GLuint fontVAO;
extern GLuint fontVBO;

class	Font
{
	public:
		Font()
		{
			std::ifstream	tmpFile;
			for (unsigned char c = 33; c < 128; ++c)
			{
				std::string path = "src/assets/textures/font/" + std::string(1, c) + ".png";
				tmpFile.open(path);
				if (tmpFile.is_open())
				{
					Texture	tmp(path.c_str());
					font[c].cut(tmp);
				}
				tmpFile.close();
			}
			Texture	tmp("src/assets/textures/font/?.png");
			font[127].cut(tmp);
		}
		Texture& operator[](char c)
		{
			if (c < 0 || c > 127 || font[c].ID <= 0)
				return (font[127]);
			return (font[c]);
		}
		Texture& getChar(char c)
		{
			if (c < 0 || c > 127 || font[c].ID <= 0)
				return (font[127]);
			return (font[c]);
		}
		void	initFontModel()
		{
		    if (fontVAO != 0) return;
				
		    float vertices[] = {
		        0.0f, 0.0f,
		        1.0f, 1.0f,
		        0.0f, 1.0f,
				0.0f, 0.0f,
		        1.0f, 0.0f,
		        1.0f, 1.0f
		    };
		
		    glGenVertexArrays(1, &fontVAO);
		    glGenBuffers(1, &fontVBO);
		
		    glBindVertexArray(fontVAO);
		    glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
		    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		    glEnableVertexAttribArray(0);
		    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		
		    glBindVertexArray(0);
		}
		void    putChar(char c, Shader &shader, glm::vec2 pos, glm::vec2 size)
        {
			if (c == ' ')
				return ;
            initFontModel();
            shader.use();
			getChar(c).use();
			

            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
            model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
			glm::mat4 projection = glm::ortho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			shader.setMat4("projection", projection);

            shader.setMat4("model", model);

			glDisable(GL_DEPTH_TEST);
            glBindVertexArray(fontVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
			glEnable(GL_DEPTH_TEST);
        }
		void	putString(std::string str, Shader &shader, glm::vec2 pos, glm::vec2 size)
		{
			float	offset = size.x / str.size();
			float	charPos = pos.x;
			for (std::string::iterator it = str.begin(); it != str.end(); it++)
			{
				putChar(*it, shader, glm::vec2(charPos, pos.y), glm::vec2(offset, size.y));
				charPos += offset;
			}
		}
		std::array<Texture, 128> font;	
};

#endif