/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:10 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/27 12:01:10 by mbatty           ###   ########.fr       */
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

# include "Math.hpp"

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

#define ICON_PATH "src/assets/textures/icon.bmp"

#define BUTTON_PATH "src/assets/textures/button.bmp"
#define BUTTON_PRESSED_PATH "src/assets/textures/button_pressed.bmp"

#define SLIDER_BG_PATH "src/assets/textures/slider_background.bmp"

#define RED_BUTTON_PATH "src/assets/textures/red_button.bmp"
#define GREEN_BUTTON_PATH "src/assets/textures/green_button.bmp"
#define BLUE_BUTTON_PATH "src/assets/textures/blue_button.bmp"

#define CAMERA_BUTTON_PATH "src/assets/textures/button_toggle_camera.bmp"
#define TEXTURE_BUTTON_PATH "src/assets/textures/button_toggle_texture.bmp"

#define TERMINAL_CHAR_SIZE 15

#endif