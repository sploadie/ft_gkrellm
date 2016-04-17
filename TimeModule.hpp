/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TimeModule.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 18:50:27 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMEMODULE_H
# define TIMEMODULE_H

# include "AMonitorModule.hpp"

class TimeModule : public AMonitorModule {

public:

	TimeModule( bool has_widget );

	~TimeModule( void );

	void refresh( void );
	int toTerminal(int row, int height);
	Gtk::Widget* getWidget( void );

private:
	TimeModule( void );
	TimeModule( TimeModule const & obj );
	TimeModule & operator=( TimeModule const & rhs );

	// Gtk::Box* _box;
	std::string _time;
	Gtk::Label* _time_label;
};

#endif
