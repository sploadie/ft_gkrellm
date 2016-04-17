/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcModule.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 18:50:34 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCMODULE_H
# define PROCMODULE_H

# include "AMonitorModule.hpp"

class ProcModule : public AMonitorModule {

public:

	ProcModule( bool has_widget );

	~ProcModule( void );

	void refresh( void );
	int toTerminal(int row, int height);
	Gtk::Widget* getWidget( void );

private:
	ProcModule( void );
	ProcModule( ProcModule const & obj );
	ProcModule & operator=( ProcModule const & rhs );

	// Gtk::Box* _box;
	std::string _procinfo;
	Gtk::Label* _proc_label;
};

#endif
