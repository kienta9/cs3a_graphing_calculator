#include "shunting_yard.h"

ShuntingYard::ShuntingYard(){
    _infix = Queue<Token*>();
}

ShuntingYard::ShuntingYard(Queue<Token*> infix){
    _infix = infix;
}

void ShuntingYard::infix(Queue<Token*> newinfix){
    _infix = newinfix;
}

Queue<Token*> ShuntingYard::postfix(){
    Queue<Token*> infix;
    infix = _infix;
    Queue<Token*> queue;
    Stack<Token*> stack;
    while (!infix.empty()){
        Token* p = infix.pop();
        if (p->TypeOf() == NUMBER){
            queue.push(p);
        }
        if (p->TypeOf() == VARIABLE){
            queue.push(p);
        }
        if (p->TypeOf() == FUNCTION){
            stack.push(p);
        }
        if (p->TypeOf() == OPERATOR){
            while (!stack.empty() 
            && (static_cast<Operator*>(p)->getprec() <= static_cast<Operator*>(stack.top())->getprec())
            && (stack.top()->TypeOf() != LPAREN)){
                queue.push(stack.pop());
            }
            stack.push(p);
        }
        if (p->TypeOf() == LPAREN){
            stack.push(p);
        }
        if (p->TypeOf() == RPAREN){
            while(stack.top()->TypeOf() != LPAREN){
                queue.push(stack.pop());
            }
            stack.pop();
        }
    }
    if (infix.empty()){
        while(!stack.empty()){
            queue.push(stack.pop());
        }
    }
    return queue;
}

Queue<Token*> ShuntingYard::postfix(Queue<Token*> input){
    _infix = input;
    Queue<Token*> infix;
    infix = _infix;
    Queue<Token*> queue;
    Stack<Token*> stack;
    while (!infix.empty()){
        Token* p = infix.pop();
        if (p->TypeOf() == NUMBER){
            queue.push(p);
        }
        if (p->TypeOf() == VARIABLE){
            queue.push(p);
        }
        if (p->TypeOf() == FUNCTION){
            stack.push(p);
        }
        if (p->TypeOf() == OPERATOR){
            while (!stack.empty() 
            && (static_cast<Operator*>(p)->getprec() <= static_cast<Operator*>(stack.top())->getprec())
            && (stack.top()->TypeOf() != LPAREN)){
                queue.push(stack.pop());
            }
            stack.push(p);
        }
        if (p->TypeOf() == LPAREN){
            stack.push(p);
        }
        if (p->TypeOf() == RPAREN){
            while(stack.top()->TypeOf() != LPAREN){
                queue.push(stack.pop());
            }
            stack.pop();
        }
    }
    if (infix.empty()){
        while(!stack.empty()){
            queue.push(stack.pop());
        }
    }
    return queue;
}