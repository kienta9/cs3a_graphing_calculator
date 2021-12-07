#include "graph.h"


Graph::Graph(Graph_info* info): _info(info), _plotter(_info) {
    //empty
}

void Graph::draw(sf::RenderWindow& window){
    //--draw axis--
    sf::Vertex lineX[] = 
    {
        sf::Vertex(sf::Vector2f(0,_info->origin.y)),
        sf::Vertex(sf::Vector2f(WORK_PANEL,_info->origin.y))
    };
    sf::Vertex lineY[] = 
    {
        sf::Vertex(sf::Vector2f(_info->origin.x,0)),
        sf::Vertex(sf::Vector2f(_info->origin.x,SCREEN_HEIGHT))
    };
    window.draw(lineX, 2, sf::Lines);
    window.draw(lineY, 2, sf::Lines);

    //--draw points--
    sf::CircleShape Points;
    Points = sf::CircleShape(3);
    Points.setFillColor(sf::Color::Red);
    for (int i = 0; i < _points.size(); i++){
        Points.setPosition(_points[i]);
        window.draw(Points);
    }
}

void Graph::set_info(){
    // _points = _plotter();
    _points = _plotter();
}

void Graph::update(Graph_info* info){
    set_info();
}