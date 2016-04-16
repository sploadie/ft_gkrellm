/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalDisplay.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:31:06 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 19:33:37 by tgauvrit         ###   ########.fr       */
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
TerminalDisplay & TerminalDisplay::operator=( TerminalDisplay const & rhs ) { static_cast<void>(rhs); return *this; }

TerminalDisplay::~TerminalDisplay( void ) {
	for (std::map<char,IMonitorModule*>::iterator it=this->_modules.begin(); it!=this->_modules.end(); ++it)
		delete it->second;
	endwin();
	return;
}

void TerminalDisplay::refresh( void ) {
	for (std::map<char,IMonitorModule*>::iterator it=this->_modules.begin(); it!=this->_modules.end(); ++it)
		it->second->refresh();
}

int TerminalDisplay::run( void ) {
	time_t last_time = time(NULL);
	int	columns_remaining;
	std::map<char,IMonitorModule*>::iterator it;
	while (42) {
		if (time(NULL) == last_time) continue;
		last_time = time(NULL);
		columns_remaining = COLS;
		for (it=this->_modules.begin(); it!=this->_modules.end(); ++it) {
			if (it->second != NULL) {
				if (it->second->isHidden()) continue;
				columns_remaining -= it->second->toTerminal(COLS - columns_remaining, columns_remaining);
				if (columns_remaining > 0) {
					move(COLS - columns_remaining, 0);
					hline('=', COLS);
					--columns_remaining;
				}
			}
		}
		// Listen to User Input
		this->refresh();
		// Determine # of modules not hidden
	}
	return 0;
}

void TerminalDisplay::addModules(std::string modules) {
	for (std::string::iterator it = modules.begin(); it != modules.end(); ++it) {
		switch (*it) {
			case 'n':
				if (this->_modules.find('n') == this->_modules.end()) this->_modules['n'] = new NameModule(false);
				break;
			default:
				std::cerr << "No valid Module '" << *it << "' found." << std::endl;
		}
	}
}
