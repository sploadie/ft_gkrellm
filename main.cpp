/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 11:22:21 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/04/16 15:20:46 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helloworld.hpp"
#include <gtkmm/application.h>
#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <signal.h>

static void terminal_settings() {
}

static int do_terminal() {
	terminal_settings();
	// START LOOP
	time_t last_time = time(NULL);
	while (42) {
		if (time(NULL) == last_time) continue;
		last_time = time(NULL);
		// LOOP
	}
	return 0;
}

static int do_graphic(int argc, char *argv[]) {
	// Initialize the widget set
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

	// Create the main window
	Glib::RefPtr<Gtk::Window> mainwin = Gtk::Window(GTK_WINDOW_TOPLEVEL);

	// Set up our GUI elements
	mainwin.add();

	// Show the application window
	gtk_widget_show_all(mainwin);

	// Enter the main event loop, and wait for user interaction
	gtk_main();
	return 0;
}

int main (int argc, char *argv[])
{
	IMonitorDisplay* display;
	std::string default_modules;
	if (argc > 1 && std::string("-t").compare(argv[1]) == 0)	display = new TerminalDisplay();
	else														display = new GraphicDisplay(argc, argv);
	if (argc > 2)	default_modules = argv[2];
	else			default_modules = "abc";
	display.addModules(default_modules);
	return display->run();
}
