#include "system.h"


System::System(Graph_info* info): _g(info)
{
    //empty
}

void System::Step(int command, Graph_info* info){
    _g.update(info);
}


void System::Draw(sf::RenderWindow& window){
    _g.draw(window);
}
