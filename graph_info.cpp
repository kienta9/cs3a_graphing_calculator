#include "graph_info.h"

Graph_info::Graph_info(){
    equation = "0";
    
    window_dimension = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);

    origin = sf::Vector2f(WORK_PANEL/2, SCREEN_HEIGHT/2);

    scale = sf::Vector2f(100,100);

    domain = sf::Vector2f(-10,10);

    points = 1000;
}

