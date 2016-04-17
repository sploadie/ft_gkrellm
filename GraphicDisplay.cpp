
#include "GraphicDisplay.hpp"

GraphicDisplay::GraphicDisplay( GraphicDisplay const & obj ) { *this = obj; }
GraphicDisplay & GraphicDisplay::operator=( GraphicDisplay const & rhs ) { static_cast<void>(rhs); return *this; }

GraphicDisplay::GraphicDisplay( void ) {
	// Initialize the widget set
	this->_app = Gtk::Application::create();

	// Settings
	Gtk::Settings::get_default()->property_gtk_font_name() = "Copperplate 14";

	// Create the main window
	this->_mainwin = new Gtk::Window(Gtk::WINDOW_TOPLEVEL);
	this->_mainwin->set_title("ft_gkrellm");
	this->_mainwin->set_border_width(5);
	this->_mainwin->add_events(Gdk::KEY_PRESS_MASK);
	this->_mainwin->signal_key_press_event().connect(
    sigc::mem_fun(*this, &GraphicDisplay::keypress));

	// Create Shared Box
	this->_box = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5);
	this->_mainwin->add(*this->_box);
	// this->_box->show();
}

bool GraphicDisplay::keypress(GdkEventKey* e) {
	std::string key = gdk_keyval_name(e->keyval);
	if (key.size() != 1) return true;
	if (this->_modules.find(key[0]) != this->_modules.end()) {
		this->_modules[key[0]]->swapHide();
	} else {
		this->addModules(key);
	}
	return true;
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
				if (this->_modules.find(*it) == this->_modules.end()) { this->_modules[*it] = new NameModule(true); new_widget = true; }
				break;
			case 'o':
				if (this->_modules.find(*it) == this->_modules.end()) { this->_modules[*it] = new OsInfoModule(true); new_widget = true; }
				break;
			case 't':
				if (this->_modules.find(*it) == this->_modules.end()) { this->_modules[*it] = new TimeModule(true); new_widget = true; }
				break;
			case 'c':
				if (this->_modules.find(*it) == this->_modules.end()) { this->_modules[*it] = new CPUModule(true); new_widget = true; }
				break;
			case 'p':
				if (this->_modules.find(*it) == this->_modules.end()) { this->_modules[*it] = new ProcModule(true); new_widget = true; }
				break;
			case 'u':
				if (this->_modules.find(*it) == this->_modules.end()) { this->_modules[*it] = new UsageModule(true); new_widget = true; }
				break;
			case 'r':
				if (this->_modules.find(*it) == this->_modules.end()) { this->_modules[*it] = new RAMModule(true); new_widget = true; }
				break;
			case 'w':
				if (this->_modules.find(*it) == this->_modules.end()) { this->_modules[*it] = new NetworkModule(true); new_widget = true; }
				break;
			case 'l':
				if (this->_modules.find(*it) == this->_modules.end()) { this->_modules[*it] = new PonyModule(true); new_widget = true; }
				break;
			default:
				std::cerr << "No valid Module '" << *it << "' found." << std::endl;
		}
		if (new_widget) {
			new_widget = false;
			this->_box->pack_start(*this->_modules[*it]->getWidget());
			this->_modules[*it]->getWidget()->show_all();
		}
	}
	// this->_box->show();
}
