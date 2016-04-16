/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 11:22:21 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 18:49:17 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IMonitorDisplay.hpp"
#include "TerminalDisplay.hpp"
#include "GraphicDisplay.hpp"
#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <signal.h>

int main (int argc, char *argv[])
{
	IMonitorDisplay* display;
	std::string default_modules;
	if (argc > 1 && std::string("-t").compare(argv[1]) == 0)	display = new TerminalDisplay();
	else														display = new GraphicDisplay(argc, argv);
	if (argc > 2)	default_modules = argv[2];
	else			default_modules = "n";
	display->addModules(default_modules);
	return display->run();
}
