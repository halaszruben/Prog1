#include "Lines_window.h"

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    :Window{xy,w,h,title},
    next_button{Point{x_max()-300,0}, 150, 40, "Next point",
        [](Address, Address pw) {reference_to<Lines_window>(pw).next();}},
    quit_button{Point{x_max()-150,0}, 150, 40, "Quit",
        [](Address, Address pw) {reference_to<Lines_window>(pw).quit();}},
    next_x{Point{300,0}, 50, 40, "next x:"},
    next_y{Point{450,0}, 50, 40, "next y:"},
    xy_out{Point{100,0}, 100, 40, "current (x,y):"},
    color_menu{Point{x_max()-150, 60}, 150, 40, Menu::vertical, "Colors"},
    select_color{Point{x_max()-150, 60}, 150, 40, "Select Color",
		[](Address, Address pw){reference_to<Lines_window>(pw).select_color_pressed(); }},
    line_menu{Point{x_max()- 300, 60}, 150, 40, Menu::vertical, "Lines"},
    select_line{Point{x_max()-300, 60}, 150, 40, "Select Line",
		[](Address, Address pw) {reference_to<Lines_window>(pw).select_line_pressed(); }}
    	
{

    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    attach(lines);


    color_menu.attach(new Button(Point{0,0}, 0, 0, "Red", 
    	[](Address, Address pw) {reference_to<Lines_window>(pw).pressed_red_color(); 
    	}));
    color_menu.attach(new Button(Point{0,0}, 0, 0, "Blue",
    	[](Address, Address pw) {reference_to<Lines_window>(pw).pressed_blue_color(); 
    	}));
    color_menu.attach(new Button(Point{0,0}, 0, 0, "Black",
    	[](Address, Address pw) {reference_to<Lines_window>(pw).pressed_black_color(); 
    	}));

    attach(color_menu);
    color_menu.hide();

    attach(select_color);

    line_menu.attach(new Button(Point{0,0}, 0, 0, "Solid",
    	[](Address, Address pw) {reference_to<Lines_window>(pw).pressed_solid_linestyle();
    	}));
    line_menu.attach(new Button(Point{0,0}, 0, 0, "Dash",
		[](Address, Address pw) {reference_to<Lines_window>(pw).pressed_dash_linestyle();
		}));
	line_menu.attach(new Button(Point{0,0}, 0, 0, "Dot",
		[](Address, Address pw) {reference_to<Lines_window>(pw).pressed_dot_linestyle();
		}));

	attach(line_menu); 
	line_menu.hide();   

	attach(select_line);

}

void Lines_window::changed_color(Color c)
{
	lines.set_color(c);
}

void Lines_window::pressed_red_color()
{
	changed_color(Color::red);
	color_after_pressed();
	redraw();
}

void Lines_window::pressed_blue_color()
{
	changed_color(Color::blue);
	color_after_pressed();
	redraw();
}

void Lines_window::pressed_black_color()
{
	changed_color(Color::black);
	color_after_pressed();
	redraw();
}

void Lines_window::select_color_pressed()
{
	select_color.hide();
	color_menu.show();
}

void Lines_window::color_after_pressed()
{
	color_menu.hide();
	select_color.show();	
}

void Lines_window::changed_line(Line_style ls)
{
	lines.set_style(ls);
}

void Lines_window::pressed_solid_linestyle()
{
	changed_line(Line_style::solid);
	line_after_pressed();
	redraw();
}

void Lines_window::pressed_dash_linestyle()
{
	changed_line(Line_style::dash);
	line_after_pressed();
	redraw();
}

void Lines_window::pressed_dot_linestyle()
{
	changed_line(Line_style::dot);
	line_after_pressed();
	redraw();
}

void Lines_window::select_line_pressed()
{
	select_line.hide();
	line_menu.show();
}

void Lines_window::line_after_pressed()
{
	line_menu.hide();
	select_line.show();
}

void Lines_window::quit()
{
    hide();
}

void Lines_window::next()
{
    int x = next_x.get_int();
    int y = next_y.get_int();

    lines.add(Point{x,y});

    ostringstream ss;
    ss << '(' << x << ',' << y << ')';
    xy_out.put(ss.str());

    redraw();
}