/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OsInfoModule.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 16:11:17 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OsInfoModule.hpp"
#include <sys/utsname.h>

OsInfoModule::OsInfoModule( void ) : AMonitorModule('o', false) {}
OsInfoModule::OsInfoModule( OsInfoModule const & obj ) : AMonitorModule('o', false) { static_cast<void>(obj); }
OsInfoModule & OsInfoModule::operator=( OsInfoModule const & rhs ) { static_cast<void>(rhs); return *this; }

OsInfoModule::OsInfoModule( bool has_widget ) : AMonitorModule('o', has_widget) {
	if (this->_has_widget) {
		this->_box = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
		this->_osinfo_label = Gtk::manage(new Gtk::Label("OSINFO"));
		this->_osinfo_label->set_padding(5, 3);
		Gtk::Frame* frame;
		frame = Gtk::manage(new Gtk::Frame("OS Info"));
		try { dynamic_cast<Gtk::Label*>(frame->get_label_widget())->set_markup("<b>OS Info</b>"); } catch(std::exception) {}
		frame->add(*this->_osinfo_label);
		this->_box->pack_start(*frame);
		this->refresh();
	}
}

OsInfoModule::~OsInfoModule( void ) {
	if (this->_has_widget) delete this->_box;
}

void OsInfoModule::refresh( void ) {
	struct utsname name;

	if (!uname(&name)) {
		this->_osinfo = std::string(name.sysname) + std::string(" ") + std::string(name.release) + std::string(" ") + std::string(name.machine);
	} else {
		this->_osinfo = "Unknown";
	}
	if (this->_has_widget) {
		this->_osinfo_label->set_text(this->_osinfo);
	}
}

int OsInfoModule::toTerminal(int row, int height) {
	if (height < 1) return 0;
	std::string out(std::string("OS Info: ") + this->_osinfo);
	// if (out.size() > static_cast<unsigned long>(COLS))
	// 	out.erase(COLS, std::string::npos);
	mvaddstr(row, 0, out.c_str());
	return 1;
}

Gtk::Widget* OsInfoModule::getWidget( void ) { return this->_box; }
