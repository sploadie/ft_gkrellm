
#include "GraphicDisplay.hpp"

GraphicDisplay::GraphicDisplay( GraphicDisplay const & obj ) { *this = obj; }
GraphicDisplay & GraphicDisplay::operator=( GraphicDisplay const & rhs ) { static_cast<void>(rhs); return *this; }

GraphicDisplay::GraphicDisplay( void ) {
	// Initialize the widget set
	this->_app = Gtk::Application::create();

	// Create the main window
	this->_mainwin = new Gtk::Window(Gtk::WINDOW_TOPLEVEL);
	this->_mainwin->set_title("ft_gkrellm");
	this->_mainwin->set_border_width(5);

	// Create Shared Box
	this->_box = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5);
	this->_mainwin->add(*this->_box);
	// this->_box->show();
}

GraphicDisplay::~GraphicDisplay( void ) {
	for (std::map<char,IMonitorModule*>::iterator it=this->_modules.begin(); it!=this->_modules.end(); ++it)
		delete it->second;
	delete this->_box;
	delete this->_mainwin;
	return;
}

bool GraphicDisplay::refresh( void ) {
	for (std::map<char,IMonitorModule*>::iterator it=this->_modules.begin(); it!=this->_modules.end(); ++it)
		it->second->refresh();
	return true;
}

int GraphicDisplay::run( void ) {
	sigc::connection conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &GraphicDisplay::refresh), 1000);
	this->_mainwin->show_all();
	int ret = this->_app->run(*this->_mainwin);
	conn.disconnect();
	return ret;
}

void GraphicDisplay::addModules(std::string modules) {
	bool new_widget = false;
	for (std::string::iterator it = modules.begin(); it != modules.end(); ++it) {
		switch (*it) {
			case 'n':
				if (this->_modules.find('n') == this->_modules.end()) { this->_modules['n'] = new NameModule(true); new_widget = true; }
				break;
			case 'o':
				if (this->_modules.find('o') == this->_modules.end()) { this->_modules['o'] = new OsInfoModule(true); new_widget = true; }
				break;
			case 't':
				if (this->_modules.find('t') == this->_modules.end()) { this->_modules['t'] = new TimeModule(true); new_widget = true; }
				break;
			case 'c':
				if (this->_modules.find('c') == this->_modules.end()) { this->_modules['c'] = new CPUModule(true); new_widget = true; }
				break;
			default:
				std::cerr << "No valid Module '" << *it << "' found." << std::endl;
		}
		if (new_widget) {
			new_widget = false;
			this->_box->pack_start(*this->_modules[*it]->getWidget());
			// this->_modules[*it]->getWidget()->show();
		}
	}
	// this->_box->show();
}
