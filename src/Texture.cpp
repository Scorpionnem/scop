/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:49:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/21 14:22:34 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Texture.hpp"

Texture::~Texture()
{
	if (ID > 0)
		glDeleteTextures(1, &ID);
}

Texture::Texture(const char *path)
{
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path, &this->width, &this->height, &this->nrChannels, 4);
	if (!data)
		throw std::runtime_error("Failed to load image");
	glGenTextures(1, &this->ID);
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	Texture::use(void)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

void	Texture::reset(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
