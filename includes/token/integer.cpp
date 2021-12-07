#include "integer.h"

Integer::Integer(): Token(){
    //empty
}

Integer::Integer(double value): Token(){
    _num = value;
}

Integer::Integer(string value): Token(){
    _num = atoi(value.c_str());
}

void Integer::Print(ostream& outs) const{
    outs << _num;
}

double Integer::Num(){
    return _num;
}