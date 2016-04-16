
#include "GraphicDisplay.hpp"

GraphicDisplay::GraphicDisplay( void ) {}
GraphicDisplay::GraphicDisplay( int argc, char *argv[] ) {
	// Initialize the widget set
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "ft_gkrellm");

	// Create the main window
	Glib::RefPtr<Gtk::Window> mainwin = Gtk::Window(GTK_WINDOW_TOPLEVEL);

	// Add default elements

}

GraphicDisplay::GraphicDisplay( GraphicDisplay const & obj ) { *this = obj; }

GraphicDisplay::~GraphicDisplay( void ) {
	for (std::map<char,IMonitorModule*>::iterator it=this->_modules.begin(); it!=this->_modules.end(); ++it)
		delete it->second;
	return;
}

GraphicDisplay & GraphicDisplay::operator=( GraphicDisplay const & rhs ) {
	// Delete Modules
	// Clone Modules
	return *this;
}

int GraphicDisplay::run( void ) {
	return app->run(this->_mainwin);
}

void GraphicDisplay::addModules(std::string modules) {
	// Add modules (use case)

	this->_mainwin.add();
	// MODULE.WIDGET.show();
}
