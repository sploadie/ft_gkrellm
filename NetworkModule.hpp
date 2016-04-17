/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkModule.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 18:50:42 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORKMODULE_H
# define NETWORKMODULE_H

# include "AMonitorModule.hpp"

class NetworkModule : public AMonitorModule {

public:

	NetworkModule( bool has_widget );

	~NetworkModule( void );

	void refresh( void );
	int toTerminal(int row, int height);
	Gtk::Widget* getWidget( void );

private:
	NetworkModule( void );
	NetworkModule( NetworkModule const & obj );
	NetworkModule & operator=( NetworkModule const & rhs );

	// Gtk::Box* _box;
	std::string _procinfo;
	Gtk::Label* _proc_label;
};

#endif
