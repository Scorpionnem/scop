/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:10 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/28 12:53:23 by mbatty           ###   ########.fr       */
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
#include <algorithm>

# include "vec2.hpp"
# include "vec3.hpp"
# include "vec4.hpp"
# include "mat4.hpp"

# include "strings.hpp"

# include "glad.h"
# include "glfw3.h"

std::string	toString(int nbr);

# define WIN_NAME "scop"

extern float	SCREEN_WIDTH;
extern float	SCREEN_HEIGHT;
extern float	FOV;
extern float	RENDER_DISTANCE;
extern unsigned int	TOTAL_VERTICES;
extern unsigned int	TOTAL_TRIANGLES;
extern vec3	mesh_pos;
extern bool	rainbow;

extern bool	F1;
extern bool	F3;

extern bool	mesh_spin;

# define TERMINAL_CHAR_SIZE 15

inline float   clamp(float val, float min, float max)
{
    float   res = val;
    if (res < min)
        res = min;
    else if (res > max)
        res = max;
    return (res);
}

inline float   toRadians(float deg)
{
    return(deg * M_PI / 180.0f);
}

#endif