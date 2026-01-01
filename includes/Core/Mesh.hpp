/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 22:22:50 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/01 23:42:32 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>

struct	Vec3
{
	Vec3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Vec3(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	double	x, y, z;
};

struct	Vec2
{
	Vec2()
	{
		this->x = 0;
		this->y = 0;
	}
	Vec2(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	double	x, y;
};

class	Mesh
{
	public:
		Mesh() {}
		~Mesh() {}

		void	load(const std::string &path)
		{
			std::ifstream	file(path);
			if (!file.is_open())
				throw (std::runtime_error("Failed to open " + path));

			std::cout << "Loading " << path << std::endl;

			std::string	line;
			while (std::getline(file, line))
			{
				_lineNumber++;

				line = _preprocessLine(line);
				if (line.empty())
					continue ;

				std::istringstream	iss(line);

				std::string	identifier;

				if (!(iss >> identifier))
					throw std::runtime_error("Failed to get identifier at line " + std::to_string(_lineNumber));

				if (identifier == "v")
					_positionVertices.push_back(_parseVec3(iss));
				else if (identifier == "vn")
					_normalVertices.push_back(_parseVec3(iss));
				else if (identifier == "vt")
					_textureVertices.push_back(_parseVec2(iss));
				else if (identifier == "f")
					_parseFace(iss);
				else if (identifier == "o")
				{}
			}

			std::cout << "Loaded " << path << std::endl;
		}
	private:
		struct	Face
		{
			Face() {}
			Vec3	pos1;
			Vec3	pos2;
			Vec3	pos3;
			Vec2	uv1;
			Vec2	uv2;
			Vec2	uv3;
			Vec3	normal1;
			Vec3	normal2;
			Vec3	normal3;
		};
		struct	FaceVertex
		{
			FaceVertex(int pos, int uv, int normal)
			{
				this->pos = pos;
				this->uv = uv;
				this->normal = normal;
			}
			int	pos;
			int	uv;
			int	normal;
		};
		void	_parseFace(std::istringstream &iss)
		{
			std::string	token;
			std::vector<FaceVertex>	faceVertices;

			while (iss >> token)
			{
				std::istringstream	iss2(token);

				std::string	positionStr, textureStr, normalStr;

				std::getline(iss2, positionStr, '/');
				std::getline(iss2, textureStr, '/');
				iss2 >> normalStr;

				if (positionStr.empty())
					throw std::runtime_error("No position in face at line " + std::to_string(_lineNumber));

				int	positionVert, textureVert = -1, normalVert = -1;

				try {
					positionVert = std::stoi(positionStr) - 1;
					if (!textureStr.empty())
						textureVert = std::stoi(textureStr) - 1;
					if (!normalStr.empty())
						normalVert = std::stoi(normalStr) - 1;
				} catch (const std::exception &e) {
					throw std::runtime_error("Invalid index format in face at line " + std::to_string(_lineNumber));
				}

				faceVertices.push_back(FaceVertex(positionVert, textureVert, normalVert));
			}

			if (faceVertices.size() < 3)
				throw std::runtime_error("Face with less than 3 vertices at line " + std::to_string(_lineNumber));

			for (size_t i = 1; i + 1 < faceVertices.size(); ++i)
			{
				Face	face;

				FaceVertex	fv1 = faceVertices[0];
				FaceVertex	fv2 = faceVertices[i];
				FaceVertex	fv3 = faceVertices[i + 1];

				if (fv1.pos < 0 || fv2.pos < 0 || fv3.pos < 0)
					throw std::runtime_error("Invalid pos index in face at line " + std::to_string(_lineNumber));
				if (fv1.pos > (int)_positionVertices.size() - 1 || fv2.pos > (int)_positionVertices.size() - 1, fv3.pos > (int)_positionVertices.size() - 1)
					throw std::runtime_error("Invalid pos index in face at line " + std::to_string(_lineNumber));
				face.pos1 = _positionVertices[fv1.pos];
				face.pos2 = _positionVertices[fv2.pos];
				face.pos3 = _positionVertices[fv3.pos];

				if (fv1.uv >= 0 || fv2.uv >= 0 || fv3.uv >= 0)
				{
					if (fv1.uv > (int)_textureVertices.size() - 1 || fv2.uv > (int)_textureVertices.size() - 1, fv3.uv > (int)_textureVertices.size() - 1)
						throw std::runtime_error("Invalid uv index in face at line " + std::to_string(_lineNumber));
					face.uv1 = _textureVertices[fv1.uv];
					face.uv2 = _textureVertices[fv2.uv];
					face.uv3 = _textureVertices[fv3.uv];
				}

				if (fv1.normal >= 0 || fv2.normal >= 0 || fv3.normal >= 0)
				{
					if (fv1.normal > (int)_normalVertices.size() - 1 || fv2.normal > (int)_normalVertices.size() - 1, fv3.normal > (int)_normalVertices.size() - 1)
						throw std::runtime_error("Invalid normal index in face at line " + std::to_string(_lineNumber));
					face.normal1 = _normalVertices[fv1.normal];
					face.normal2 = _normalVertices[fv2.normal];
					face.normal3 = _normalVertices[fv3.normal];
				}

				_faces.push_back(face);
			}
		}
		Vec3		_parseVec3(std::istringstream &iss)
		{
			double	x, y, z;

			if (!(iss >> x >> y >> z))
				throw std::runtime_error("Failed to get vertice at line " + std::to_string(_lineNumber));

			return (Vec3(x, y, z));
		}
		Vec2		_parseVec2(std::istringstream &iss)
		{
			double	x, y;

			if (!(iss >> x >> y))
				throw std::runtime_error("Failed to get vertice at line " + std::to_string(_lineNumber));

			return (Vec2(x, y));
		}
		std::string	_preprocessLine(const std::string &line)
		{
			std::string	res;

			res = line.substr(0, line.find('#'));
			res = res.substr(0, res.find('\r'));
			return (res);
		}

		uint32_t	_lineNumber = 0;

		std::vector<Face>	_faces;

		std::vector<Vec3>	_positionVertices;
		std::vector<Vec3>	_normalVertices;
		std::vector<Vec2>	_textureVertices;
};
