/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OsInfoModule.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 18:50:40 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OSINFOMODULE_H
# define OSINFOMODULE_H

# include "AMonitorModule.hpp"

class OsInfoModule : public AMonitorModule {

public:

	OsInfoModule( bool has_widget );

	~OsInfoModule( void );

	void refresh( void );
	int toTerminal(int row, int height);
	Gtk::Widget* getWidget( void );

private:
	OsInfoModule( void );
	OsInfoModule( OsInfoModule const & obj );
	OsInfoModule & operator=( OsInfoModule const & rhs );

	// Gtk::Box* _box;
	std::string _osinfo;
	Gtk::Label* _osinfo_label;
};

#endif
