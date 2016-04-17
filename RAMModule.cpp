/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RAMModule.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 16:11:33 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RAMModule.hpp"
#include <cstdio>

RAMModule::RAMModule( void ) : AMonitorModule('r', false) {}
RAMModule::RAMModule( RAMModule const & obj ) : AMonitorModule('r', false) { static_cast<void>(obj); }
RAMModule & RAMModule::operator=( RAMModule const & rhs ) { static_cast<void>(rhs); return *this; }

RAMModule::RAMModule( bool has_widget ) : AMonitorModule('r', has_widget) {
	if (this->_has_widget) {
		this->_box = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
		this->_proc_label = Gtk::manage(new Gtk::Label("RAM"));
		this->_proc_label->set_padding(5, 3);
		Gtk::Frame* frame;
		frame = Gtk::manage(new Gtk::Frame("RAM"));
		try { dynamic_cast<Gtk::Label*>(frame->get_label_widget())->set_markup("<b>RAM</b>"); } catch(std::exception) {}
		frame->add(*this->_proc_label);
		this->_box->pack_start(*frame);

		this->refresh();
	}
}

RAMModule::~RAMModule( void ) {
	if (this->_has_widget) delete this->_box;
}

void RAMModule::refresh( void ) {
	FILE		*info;
	char		buf[256];
	std::string	procinfo;

	info = popen("/usr/bin/top -l1 | /usr/bin/head -n10 | /usr/bin/grep PhysMem | /usr/bin/tr -d '().,' | /usr/bin/sed 's/d/d:/g' | /usr/bin/tr ':' '\\n' | /usr/bin/tail -n4 | /usr/bin/sed 's/^[\t ]*//g'", "r");
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

int RAMModule::toTerminal(int row, int height) {
	if (height < 4) return 0;
	std::string out(std::string("RAM:\n") + this->_procinfo);
	// if (out.size() > static_cast<unsigned long>(COLS))
	// 	out.erase(COLS, std::string::npos);
	mvaddstr(row, 0, out.c_str());
	return 4;
}

Gtk::Widget* RAMModule::getWidget( void ) { return this->_box; }
