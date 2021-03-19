/*
    g++ lines_main.cpp Graph.cpp Window.cpp GUI.cpp Lines_window.cpp -o lines_main `fltk-config --ldflags --use-images`
*/
#include "Lines_window.h"
#include "Graph.h"

int main()
{
    Lines_window win {Point{100,100}, 1000, 600, "Drill_16"};
    
    return gui_main();
}
