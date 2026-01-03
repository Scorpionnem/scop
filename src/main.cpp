/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:38:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 12:23:06 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"
#include "RenderScene.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	Engine	engine;

	engine.start(std::make_unique<RenderScene>(engine, av[1]));
}
