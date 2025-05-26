/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:49:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/26 14:03:48 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Texture.hpp"

Texture::~Texture()
{
	if (ID > 0)
		glDeleteTextures(1, &ID);
}

// #define FILE_HEADER_SIZE 14
// #define INFORMATION_HEADER_SIZE 40

class	Color
{
	public:
		float r, g, b;
	
		Color()
		{
			this->r = 0;
			this->g = 0;
			this->b = 0;
		}
		Color(float r, float g, float b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		}
};

typedef struct s_bmp_header
{
	uint16_t	magic;
	uint32_t	size;
	uint32_t	reserved;
	uint32_t	data_offset;
	uint32_t	dib_size;
	uint16_t	dib_width;
	uint16_t	dib_height;
	uint16_t	dib_cp;
	uint16_t	dib_bpp;

	uint32_t	data_size;
} __attribute__((packed))	bmp_header;

# define BMP_MAGIC		0x4D42
# define HEADER_SIZE	26
# define MAX_SIZE		0x5F5E11A

# define ERR_OPEN_FAILED		"Open failed."
# define ERR_READ_FAILED		"Read failed."
# define ERR_INVALID_MAGIC		"Invalid magic."
# define ERR_BMP_TOO_SMALL		"Image too small"
# define ERR_INVALID_SIZE		"Promised size vs actual size mismatch \
or read error."
# define ERR_INVALID_OFFSET		"Invalid data offset."
# define ERR_INVALID_DIB		"Only BITMAPCOREHEADER DIB header is supported."
# define ERR_INVALID_BPP		"Only 24 BPP is supported."
# define ERR_SIZE_OOB			"Image size too big or too small"
# define ERR_INVALID_RATIO		"Image size is invalid"
# define ERR_INVALID_CP			"Color plane value must be 1."

void	check_header(bmp_header *header)
{
	uint64_t	expected_size;

	if (header->magic != BMP_MAGIC)
		throw std::runtime_error(std::string("Invalid texture format"));
	if (header->size <= HEADER_SIZE || header->size > MAX_SIZE)
		throw std::runtime_error(std::string("Invalid texture format"));
	if (header->data_offset != HEADER_SIZE)
		throw std::runtime_error(std::string("Invalid texture format"));
	if (header->dib_size != 12)
		throw std::runtime_error(std::string("Invalid texture format"));
	header->data_size = header->size - HEADER_SIZE;
	if (header->dib_width < 5 || header->dib_height < 5)
		throw std::runtime_error(std::string("Invalid texture format"));
	expected_size = 3 * (header->dib_height
			* (header->dib_width + header->dib_width % 4));
	if (header->data_size != expected_size)
		throw std::runtime_error(std::string("Invalid texture format"));
	if (header->dib_bpp != 24)
		throw std::runtime_error(std::string("Invalid texture format"));
	if (header->dib_cp != 1)
		throw std::runtime_error(std::string("Invalid texture format"));
}

std::vector<unsigned char>	Texture::LoadImage(const char *path)
{
	std::ifstream	file;
	bmp_header informationHeader;
	std::vector<unsigned char>	pixels;

	file.open(path);
	if (!file.is_open())
		throw std::runtime_error(std::string("Failed to open ") + path);

	file.read((char*)&informationHeader, 26);
	check_header(&informationHeader);
	
	width = informationHeader.dib_width;
	height = informationHeader.dib_height;
	
	pixels.resize((width * height) * 4);
	
	for (int y = 0; y < height * 4; y += 4)
	{
		for (int x = 0; x < width * 4; x += 4)
		{
			char	color[3];
			file.read(color, 3);

			pixels[(y * width + x)] = color[2];
			pixels[(y * width + x) + 1] = color[1];
			pixels[(y * width + x) + 2] = color[0];
			pixels[(y * width + x) + 3] = 255;
		}
	}
	file.close();
	return (pixels);
}

Texture::Texture(const char *path)
{
	data = LoadImage(path);
	glGenTextures(1, &this->ID);
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	glGenerateMipmap(GL_TEXTURE_2D);
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
