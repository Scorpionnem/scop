/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:38:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 15:29:03 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	Window	window;

	window.open(800, 800, "scop");

	while (window.running())
	{
		window.pollEvents();

		window.display();
	}
}
