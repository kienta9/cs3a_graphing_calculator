#include "token.h"

Token::Token(){
    //empty
}

ostream& operator << (ostream& outs, const Token& token){
    token.Print(outs);
    return outs;
}

void Token::Print(ostream& outs) const{
    outs << "TOKEN Print: Don't call me again!" << endl;
    //virtual, use children's
}