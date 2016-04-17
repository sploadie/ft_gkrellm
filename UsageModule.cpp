/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UsageModule.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 16:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/17 20:14:30 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UsageModule.hpp"
#include <cstdio>

UsageModule::UsageModule( void ) : AMonitorModule('u', false) {}
UsageModule::UsageModule( UsageModule const & obj ) : AMonitorModule('u', false) { static_cast<void>(obj); }
UsageModule & UsageModule::operator=( UsageModule const & rhs ) { static_cast<void>(rhs); return *this; }

bool UsageModule::onClick( void ) {
	this->_visual = (this->_visual ? false : true);
	this->_frame->remove();
	return true;
}

UsageModule::UsageModule( bool has_widget ) : AMonitorModule('u', has_widget) {
	this->_visual = false;
	if (this->_has_widget) {
		this->_box = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
		this->_proc_label = new Gtk::Label("USAGE");
		this->_proc_label->set_padding(5, 3);
		this->_frame = Gtk::manage(new Gtk::Frame("CPU Usage"));
		try { dynamic_cast<Gtk::Label*>(this->_frame->get_label_widget())->set_markup("<b>CPU Usage</b>"); } catch(std::exception) {}
		this->_frame->add(*this->_proc_label);
		Gtk::EventBox* event_box = Gtk::manage(new Gtk::EventBox());
		event_box->add(*this->_frame);
		event_box->add_events(Gdk::ALL_EVENTS_MASK);
		event_box->signal_button_release_event().connect(sigc::hide(sigc::mem_fun(*this, &UsageModule::onClick)));
		this->_box->pack_start(*event_box);
		this->_drawing_area = NULL;
		this->refresh();
	}
}

UsageModule::~UsageModule( void ) {
	if (this->_has_widget) {
		delete this->_box;
		delete this->_proc_label;
		if (this->_drawing_area != NULL) delete this->_drawing_area;
	}
}

void UsageModule::refresh( void ) {
	FILE		*info;
	char		buf[256];
	std::string	procinfo;

	info = popen("/usr/bin/top -l1 | /usr/bin/grep 'CPU usage' | /usr/bin/head -n1 | /usr/bin/tr ':,' '\n\n' | /usr/bin/tail -n3 | /usr/bin/sed 's/^[\t ]*//g'", "r");
	if (info == NULL) {
		this->_procinfo = "Information unavailable";
		return ;
	}
	while (fgets(buf, 256, info) != NULL) {
		procinfo.append(buf);
	}
	pclose(info);
	procinfo.erase(std::remove(procinfo.end()-1, procinfo.end(), '\n'), procinfo.end());
	this->_procinfo = procinfo;
	if (this->_has_widget) {
		this->_proc_label->set_text(this->_procinfo);
		if (this->_visual) {
			float f = 0.0;
			try { f = stof(this->_procinfo.substr(this->_procinfo.find_last_of('\n'), std::string::npos)); } catch(std::exception) {}
			f = f / 100;
			if (this->_drawing_area == NULL) {
				this->_drawing_area = new Gtk::DrawingArea;
			}
			if (this->_drawing_area->get_window() != static_cast<Glib::RefPtr<Gdk::Window> >(nullptr)) {
				std::cout << f << std::endl;
				Cairo::RefPtr<Cairo::Context> cr = this->_drawing_area->get_window()->create_cairo_context();
				// this->_drawing_area->queue_draw();
				// cr->save();
				cr->set_source_rgb(1.0, 0.0, 0.0);
				cr->set_line_width(2.0);
				Gtk::Allocation a = this->_drawing_area->get_allocation();
				const int width = a.get_width();
				const int height = a.get_height();
				int xc, yc;
				xc = width / 2;
				yc = height / 2;
				cr->move_to(width-1, height);
				cr->line_to(width-1, static_cast<float>(height) * f);
				cr->stroke();
				// cr->restore();
				this->_drawing_area->queue_draw();
			}
		}
		if (this->_frame->get_child() == nullptr) {
			if (this->_visual && this->_drawing_area != NULL) {
				this->_frame->add(*this->_drawing_area);
				this->_drawing_area->set_hexpand(true);
				this->_drawing_area->set_vexpand(true);
			} else {
				this->_frame->add(*this->_proc_label);
			}
			this->_frame->show_all();
		}
	}
}

int UsageModule::toTerminal(int row, int height) {
	if (height < 4) return 0;
	std::string out(std::string("CPU Usage:\n") + this->_procinfo);
	// if (out.size() > static_cast<unsigned long>(COLS))
	// 	out.erase(COLS, std::string::npos);
	mvaddstr(row, 0, out.c_str());
	return 4;
}

Gtk::Widget* UsageModule::getWidget( void ) { return this->_box; }
