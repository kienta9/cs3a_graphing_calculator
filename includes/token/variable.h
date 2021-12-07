#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <string>
#include "token.h"

using namespace std;

class Variable : public Token
{
public:
    Variable();
    Variable(char variable);

    void Print(ostream& outs) const;
    TOKEN_TYPES TypeOf(){return VARIABLE;}

    char var();
private:
    char _var;
};



#endif //VARIABLE_H