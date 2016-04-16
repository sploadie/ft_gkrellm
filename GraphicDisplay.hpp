/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicDisplay.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:32:22 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 15:35:44 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICDISPLAY_H
# define GRAPHICDISPLAY_H

# include "IMonitorDisplay.hpp"

class GraphicDisplay {

public:

	GraphicDisplay( int argc, char *argv[] );
	GraphicDisplay( GraphicDisplay const & obj );

	~GraphicDisplay( void );

	GraphicDisplay & operator=( GraphicDisplay const & rhs );

	int run( void );
	void addModules( std::string );

private:
	GraphicDisplay( void );
	std::map<char, IMonitorModule*>	_modules;
	Glib::RefPtr<Gtk::Application>	_app;
	Glib::RefPtr<Gtk::Window>		_mainwin;

};

#endif
