#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <string>
#include <cmath>
#include "token.h"
#include "integer.h"

using namespace std;

class Operator : public Token
{
public:
    Operator();
    Operator(string op);

    virtual int prec();

    int getprec();

    double perform(double right, double left);

    string op(); //accessor
    
    void Print(ostream& outs) const;
    TOKEN_TYPES TypeOf(){return OPERATOR;}

private:
    int _precedence;
    string _op;
};



#endif //OPERATOR_H