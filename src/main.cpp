/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:38:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 00:08:14 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include "Mesh.hpp"

int	main(int ac, char **av)
{
	// Window	window;

	// window.open(800, 800, "scop");
	// while (window.running())
	// {
	// 	window.pollEvents();
	// 	window.display();
	// }
	// window.close();

	if (ac < 2)
		return (1);

	while (*(++av))
	{
		try {
			Mesh	mesh;

			mesh.load(*av);
		} catch (const std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
			continue ;
		}
	}
	return (0);
}
