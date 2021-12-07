#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <string>
#include "token.h"

using namespace std;

class Integer : public Token
{
public:
    Integer();
    Integer(double value);
    Integer(string value);

    void Print(ostream& outs) const;
    TOKEN_TYPES TypeOf(){return NUMBER;}

    double Num();
private:
    double _num;
};



#endif //INTEGER_H