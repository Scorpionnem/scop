/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:38:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/01 23:26:06 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include "Mesh.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	// Window	window;

	// window.open(200, 200, "scop");
	// while (window.running())
	// {
	// 	window.pollEvents();
	// 	window.display();
	// }

	Mesh	mesh;

	try {
		mesh.load(av[1]);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
