#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include <iostream>
#include <string>
#include "operator.h"

using namespace std;

class LeftParen : public Operator
{
public:
    LeftParen();

    int prec();
    
    void Print(ostream& outs) const;
    TOKEN_TYPES TypeOf(){return LPAREN;}

private:
    int _precedence;
    string _op;
};



#endif //LEFTPAREN_H