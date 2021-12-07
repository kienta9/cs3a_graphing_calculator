#include "leftparen.h"

LeftParen::LeftParen(): Operator("("){
    _op = "(";
    _precedence = 3;
}

void LeftParen::Print(ostream& outs) const{
    outs << _op;
}

int LeftParen::prec(){
    return _precedence;
}