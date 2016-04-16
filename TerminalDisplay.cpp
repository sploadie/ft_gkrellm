/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalDisplay.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:31:06 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 16:02:45 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TerminalDisplay.hpp"

TerminalDisplay::TerminalDisplay( void ) {
	setlocale(LC_ALL,"");
	// Initialisation
	initscr();
	// Clear screen
	clear();
	// User input not displayed
	noecho();
	// User input does not require newline
	cbreak();
	// Special user input does not generate a signal and is passed to program instead
	raw();
	// getch does not wait for user input
	nodelay(stdscr, TRUE);
	// Preparing the keypad and cursor
	keypad(stdscr, TRUE);
	curs_set(0);
	// Initialising colors we will use
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_BLACK);
}

TerminalDisplay::TerminalDisplay( TerminalDisplay const & obj ) { *this = obj; }

TerminalDisplay::~TerminalDisplay( void ) {
	for (std::map<char,IMonitorModule*>::iterator it=this->_modules.begin(); it!=this->_modules.end(); ++it)
		delete it->second;
	endwin();
	return;
}

TerminalDisplay & TerminalDisplay::operator=( TerminalDisplay const & rhs ) {
	// Delete Modules
	// Clone Modules
	return *this;
}

int TerminalDisplay::run( void ) {
	time_t last_time = time(NULL);
	while (42) {
		if (time(NULL) == last_time) continue;
		last_time = time(NULL);
		// Display
		// Listen to User Input
		// Refresh Modules
		// Determine # of modules not hidden
	}
	return 0;
}

void TerminalDisplay::addModules(std::string modules) {
	// Add modules (use case)
}
