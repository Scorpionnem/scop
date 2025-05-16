/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:48:51 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/16 20:29:43 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"

class	Texture
{
	public:
		Texture();
		int	load(const char *path);
		void	use(void);
		static void	reset(void);
		unsigned int	ID;
	private:
		unsigned char	*data;
		int	width;
		int	height;
		int	nrChannels;
};
