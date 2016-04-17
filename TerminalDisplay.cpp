/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalDisplay.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:31:06 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 13:58:26 by tpaulmye         ###   ########.fr       */
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

	this->_types = "";
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
	std::string::iterator it;
	char ch;
	while (42) {
		if (time(NULL) == last_time) continue;
		last_time = time(NULL);
		columns_remaining = COLS;
		// try {
		for (it=this->_types.begin(); it!=this->_types.end(); ++it) {
			if (this->_modules[*it] != NULL) {
				if (this->_modules[*it]->isHidden()) continue;
				// try { columns_remaining -= this->_modules[*it]->toTerminal(COLS - columns_remaining, columns_remaining); } catch(std::exception & e) { endwin(); std::cerr << "this->_modules[*]->toTerminal : " << e.what() << std::endl; }
				columns_remaining -= this->_modules[*it]->toTerminal(COLS - columns_remaining, columns_remaining);
				if (columns_remaining > 0) {
					move(COLS - columns_remaining, 0);
					hline('=', COLS);
					--columns_remaining;
				}
			}
		}
		// } catch(std::exception & e) { endwin(); std::cerr << "for (it=this->_modules.begin(); : " << e.what() << std::endl; }
		ch = getch();
		if (ch == 'q' || ch == 'Q') {
			endwin();
 			break;
 		}
		// try { this->refresh(); } catch(std::exception & e) { endwin(); std::cerr << "this->refresh(); : " << e.what() << std::endl; }
		this->refresh();
		// Determine # of modules not hidden
	}
	return 0;
}

void TerminalDisplay::addModules(std::string modules) {
	for (std::string::iterator it = modules.begin(); it != modules.end(); ++it) {
		switch (*it) {
			case 'n':
				if (this->_modules.find(*it) == this->_modules.end()) {
					this->_modules[*it] = new NameModule(false);
					this->_types.append(1, *it);
				}
				break;
			case 'o':
				if (this->_modules.find(*it) == this->_modules.end()) {
					this->_modules[*it] = new OsInfoModule(false);
					this->_types.append(1, *it);
				}
				break;
			case 't':
				if (this->_modules.find(*it) == this->_modules.end()) {
					this->_modules[*it] = new TimeModule(false);
					this->_types.append(1, *it);
				}
				break;
			case 'c':
				if (this->_modules.find(*it) == this->_modules.end()) {
					this->_modules[*it] = new CPUModule(false);
					this->_types.append(1, *it);
				}
				break;
			case 'p':
				if (this->_modules.find(*it) == this->_modules.end()) {
					this->_modules[*it] = new ProcModule(false);
					this->_types.append(1, *it);
				}
				break;
			case 'u':
				if (this->_modules.find(*it) == this->_modules.end()) {
					this->_modules[*it] = new UsageModule(false);
					this->_types.append(1, *it);
				}
				break;
			default:
				std::cerr << "No valid Module '" << *it << "' found." << std::endl;
		}
	}
}
