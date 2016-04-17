/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalDisplay.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:31:06 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 19:14:30 by tpaulmye         ###   ########.fr       */
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
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);

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
	int	lines_used;
	int	lines_remaining;
	std::string::iterator it;
	char ch;
	while (42) {
		ch = getch();
		if (ch == 'q' || ch == 'Q') {
			endwin();
 			break;
 		} else if (ch != ERR) {
			if (this->_modules.find(ch) != this->_modules.end()) {
				this->_modules[ch]->swapHide();
			} else {
				this->addModules(std::string(1, ch));
			}
			last_time = 0;
		}
		if (time(NULL) == last_time) continue;
		last_time = time(NULL);
		::refresh();
		clear();
		lines_remaining = LINES;
		// try {
		for (it=this->_types.begin(); it!=this->_types.end(); ++it) {
			if (this->_modules[*it] != NULL) {
				if (this->_modules[*it]->isHidden()) continue;
				// try { lines_remaining -= this->_modules[*it]->toTerminal(LINES - lines_remaining, lines_remaining); } catch(std::exception & e) { endwin(); std::cerr << "this->_modules[*]->toTerminal : " << e.what() << std::endl; }
				lines_used = this->_modules[*it]->toTerminal(LINES - lines_remaining, lines_remaining);
				if (lines_used == 0) continue;
				lines_remaining -= lines_used;
				if (lines_remaining > 0) {
					move(LINES - lines_remaining, 0);
					hline('=', COLS);
					--lines_remaining;
				} else { break; }
			}
		}
		// } catch(std::exception & e) { endwin(); std::cerr << "for (it=this->_modules.begin(); : " << e.what() << std::endl; }
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
			case 'r':
				if (this->_modules.find(*it) == this->_modules.end()) {
					this->_modules[*it] = new RAMModule(false);
					this->_types.append(1, *it);
				}
				break;
			case 'w':
				if (this->_modules.find(*it) == this->_modules.end()) {
					this->_modules[*it] = new NetworkModule(false);
					this->_types.append(1, *it);
				}
				break;
			case 'l':
				if (this->_modules.find(*it) == this->_modules.end()) {
					this->_modules[*it] = new PonyModule(false);
					this->_types.append(1, *it);
				}
				break;
			default:
				std::cerr << "No valid Module '" << *it << "' found." << std::endl;
		}
	}
}
