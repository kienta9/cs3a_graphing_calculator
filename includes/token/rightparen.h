#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H

#include <iostream>
#include <string>
#include "operator.h"

using namespace std;

class RightParen : public Operator
{
public:
    RightParen();

    int prec();
    
    void Print(ostream& outs) const;
    TOKEN_TYPES TypeOf(){return RPAREN;}

private:
    int _precedence;
    string _op;
};



#endif //RIGHTPAREN_H