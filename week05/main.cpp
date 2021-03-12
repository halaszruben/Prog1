/*
    g++ main.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`
*/
#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities.h"

double one(double x) { return 1; }

double slope(double x) { return x/2; }

double square(double x) { return x*x; }

double sloping_cos(double x ) { return slope(x) + cos(x); }

int main()
{
    using namespace Graph_lib;

    Simple_window win(Point{10,10}, 600, 600, "Function graphs.");

    Axis x {Axis::x, Point{100,300}, 400, 20, "1 = = 20 pixels"};
    Axis y {Axis::y, Point{300,500}, 400, 20, "1 = = 20 pixels"};

    x.set_color(Color::red);
    y.set_color(Color::red);

    win.attach(x);
    win.attach(y);

    constexpr int x_max = 600;
    constexpr int y_max = 600;
    constexpr int range_min = -10;
    constexpr int range_max = 11;
    constexpr int number_points = 400;
    constexpr int x_scale = 20;
    constexpr int y_scale = 20;
    constexpr int x_orig = x_max / 2;
    constexpr int y_orig = y_max / 2;

    Point orig {x_orig, y_orig};

    Function one_line(one, range_min, range_max, orig, number_points, x_scale, y_scale);

    Function slope_line(slope, range_min, range_max, orig, number_points, x_scale, y_scale);

    Text text{ Point{100,390}, "x/2" };

    Function square_line(square, range_min, range_max, orig, number_points, x_scale, y_scale);

    Function cos_line(cos, range_min, range_max, orig, number_points, x_scale, y_scale);
    cos_line.set_color(Color::blue);

    Function sloping_cos_line(sloping_cos, range_min, range_max, orig, number_points, x_scale, y_scale);

    win.attach(one_line);
    win.attach(slope_line);
    win.attach(text);
    win.attach(square_line);
    win.attach(cos_line);
    win.attach(sloping_cos_line);


    win.wait_for_button();

    return 0;
}
