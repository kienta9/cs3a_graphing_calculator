#include "rightparen.h"

RightParen::RightParen(): Operator(")"){
    _op = ")";
    _precedence = 3;
}

void RightParen::Print(ostream& outs) const{
    outs << _op;
}

int RightParen::prec(){
    return _precedence;
}