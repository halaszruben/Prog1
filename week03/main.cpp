/*
    g++ main.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`
*/
#include "Simple_window.h"
#include "Graph.h"

int main()
{
    using namespace Graph_lib;

    constexpr int width_max = 700;
    constexpr int height_max = 500;

    Simple_window win(Point{50,50}, width_max, height_max, "Drill_13");


    constexpr int grid_min = 100;
    constexpr int grid_max = 500;
    Lines grid;
    for (int grid_xy = grid_min; grid_xy <= grid_max; grid_xy += grid_min)
    {
    	grid.add(Point{grid_xy,0}, Point{grid_xy, grid_max});
    	grid.add(Point{0,grid_xy}, Point{grid_max,grid_xy});
    }

    win.attach(grid);

    Vector_ref<Rectangle> vector_rectangle;
    for(int i=0; i<5; i++)
    {
    	vector_rectangle.push_back(new Rectangle(Point{i*grid_min, i*grid_min}, grid_min, grid_min));
    	vector_rectangle[i].set_fill_color(Color::red);
    	win.attach(vector_rectangle[i]);

    }

    Vector_ref<Image> vector_image;
    vector_image.push_back(new Image(Point{0,200}, "hawaii-palmtrees.jpg"));
    vector_image.push_back(new Image(Point{0,300}, "hawaii-palmtrees.jpg"));
    vector_image.push_back(new Image(Point{0,400}, "hawaii-palmtrees.jpg"));

    constexpr int image_size = 100;
    for(int i = 0; i < vector_image.size(); ++i)
    {
    	//vector_image[i].set_mask(Point{100,100}, image_size, image_size);
    	win.attach(vector_image[i]);
    }

    Image logo(Point{0,0}, "index.jpeg");
    win.attach(logo);

    for(int i = 0; i < 5; ++i)
    {
    	for(int j = 0; j < 5; j++)
    	{
    		win.wait_for_button();
    		if(j < 4) logo.move(100, 0);
    		else logo.move(-400, 100);
    	}

    }

}
