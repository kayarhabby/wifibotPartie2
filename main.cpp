#include <iostream>
#include <gtkmm/main.h>
#include "gui.h"


int main(int argc, char *argv[])
{
	Gtk::Main app(argc,argv);
	Gui win;
	app.run(win);
	return 0;
}