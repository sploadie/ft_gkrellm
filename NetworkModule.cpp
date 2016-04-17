/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkModule.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 16:10:45 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetworkModule.hpp"
#include <cstdio>

NetworkModule::NetworkModule( void ) : AMonitorModule('w', false) {}
NetworkModule::NetworkModule( NetworkModule const & obj ) : AMonitorModule('w', false) { static_cast<void>(obj); }
NetworkModule & NetworkModule::operator=( NetworkModule const & rhs ) { static_cast<void>(rhs); return *this; }

NetworkModule::NetworkModule( bool has_widget ) : AMonitorModule('w', has_widget) {
	if (this->_has_widget) {
		this->_box = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
		this->_proc_label = Gtk::manage(new Gtk::Label("Network"));
		this->_proc_label->set_padding(5, 3);
		Gtk::Frame* frame;
		frame = Gtk::manage(new Gtk::Frame("Network"));
		try { dynamic_cast<Gtk::Label*>(frame->get_label_widget())->set_markup("<b>Network</b>"); } catch(std::exception) {}
		frame->add(*this->_proc_label);
		this->_box->pack_start(*frame);

		this->refresh();
	}
}

NetworkModule::~NetworkModule( void ) {
	if (this->_has_widget) delete this->_box;
}

void NetworkModule::refresh( void ) {
	FILE		*info;
	char		buf[256];
	std::string	procinfo;

	info = popen("/usr/bin/top -l1 | /usr/bin/head -n10 | /usr/bin/grep 'Networks' | /usr/bin/tr -d ' .' | /usr/bin/tr ':,' '\n' | /usr/bin/sed 's/M/M /g' | /usr/bin/tail -n2 | /usr/bin/sed 's/\\// \\/ /g'", "r");
	if (info == NULL) {
		this->_procinfo = "Information unavailable";
		return ;
	}
	while (fgets(buf, 256, info) != NULL) {
		procinfo.append(buf);
	}
	pclose(info);
	procinfo.erase(std::remove(procinfo.end()-3, procinfo.end(), '\n'), procinfo.end());
	this->_procinfo = procinfo;
	if (this->_has_widget) {
		this->_proc_label->set_text(this->_procinfo);
	}
}

int NetworkModule::toTerminal(int row, int height) {
	if (height < 3) return 0;
	std::string out(std::string("Network:\n") + this->_procinfo);
	// if (out.size() > static_cast<unsigned long>(COLS))
	// 	out.erase(COLS, std::string::npos);
	mvaddstr(row, 0, out.c_str());
	return 3;
}

Gtk::Widget* NetworkModule::getWidget( void ) { return this->_box; }
