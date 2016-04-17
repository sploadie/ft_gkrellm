/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 11:22:21 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 16:49:24 by tpaulmye         ###   ########.fr       */
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
#include <algorithm>

int main (int argc, char *argv[])
{
	IMonitorDisplay* display;
	std::string default_modules;
	if (argc > 1 && std::string("-t").compare(std::string(argv[1])) == 0)	display = new TerminalDisplay();
	else														display = new GraphicDisplay();
	if (argc > 2)	default_modules = std::string(argv[2]);
	else			default_modules = "notcpurwl";
	default_modules.erase(std::unique(default_modules.begin(), default_modules.end()), default_modules.end());
	display->addModules(default_modules);
	try { display->run(); } catch(std::exception & e) { endwin(); std::cerr << "display->run() : " << e.what() << std::endl; }
	return 0;
}
