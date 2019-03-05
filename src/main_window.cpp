#include "main_window.hpp"
#include "sudoku_solver.h"

//Deb include
#include <iostream>

main_window::main_window(){
	int i,j;
	main_window::set_title("Sudoku Solver");
	main_window::set_border_width(12);
	main_window::entry_grid.resize(9);
	for(i=0;i<9;i++){
		main_window::entry_grid[i].resize(9);
		for(j=0;j<9;j++){
			main_window::entry_grid[i][j] = Gtk::Entry();
			main_window::entry_grid[i][j].override_font(Pango::FontDescription("Currier 20"));
			main_window::entry_grid[i][j].set_width_chars(1);
			main_window::g_layout.attach(main_window::entry_grid[i][j], i + (i/3 +1), j + (j/3 +1), 1, 1);
		}
	}
	
	for(i=0;i<4;i++){
		//g_layout.attach(Gtk::HSeparator(), 0, i*4, 13, 1);
	}
	for(i=0;i<4;i++){
		//g_layout.attach(Gtk::VSeparator(), i*4, 0, 1, 13);
	}
	
	main_window::btn_solve = Gtk::Button("Solve");
	main_window::g_layout.attach(main_window::btn_solve, 0, 14, 13, 1);
	main_window::btn_solve.signal_clicked().connect(sigc::mem_fun(*this,
              &main_window::btn_solve_handler) );
	
	main_window::btn_clear = Gtk::Button("Clear");
	main_window::g_layout.attach(main_window::btn_clear, 0, 15, 13, 1);
	main_window::btn_clear.signal_clicked().connect(sigc::mem_fun(*this,
              &main_window::btn_clear_handler) );
	
	
	main_window::add(main_window::g_layout);
	main_window::show_all_children();

}

main_window::~main_window(){}

void main_window::btn_solve_handler(){
	std::vector<std::vector < int> > g;
	main_window::get_grid(g);
	solveSudoku(g);
	main_window::set_grid(g);
}

void main_window::btn_clear_handler(){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			main_window::entry_grid[i][j].set_text(std::string("").c_str());
		}
	}
}

void main_window::get_grid(std::vector<std::vector < int> > &g){
	int i,j;
	g.resize(9);
	for(i=0;i<9;i++){
		g[i].resize(9);
		for(j=0;j<9;j++){
			std::string s(main_window::entry_grid[i][j].get_text());
			if(s.size()>0 && s[0]>='1' && s[0]<='9'){
				g[i][j]=s[0]-'0';
			}else{
				g[i][j]=0;
			}
		}
	}
}

void main_window::set_grid(std::vector<std::vector < int> > &g){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			main_window::entry_grid[i][j].set_text(std::to_string(g[i][j]).c_str());
		}
	}
}
