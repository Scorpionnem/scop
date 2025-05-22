/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:10 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/22 16:28:50 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_HPP
# define LIBS_HPP

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <istream>
# include <vector>
# include <map>
# include <cmath>
# include <unistd.h>
# include <exception>
# include <functional>
# include <array>

# include "glad.h"
# include "glfw3.h"

# include "glm.hpp"
# include "gtc/matrix_transform.hpp"
# include "gtc/type_ptr.hpp"

# include "stb_image.h"

# define WIN_NAME "scop"
extern float	SCREEN_WIDTH;
extern float	SCREEN_HEIGHT;
extern float	FOV;
extern float	RENDER_DISTANCE;
extern unsigned int	TOTAL_VERTICES;
extern unsigned int	TOTAL_FACES;
extern glm::vec3	mesh_pos;
extern bool	rainbow;

extern bool	F1;
extern bool	F3;

#define TERMINAL_CHAR_SIZE 15

#endif