/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UsageModule.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 18:14:13 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USAGEMODULE_H
# define USAGEMODULE_H

# include "AMonitorModule.hpp"

class UsageModule : public AMonitorModule {

public:

	UsageModule( bool has_widget );

	~UsageModule( void );

	void refresh( void );
	int toTerminal(int row, int height);
	Gtk::Widget* getWidget( void );
	bool onClick( void );

private:
	UsageModule( void );
	UsageModule( UsageModule const & obj );
	UsageModule & operator=( UsageModule const & rhs );

	Gtk::Box* _box;
	Gtk::Frame* _frame;
	std::string _procinfo;
	Gtk::Label* _proc_label;
	bool _visual;
	Gtk::DrawingArea* _drawing_area;
};

#endif
