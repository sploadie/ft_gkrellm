/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicDisplay.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:32:22 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 19:43:48 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICDISPLAY_H
# define GRAPHICDISPLAY_H

# include "IMonitorDisplay.hpp"
# include "IMonitorModule.hpp"

class GraphicDisplay : public IMonitorDisplay {

public:

	GraphicDisplay( void );

	~GraphicDisplay( void );

	int run( void );
	bool refresh( void );
	void addModules( std::string );

private:
	GraphicDisplay( GraphicDisplay const & obj );
	GraphicDisplay & operator=( GraphicDisplay const & rhs );

	std::map<char, IMonitorModule*>	_modules;
	Glib::RefPtr<Gtk::Application>	_app;
	Gtk::Window*					_mainwin;
	Gtk::Box*						_box;

};

#endif
