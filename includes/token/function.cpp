#include "function.h"

Function::Function(): Operator(){
    //empty
}

Function::Function(string func):Operator(func){
    _func = func;
}

string Function::getString(){
    return _func;
}

double Function::perform(double val){
    double result = 0;
    if (_func == "sin"){
        result = sin(val);
    }
    if (_func == "cos"){
        result = cos(val);
        // result = sqrt(1 - pow(sin(val),2));
    }
    if (_func == "tan"){
        result = tan(val);
    }
    if (_func == "log"){
        result = log(val);
    }
    if (_func == "abs"){
        result = abs(val);
    }
    return result;
}

void Function::Print(ostream& outs) const{
    outs << _func;
}
