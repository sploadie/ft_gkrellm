/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPUModule.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 16:10:52 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CPUModule.hpp"
#include <cstdio>

CPUModule::CPUModule( void ) : AMonitorModule('c', false) {}
CPUModule::CPUModule( CPUModule const & obj ) : AMonitorModule('c', false) { static_cast<void>(obj); }
CPUModule & CPUModule::operator=( CPUModule const & rhs ) { static_cast<void>(rhs); return *this; }

CPUModule::CPUModule( bool has_widget ) : AMonitorModule('c', has_widget) {
	if (this->_has_widget) {
		this->_box = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
		this->_cpu_label = Gtk::manage(new Gtk::Label("CPU"));
		this->_cpu_label->set_padding(5, 3);
		Gtk::Frame* frame;
		frame = Gtk::manage(new Gtk::Frame("CPU Info"));
		try { dynamic_cast<Gtk::Label*>(frame->get_label_widget())->set_markup("<b>CPU Info</b>"); } catch(std::exception) {}
		frame->add(*this->_cpu_label);
		this->_box->pack_start(*frame);

		this->refresh();
	}
}

CPUModule::~CPUModule( void ) {
	if (this->_has_widget) delete this->_box;
}

void CPUModule::refresh( void ) {
	FILE		*info;
	char		buf[256];
	std::string	cpuinfo;

	info = popen("/usr/sbin/system_profiler SPHardwareDataType | /usr/bin/grep \"Proc\\|Cores\" | /usr/bin/sed 's/^[\t ]*//g'", "r");
	if (info == NULL) {
		this->_cpuinfo = "Information unavailable";
		return ;
	}
	while (fgets(buf, 256, info) != NULL) {
		cpuinfo.append(buf);
	}
	pclose(info);
	cpuinfo.erase(std::remove(cpuinfo.end()-1, cpuinfo.end(), '\n'), cpuinfo.end());
	this->_cpuinfo = cpuinfo;
	if (this->_has_widget) {
		this->_cpu_label->set_text(this->_cpuinfo);
	}
}

int CPUModule::toTerminal(int row, int height) {
	if (height < 5) return 0;
	std::string out(std::string("CPU Info:\n") + this->_cpuinfo);
	// if (out.size() > static_cast<unsigned long>(COLS))
	// 	out.erase(COLS, std::string::npos);
	mvaddstr(row, 0, out.c_str());
	return 5;
}

Gtk::Widget* CPUModule::getWidget( void ) { return this->_box; }
