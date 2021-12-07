#ifndef PLOT_H
#define PLOT_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "includes/rpn/rpn.h"
#include "includes/shunting_yard/shunting_yard.h"
#include "includes/token/token.h"
#include "includes/token/leftparen.h"
#include "includes/token/rightparen.h"
#include "includes/token/variable.h"
#include "includes/stack/MyStack.h"
#include "includes/queue/MyQueue.h"
#include "graph_info.h"
#include "coordinate_translator.h"

using namespace std;

class Plot
{
public:
    Plot(Graph_info* info);
    vector<sf::Vector2f> set_info();
    vector<sf::Vector2f> operator()();

    Queue<Token*> tokenize(string equation);
private:
    Queue<Token*> _post_fix;
    Graph_info* _info;
};



#endif //PLOT_H