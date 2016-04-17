/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RAMModule.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 18:50:30 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAMMODULE_H
# define RAMMODULE_H

# include "AMonitorModule.hpp"

class RAMModule : public AMonitorModule {

public:

	RAMModule( bool has_widget );

	~RAMModule( void );

	void refresh( void );
	int toTerminal(int row, int height);
	Gtk::Widget* getWidget( void );

private:
	RAMModule( void );
	RAMModule( RAMModule const & obj );
	RAMModule & operator=( RAMModule const & rhs );

	// Gtk::Box* _box;
	std::string _procinfo;
	Gtk::Label* _proc_label;
};

#endif
