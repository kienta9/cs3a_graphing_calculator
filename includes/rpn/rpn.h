#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <cmath>
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/function.h"
#include "../token/constants.h"
#include "../token/variable.h"

using namespace std;

class RPN
{
public:
    RPN();
    RPN(Queue<Token*> postfix);

    void set_input(Queue<Token*> postfix);

    double evaluate();
    double evaluate(double input);

    double operator()();
    double operator()(double input);

private:
    Queue<Token*> _postfix;
};


#endif //RPN_H