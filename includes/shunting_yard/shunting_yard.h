#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/function.h"
#include "../token/variable.h"

using namespace std;

class ShuntingYard
{
public:
    ShuntingYard();
    ShuntingYard(Queue<Token*> infix);

    Queue<Token*> postfix();
    Queue<Token*> postfix(Queue<Token*> input);
    
    void infix(Queue<Token*> newinfix);
    
private:
    Queue<Token*> _infix;
};



#endif //SHUNTING_YARD_H