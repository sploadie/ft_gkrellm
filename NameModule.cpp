/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NameModule.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 16:10:17 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NameModule.hpp"

NameModule::NameModule( void ) : AMonitorModule('n', false) {}
NameModule::NameModule( NameModule const & obj ) : AMonitorModule('n', false) { static_cast<void>(obj); }
NameModule & NameModule::operator=( NameModule const & rhs ) { static_cast<void>(rhs); return *this; }

NameModule::NameModule( bool has_widget ) : AMonitorModule('n', has_widget) {
	if (this->_has_widget) {
		this->_box = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
		this->_hostname_label = Gtk::manage(new Gtk::Label("INITIAL HOSTNAME"));
		this->_hostname_label->set_padding(5, 3);
		Gtk::Frame* frame;
		// Host
		frame = Gtk::manage(new Gtk::Frame("Host Name"));
		try { dynamic_cast<Gtk::Label*>(frame->get_label_widget())->set_markup("<b>Host Name</b>"); } catch(std::exception) {}
		frame->add(*this->_hostname_label);
		this->_box->pack_start(*frame);
		// User
		this->_username_label = Gtk::manage(new Gtk::Label("INITIAL USERNAME"));
		this->_username_label->set_padding(5, 3);
		frame = Gtk::manage(new Gtk::Frame("Username"));
		try { dynamic_cast<Gtk::Label*>(frame->get_label_widget())->set_markup("<b>Username</b>"); } catch(std::exception) {}
		frame->add(*this->_username_label);
		this->_box->pack_start(*frame);
		this->refresh();
	}
}

NameModule::~NameModule( void ) {
	if (this->_has_widget) delete this->_box;
}

void NameModule::refresh( void ) {
	char buf[256];

	if (!gethostname(buf, 256)) this->_hostname = buf;
	else						this->_hostname = strerror(errno);
	struct passwd *p = getpwuid(getuid());
	if (p != NULL)	this->_username = p->pw_name;
	else			this->_username = "Idk... root?";
	if (this->_has_widget) {
		this->_hostname_label->set_text(this->_hostname);
		this->_username_label->set_text(this->_username);
	}
}

int NameModule::toTerminal(int row, int height) {
	if (height < 2) return 0;
	std::string out(std::string("Hostname: ") + this->_hostname + std::string("\nUsername: ") + this->_username);
	// if (out.size() > static_cast<unsigned long>(COLS))
	// 	out.erase(COLS, std::string::npos);
	mvaddstr(row, 0, out.c_str());
	return 2;
}

Gtk::Widget* NameModule::getWidget( void ) { return this->_box; }
