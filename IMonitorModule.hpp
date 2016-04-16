/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitorModule.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 14:40:02 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 19:32:08 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMONITORMODULE_H
# define IMONITORMODULE_H

# include <gtkmm.h>
// # include <gtkmm/application.h>
// # include <gtkmm/window.h>
// # include <gtkmm/box.h>
// # include <gtkmm/label.h>
// # include <gtkmm/frame.h>
# include <glibmm/main.h>
# include <iostream>
# include <string>
# include <curses.h>
# include <unistd.h>
# include <cstdlib>
# include <ctime>
# include <signal.h>
# include <map>
# include <algorithm>

class IMonitorModule {
public:
	virtual ~IMonitorModule( void ) {}
	virtual char getType( void ) = 0;
	virtual void swapHide( void ) = 0;
	virtual bool isHidden( void ) = 0;
	virtual void refresh( void ) = 0;
	virtual int toTerminal(int row, int height) = 0;
	virtual Gtk::Widget* getWidget( void ) = 0;
	virtual bool hasWidget( void ) = 0;
};

#endif
