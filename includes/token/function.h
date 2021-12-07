#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <string>
#include <cmath>
#include "operator.h"

using namespace std;

class Function : public Operator //use prec
{
public:
    Function();
    Function(string func);

    string getString();

    double perform(double val);
    
    void Print(ostream& outs) const;
    TOKEN_TYPES TypeOf(){return FUNCTION;}

private:
    string _func;
};



#endif //FUNCTION_H