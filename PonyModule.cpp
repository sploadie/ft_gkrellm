/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PonyModule.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 18:41:52 by tpaulmye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PonyModule.hpp"

PonyModule::PonyModule( void ) : AMonitorModule('l', false) {}
PonyModule::PonyModule( PonyModule const & obj ) : AMonitorModule('l', false) { static_cast<void>(obj); }
PonyModule & PonyModule::operator=( PonyModule const & rhs ) { static_cast<void>(rhs); return *this; }

PonyModule::PonyModule( bool has_widget ) : AMonitorModule('l', has_widget) {
	if (this->_has_widget) {
		this->_box = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
		this->_proc_label = Gtk::manage(new Gtk::Label("PONY"));
		this->_proc_label->set_padding(5, 3);
		Gtk::Frame* frame;
		frame = Gtk::manage(new Gtk::Frame("Pony"));
		try { dynamic_cast<Gtk::Label*>(frame->get_label_widget())->set_markup("<b>Pony</b>"); } catch(std::exception) {}
		frame->add(*this->_proc_label);
		this->_box->pack_start(*frame);

		this->_switch = false;
		this->refresh();
	}
	this->_switch = false;
}

PonyModule::~PonyModule( void ) {
	if (this->_has_widget) delete this->_box;
}

void PonyModule::refresh( void ) {
	static const std::string pony1 =
	"                    ;;\n"
    "                  ,;;'\\ \n"
    "       __       ,;;' ' \\\n"
    "     /'  '\\'~~'~' \\ /'\\.)\n"
    "  ,;(      )    /  | \n"
    " ,;' \\    /-.,,(   ) \n"
    "      ) /       ) /  \n"
    "      ||        ||   \n"
    "     (_\\       (_\\\n";

	static const std::string pony2 =
	"                    ;;\n"
	"                  ,;;'\\\n"
	"       __       ,;;' ' \\\n"
	"     /'  '\\'~~'~' \\ /'\\.)\n"
	"  ,;(      )    /  |. \n"
	" ,;' \\    /-.,,(   ) \\   \n"
	"      ) /       ) / )|    \n"
	"      ||        ||  \\) \n"
	"     (_\\       (_\\\n";

	this->_procinfo = (this->_switch ? pony1 : pony2);
	this->_switch = (this->_switch ? false : true);
	if (this->_has_widget) {
		this->_proc_label->set_text(this->_procinfo);
	}
}

int PonyModule::toTerminal(int row, int height) {
	if (height < 9) return 0;
	attron(COLOR_PAIR(6));
	mvaddstr(row, 0, this->_procinfo.c_str());
	attroff(COLOR_PAIR(6));
	return 9;
}

Gtk::Widget* PonyModule::getWidget( void ) { return this->_box; }
