#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "graph.h"
#include "graph_info.h"

using namespace std;

class System
{
public:
    System(Graph_info* info);
    void Step(int command, Graph_info* info);
    void Draw(sf::RenderWindow& window);

private:
    Graph _g;
};

#endif // SYSTEM_H
