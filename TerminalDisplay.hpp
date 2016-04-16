/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalDisplay.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:31:06 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 15:35:50 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINALDISPLAY_H
# define TERMINALDISPLAY_H

# include "IMonitorDisplay.hpp"

class TerminalDisplay {

public:

	TerminalDisplay( void );
	TerminalDisplay( TerminalDisplay const & obj );

	~TerminalDisplay( void );

	TerminalDisplay & operator=( TerminalDisplay const & rhs );

	int run( void );
	void addModules( std::string );

private:
	std::map<char, IMonitorModule*>	_modules;

};

#endif
