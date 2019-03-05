#include <gtkmm.h>
#include "main_window.hpp"


int main(int argc, char **argv) {
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
	main_window window;
	return app->run(window);
}