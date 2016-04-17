/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PonyModule.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 18:50:36 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONYMODULE_H
# define PONYMODULE_H

# include "AMonitorModule.hpp"

class PonyModule : public AMonitorModule {

public:

	PonyModule( bool has_widget );

	~PonyModule( void );

	void refresh( void );
	int toTerminal(int row, int height);
	Gtk::Widget* getWidget( void );

private:
	PonyModule( void );
	PonyModule( PonyModule const & obj );
	PonyModule & operator=( PonyModule const & rhs );

	// Gtk::Box* _box;
	std::string _procinfo;
	Gtk::Label* _proc_label;
	bool		_switch;
};

#endif
