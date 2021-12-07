#include "rpn.h"

RPN::RPN(){
    _postfix = Queue<Token*>();
}

RPN::RPN(Queue<Token*> postfix){
    _postfix = postfix;
}

void RPN::set_input(Queue<Token*> postfix){
    _postfix = postfix;
}

double RPN::evaluate(){
    Stack<Token*> container;
    while (!_postfix.empty()){
        Token* p = _postfix.pop();
        if (p->TypeOf() == NUMBER){
            container.push(p);
        }
        if (p->TypeOf() == FUNCTION){
            Token* num = container.pop();
            double value = static_cast<Integer*>(num)->Num();
            double result = static_cast<Function*>(p)->perform(value);
            container.push(new Integer(result));
        }
        if (p->TypeOf() == OPERATOR){
            Token* right = container.pop();
            Token* left = container.pop();
            double rvalue = static_cast<Integer*>(right)->Num();
            double lvalue = static_cast<Integer*>(left)->Num();

            double result = static_cast<Operator*>(p)->perform(lvalue, rvalue);
            container.push(new Integer(result));
        }
    }
    return static_cast<Integer*>(container.pop())->Num();
}

double RPN::evaluate(double input){
    Stack<Token*> container;
    Queue<Token*> postfix = _postfix;
        while (!postfix.empty()){
            Token* p = postfix.pop();
            if (p->TypeOf() == NUMBER){
                container.push(p);
            }
            if (p->TypeOf() == VARIABLE){
                container.push(new Integer(input));
            }
            if (p->TypeOf() == FUNCTION){
                Token* num = container.pop();
                double value = static_cast<Integer*>(num)->Num();
                double result = static_cast<Function*>(p)->perform(value);
                container.push(new Integer(result));
            }
            if (p->TypeOf() == OPERATOR){
                Token* right = container.pop();
                Token* left = container.pop();
                double rvalue = static_cast<Integer*>(right)->Num();
                double lvalue = static_cast<Integer*>(left)->Num();
                 
                double result = static_cast<Operator*>(p)->perform(lvalue, rvalue);
                container.push(new Integer(result));
            }
        }
    return static_cast<Integer*>(container.pop())->Num();
}

double RPN::operator()(){
    return evaluate();
}

double RPN::operator()(double input){
    return evaluate(input);
}