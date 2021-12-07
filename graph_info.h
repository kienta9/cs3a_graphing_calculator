#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <iostream>
#include <string>
#include <vector>
#include "constants.h"
#include <SFML/Graphics.hpp>

using namespace std;

struct Graph_info
{
    //CTOR:
    Graph_info();

    string equation; //y=x

    sf::Vector2f window_dimension; //x=screen_width, y=screen_height

    sf::Vector2f origin; //x = workpanel/2, y = screen_height/2
    sf::Vector2f scale;   //zoom in zoom  out

    //declare outselves
    sf::Vector2f domain;    //(-5, 5)
    //declare outselves
    int points ; //# of points
};

#endif //GRAPH_INFO_H