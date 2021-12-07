#include "coordinate_translator.h"

Coordinate_translator::Coordinate_translator(Graph_info* info): _info(info){
    //empty
}

vector<sf::Vector2f> Coordinate_translator::translate(vector<sf::Vector2f> points){
    //return translated coordinate vector
    vector<sf::Vector2f> screen_points;
    for (int i = 0; i < points.size(); i++){
        sf::Vector2f point;
        point.x = _info->origin.x + points[i].x * _info->scale.x;
        point.y = _info->origin.y - points[i].y * _info->scale.y;
        screen_points.push_back(point);
    }
    return screen_points;
}

vector<sf::Vector2f> Coordinate_translator::operator()(vector<sf::Vector2f> points){
    //return translated coordinate vector
    return translate(points);
}





//(10,10)