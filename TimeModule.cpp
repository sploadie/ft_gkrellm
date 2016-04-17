/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TimeModule.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 16:11:43 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TimeModule.hpp"
#include <ctime>

TimeModule::TimeModule( void ) : AMonitorModule('t', false) {}
TimeModule::TimeModule( TimeModule const & obj ) : AMonitorModule('t', false) { static_cast<void>(obj); }
TimeModule & TimeModule::operator=( TimeModule const & rhs ) { static_cast<void>(rhs); return *this; }

TimeModule::TimeModule( bool has_widget ) : AMonitorModule('t', has_widget) {
	if (this->_has_widget) {
		this->_box = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
		this->_time_label = Gtk::manage(new Gtk::Label("TIME"));
		this->_time_label->set_padding(5, 3);
		Gtk::Frame* frame;
		frame = Gtk::manage(new Gtk::Frame("Time"));
		try { dynamic_cast<Gtk::Label*>(frame->get_label_widget())->set_markup("<b>Time</b>"); } catch(std::exception) {}
		frame->add(*this->_time_label);
		this->_box->pack_start(*frame);
		this->refresh();
	}
}

TimeModule::~TimeModule( void ) {
	if (this->_has_widget) delete this->_box;
}

void TimeModule::refresh( void ) {
	time_t rawtime;
 	struct tm *info;
	char buffer[80];

	time( &rawtime );

	info = localtime( &rawtime );

	strftime(buffer, 80, "%c", info);
	this->_time = buffer;
	if (this->_has_widget) {
		this->_time_label->set_text(this->_time);
	}
}

int TimeModule::toTerminal(int row, int height) {
	if (height < 1) return 0;
	std::string out(std::string("Time: ") + this->_time);
	// if (out.size() > static_cast<unsigned long>(COLS))
	// 	out.erase(COLS, std::string::npos);
	mvaddstr(row, 0, out.c_str());
	return 1;
}

Gtk::Widget* TimeModule::getWidget( void ) { return this->_box; }
