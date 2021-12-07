#include "operator.h"

Operator::Operator(): Token(){
    //empty
}

Operator::Operator(string op): Token(){
    _op = op;
    if (_op == "+"){
        _precedence = 1;
    }
    if (_op == "-"){
        _precedence = 1;
    }
    if (_op == "*"){
        _precedence = 2;
    }
    if (_op == "/"){
        _precedence = 2;
    }
    if (_op == "^"){
        _precedence = 3;
    }
}

void Operator::Print(ostream& outs) const{
    outs << _op;
}

int Operator::prec(){
    //virtual, use children's
}

int Operator::getprec(){
    return _precedence;
}

double Operator::perform(double left, double right){
    double result = 0;
    if (_op == "+"){
        result = left + right;
    }
    if (_op == "-"){
        result = left - right;
    }
    if (_op == "*"){
        result = left * right;
    }
    if (_op == "/"){
        result = left / right;
    }
    if (_op == "^"){
        result = pow(left,right);
    }
    return result;
}

string Operator::op(){
    return _op;
}