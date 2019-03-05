#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <gtkmm.h>
#include <vector>
#include <string>

class main_window: public Gtk::Window{

public:
	main_window();
	virtual ~main_window();
	
protected:
	void btn_solve_handler();
	void btn_clear_handler();
	void get_grid(std::vector<std::vector < int> > &g);
	void set_grid(std::vector<std::vector < int> > &g);
	
	//Child widget
	Gtk::Grid g_layout;
	std::vector < std::vector <Gtk::Entry> > entry_grid;
	Gtk::Button btn_solve;
	Gtk::Button btn_clear;
	
};
