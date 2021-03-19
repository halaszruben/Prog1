#include "GUI.h"

using namespace Graph_lib;

struct Lines_window : Graph_lib::Window {
	Lines_window(Point xy, int w, int h, const string& title );
	Open_polyline lines;

	bool wait_for_button();

private:
	Button next_button;
	Button quit_button;

	In_box next_x;
	In_box next_y;

	Out_box xy_out;

	Menu color_menu;
	void pressed_red_color();
	void pressed_blue_color();
	void pressed_black_color();
	void changed_color(Color c);

	Button select_color;
	void select_color_pressed();
	void color_after_pressed();

	Menu line_menu;
	void changed_line(Line_style ls);
	void pressed_solid_linestyle();
	void pressed_dash_linestyle();
	void pressed_dot_linestyle();

	Button select_line;
	void select_line_pressed();
	void line_after_pressed();

	void next();
	void quit();

};