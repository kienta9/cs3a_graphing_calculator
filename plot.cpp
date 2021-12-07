#include "plot.h"


Plot::Plot(Graph_info* info): _info(info){
    //empty
}

vector<sf::Vector2f> Plot::set_info(){
    vector<sf::Vector2f> _points;

    //--------tokenize string -> infix--------
    Queue<Token*> infix;
    infix = tokenize(_info->equation);

    //--------infix -> shunting yard -> postfix--------
    ShuntingYard sy(infix);
    _post_fix = sy.postfix();

    //--------postfix -> rpn -> graph points--------
    RPN rpn(_post_fix);
    vector<sf::Vector2f> graph_points;
    double delta = (_info->domain.y - _info->domain.x)/_info->points;
    double y = 0;
    for (double i = _info->domain.x; i <= _info->domain.y; i += delta){
        y = rpn(i);
        graph_points.push_back(sf::Vector2f(i,y));
    }
    //--------//graph points -> screen points--------
    Coordinate_translator transform(_info);
    _points = transform.translate(graph_points);

    return _points;
}

vector<sf::Vector2f> Plot::operator()(){
    return set_info();
}

Queue<Token*> Plot::tokenize(string equation){
    Queue<Token*> infix;
    for (int i = 0; i < equation.length(); i++){
        if (equation[i] == 'x' || equation[i] == 'X'){
            infix.push(new Variable('X'));
        }
        if (equation[i] == '0'){
            infix.push(new Integer(0));
        }
        if (equation[i] == '1'){
            infix.push(new Integer(1));
        }
        if (equation[i] == '2'){
            infix.push(new Integer(2));
        }
        if (equation[i] == '3'){
            infix.push(new Integer(3));
        }
        if (equation[i] == '4'){
            infix.push(new Integer(4));
        }
        if (equation[i] == '5'){
            infix.push(new Integer(5));
        }
        if (equation[i] == '6'){
            infix.push(new Integer(6));
        }
        if (equation[i] == '7'){
            infix.push(new Integer(7));
        }
        if (equation[i] == '8'){
            infix.push(new Integer(8));
        }
        if (equation[i] == '9'){
            infix.push(new Integer(9));
        }
        if (equation[i] == '+'){
            infix.push(new Operator("+"));
        }
        if (equation[i] == '-'){
            infix.push(new Operator("-"));
        }
        if (equation[i] == '*'){
            infix.push(new Operator("*"));
        }
        if (equation[i] == '/'){
            infix.push(new Operator("/"));
        }
        if (equation[i] == '^'){
            infix.push(new Operator("^"));
        }
        if (equation[i] == '('){
            infix.push(new LeftParen());
        }
        if (equation[i] == ')'){
            infix.push(new RightParen());
        }
        if (equation[i] == 't'){
            if (equation[i+1] == 'a' && equation[i+2] == 'n'){
                infix.push(new Function("tan"));
            }
            i+=2;
        }
        if (equation[i] == 's'){
            if (equation[i+1] == 'i' && equation[i+2] == 'n'){
                infix.push(new Function("sin"));
            }
            i+=2;
        }
        if (equation[i] == 'c'){
            if (equation[i+1] == 'o' && equation[i+2] == 's'){
                infix.push(new Function("cos"));
            }
            i+=2;
        }
        if (equation[i] == 'l'){
            if (equation[i+1] == 'o' && equation[i+2] == 'g'){
                infix.push(new Function("log"));
            }
            i+=2;
        }
        if (equation[i] == 'a'){
            if (equation[i+1] == 'b' && equation[i+2] == 's'){
                infix.push(new Function("abs"));
            }
            i+=2;
        }
    }
    return infix;
}