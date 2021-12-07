#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include "constants.h"
#include <SFML/Graphics.hpp>
#include "graph_info.h"
#include "plot.h"

using namespace std;

class Graph
{
public:
    Graph(Graph_info* info);
    void set_info();
    void draw(sf::RenderWindow& window);
    void update(Graph_info* info);

private:
    Graph_info* _info;
    Plot _plotter;
    vector<sf::Vector2f> _points;
};

#endif //GRAPH_H