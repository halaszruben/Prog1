/*
    g++ main.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`
*/
#include "Simple_window.h"
#include "Graph.h"
#include "../../std_lib_facilities.h"

double one(double) { return 1; }

double square(double x) { return x*x; }

int main()
try{
    using namespace Graph_lib;

    int x_max = 1366;
    int y_max = 768;
    int x_window = 650;
    int y_window = 400;

    Point topleft{50,50};
    Simple_window window (topleft, 650, 400, "Canvas");
    
    Axis x_axis {Axis::x, Point{10,200},300,20,"x axis"};
    Axis y_axis {Axis::y, Point{70,300},200,20, "y axis"};
    y_axis.set_color(Color::red);
    y_axis.label.set_color(Color::green);

    Function sinus {sin,0,50,Point{6,200},1000,20,20};

    Polygon poligon;
    poligon.add(Point{400,300});
    poligon.add(Point{450,200});
    poligon.add(Point{500,300});
    poligon.set_color(Color::blue);
    poligon.set_style(Line_style::dot);

    Rectangle rectangle{Point{200,30}, 100, 50};

    Closed_polyline poly_rect;
	poly_rect.add(Point{400,50});
	poly_rect.add(Point{500,50});
	poly_rect.add(Point{500,100});
	poly_rect.add(Point{400,100});
	poly_rect.add(Point{350,75});


	rectangle.set_fill_color(Color::cyan);
	poligon.set_style(Line_style(Line_style::dash,20));
	poly_rect.set_style(Line_style(Line_style::dot,4));
	poly_rect.set_fill_color(Color::red);

	Text text{Point(200,200), "Ahoooy!"};
	text.set_font(Font::helvetica_italic);
	text.set_font_size(14);

	Image image {Point(50,20), "badge.jpg"};

	Circle circle {Point(200,300),60};
	circle.set_style(Line_style(30));

	Ellipse ellipse{Point{200,300},75,25};
	ellipse.set_color(Color::dark_red);
	Mark mark{Point(200,300),'x'};

	
	window.attach(image);
	ostringstream oss;
		oss << "screen size: " << x_max << "*" << y_max
 			<< "; window size: " << x_window << "*" << y_window;
		Text sizes {Point{50,10},oss.str()};



	window.attach(circle);
	window.attach(mark);
	window.attach(sizes);
	window.attach(ellipse);
	window.attach(text);
	window.attach(poly_rect);
    window.attach(rectangle);
    window.attach(poligon);
    window.attach(sinus);
    window.attach(y_axis);
    window.attach(x_axis);

    window.set_label("Testing, 1, 2, 3");
    window.wait_for_button();


}
catch(exception& e)
{
	cerr << e.what() << endl;
	return 1;
}
catch(...)
{
	cerr << "Some error\n";
	return 2;
}
