#ifndef COORDINATE_TRANSLATOR_H
#define COORDINATE_TRANSLATOR_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "graph_info.h"

using namespace std;

class Coordinate_translator
{
public:
    Coordinate_translator(Graph_info* info);
    vector<sf::Vector2f> translate(vector<sf::Vector2f> points);
    vector<sf::Vector2f> operator()(vector<sf::Vector2f> points);
private:
    Graph_info* _info;
};

#endif //COORDINATE_TRANSLATOR_H