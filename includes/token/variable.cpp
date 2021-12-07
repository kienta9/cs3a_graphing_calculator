#include "variable.h"

Variable::Variable(): Token(){
    //empty
}

Variable::Variable(char variable): Token(){
    _var = variable;
}

void Variable::Print(ostream& outs) const{
    outs << _var;
}

char Variable::var(){
    return _var;
}