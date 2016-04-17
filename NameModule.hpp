/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NameModule.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 18:50:48 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMEMODULE_H
# define NAMEMODULE_H

# include "AMonitorModule.hpp"
# include <pwd.h>

class NameModule : public AMonitorModule {

public:

	NameModule( bool has_widget );

	~NameModule( void );

	void refresh( void );
	int toTerminal(int row, int height);
	Gtk::Widget* getWidget( void );

private:
	NameModule( void );
	NameModule( NameModule const & obj );
	NameModule & operator=( NameModule const & rhs );

	// Gtk::Box* _box;
	std::string _hostname;
	std::string _username;
	Gtk::Label* _hostname_label;
	Gtk::Label* _username_label;
};

#endif
