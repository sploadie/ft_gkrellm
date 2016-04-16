/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalDisplay.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:31:06 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 19:25:47 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINALDISPLAY_H
# define TERMINALDISPLAY_H

# include "IMonitorDisplay.hpp"
# include <curses.h>

class TerminalDisplay : public IMonitorDisplay {

public:
	TerminalDisplay( void );
	~TerminalDisplay( void );

	int run( void );
	void refresh( void );
	void addModules( std::string );

private:
	TerminalDisplay( TerminalDisplay const & obj );
	TerminalDisplay & operator=( TerminalDisplay const & rhs );

	std::map<char, IMonitorModule*>	_modules;

};

#endif
