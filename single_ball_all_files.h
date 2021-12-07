#ifndef SINGLE_BALL_ALL_FILES_H
#define SINGLE_BALL_ALL_FILES_H


/************************************************************************
 *   main.cpp
 ***********************************************************************/

int main()
{

    animate game;
    game.run();
    cout<<endl<<endl<<"------ MAIN EXITING --------------------------"<<endl;
    return 0;
}

/************************************************************************
 *   constants.h
 ***********************************************************************/
const float SCREEN_WIDTH = 1400;
const float SCREEN_HEIGHT = 800;
const float WORK_PANEL = SCREEN_WIDTH*4/5;
const float SIDE_BAR = SCREEN_WIDTH*1/5;


const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;


/************************************************************************
 *   animate.h
 ***********************************************************************/

#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"
class animate{
public:
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
private:
    sf::RenderWindow window;
    sf::CircleShape mousePoint;         //The little red dot
    System system;                      //container for all the animated objects
    int command;                        //command to send to system
    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen
    bool mouseIn;                       //mouse is in the screen
    Sidebar sidebar;                    //rectangular message sidebar

};

string mouse_pos_string(sf::RenderWindow& window);

/************************************************************************
 *   animate.cpp
 ***********************************************************************/
#include "animate.h"
#include "constants.h"
#include <iostream>
using namespace std;
#include "system.h"


animate::animate():sidebar(WORK_PANEL, SIDE_BAR)

{
    cout<<"animate CTOR: TOP"<<endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.

    //System will be implemented to manage a vector of objects to be animated.
    //  at that point, the constructor of the System class will take a vector
    //  of objects created by the animate object.
    //  animate will
    system = System();
    window.setFramerateLimit(60);

    mouseIn = true;




    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);

    cout<<"Geme CTOR. preparing to load the font."<<endl;
    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("../arial.ttf")){
        cout<<"animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("Initial String for myTextLabel", font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setColor(sf::Color::Green);
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-5));







    cout<<"animate instantiated successfully."<<endl;
}

void animate::Draw(){
    //Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn){
        window.draw(mousePoint);
    }

    sidebar.draw(window);

    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(window) gives you window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    //drawing Test: . . . . . . . . . . . .
    //This is how you draw text:)
    window.draw(myTextLabel);
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update(){
    //cause changes to the data for the next frame
    system.Step(command);
    command = 0;
    if (mouseIn){
        //mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x-5,
                               sf::Mouse::getPosition(window).y-5);

        //mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);




    }
}
void animate::render(){
       window.clear();
       Draw();
       window.display();
}



void animate::processEvents()
{
   sf::Event event;
   float mouseX, mouseY;
   while (window.pollEvent(event))//or waitEvent
       {
       // check the type of the event...
           switch (event.type)
           {
           // window closed
           case sf::Event::Closed:
               window.close();
               break;

           // key pressed
           case sf::Event::KeyPressed:
               switch(event.key.code){
                case sf::Keyboard::Left:
                   sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                   command = 4;
                   break;
               case sf::Keyboard::Right:
                   sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                   command = 6;
                   break;
               case sf::Keyboard::Escape:
                   sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                   window.close();
                break;
               }

               break;
           case sf::Event::MouseEntered:
               mouseIn = true;
               break;

           case sf::Event::MouseLeft:
               mouseIn = false;
               break;

           case sf::Event::MouseMoved:
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
                //Do something with it if you need to...
               break;
           case sf::Event::MouseButtonReleased:
                   if (event.mouseButton.button == sf::Mouse::Right)
                   {
                       sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " +
                               mouse_pos_string(window);

                   }
                   else{
                       sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
                               mouse_pos_string(window);
                   }
                   break;

               default:
                   break;
           }
       }
}
void animate::run()
{
   while (window.isOpen())
   {
       processEvents();
       update();
       render(); //clear/draw/display
   }
   cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}

string mouse_pos_string(sf::RenderWindow& window){
    return "(" +
            to_string(sf::Mouse::getPosition(window).x) +
            ", " +
            to_string(sf::Mouse::getPosition(window).y) +
            ")";
}

/************************************************************************
 *   system.h
 ***********************************************************************/
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
class System
{
public:
    System();
    void Step(int command);
    int Size();
    void Draw(sf::RenderWindow& widnow);
private:
//    vector<Particle> system;
    sf::CircleShape shape;
    sf::Vector2f vel;
};
/************************************************************************
 *   system.cpp
 ***********************************************************************/
#include "system.h"
#include "random.h"

#include <iostream>

#include <constants.h>
System::System()
{
    Random r;
    int xpos = 100;
    int ypos = 100;
    //the shape of the object, along with its velocity, acceleration,
    //position, etc. should be part of the individual object.
    shape = sf::CircleShape(10);
    shape.setPosition(sf::Vector2f(xpos, ypos));
    vel = sf::Vector2f(r.Next(-5,5), r.Next(-5,5)); //random velocity
    int r_ = r.Next(0,255);
    int g_ = r.Next(0,255);
    int b_ = r.Next(0,255);
    shape.setFillColor(sf::Color(r_, g_, b_));

}


//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command){

        //all this is the responsibility of the
        // individual object:
        shape.move(vel);
        sf::Vector2f pos = shape.getPosition();
        if ((pos.x)>=WORK_PANEL-20)
            vel = sf::Vector2f(-1*vel.x,1*vel.y);
        if (pos.x<=0)
            vel = sf::Vector2f(-1*vel.x,1*vel.y);
        if ((pos.y)>=SCREEN_HEIGHT-20)
            vel = sf::Vector2f(1*vel.x,-1*vel.y);
        if (pos.y<=0)
            vel = sf::Vector2f(1*vel.x,-1*vel.y);

}


void System::Draw(sf::RenderWindow& window){
    window.draw(shape);

}


/************************************************************************
 *   sidebar.h
 ***********************************************************************/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);
    string& operator [](int index);
private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object

    float _left;
    float _width;

};
/************************************************************************
 *   sidebar.cpp
 ***********************************************************************/
#include "sidebar.h"
#include "constants.h"
Sidebar::Sidebar(){

}

Sidebar::Sidebar(float left, float width):_left(left), _width(width){
    cout<<"Sidebar CTOR: TOP"<<endl;
    items.reserve(50);

    //set up the sidebar rectangle:
    rect.setFillColor(sf::Color(105,105,105)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout<<"Sidebar CTOR: about to load font."<<endl;

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //the font file must be in the "working directory"
    // check projects->run->working directory
    //      [Make sure it's not pointing to the app file]

    if (!font.loadFromFile("Roboto-Thin.ttf")){
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout<<"Sidebar CTOR: loaded font."<<endl;

    //. . . . . text / font problems: . . . . . . . .
    //initializing text object in this way caused problems
    // (hangs!)
    //only when sb_text was a private member and worked fine
    //when it was a public member. Probably not releavant,
    //but still strange!
    //
    //sb_text = sf::Text("Initial String for myTextLabel", font);
    //
    //. . . . . . . . . . . . . . . . . . . . . . . . .
    cout<<"Sidebar CTOR: Text object initialized."<<endl;
    sb_text.setFont(font);
    sb_text.setCharacterSize(20);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setColor(sf::Color::Yellow);

    ////this is how you would position text on screen:
    //sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-sb_text.getLocalBounds().height-5));

    items.push_back("sidebar sample text");
    //Fill the items vector with empty strings so that we can use [] to read them:
    for (int i=0 ; i<30; i++){
        items.push_back("");
    }
    cout<<"Sidebar: CTOR: Exit."<<endl;
}

void Sidebar::draw(sf::RenderWindow& window){
    const double VERTICAL_LINE_SPACING = 5.0;
    const double LEFT_MARGIN = 10.0;

    window.draw(rect);
    float height = 10;

    for (vector<string>::iterator it = items.begin();
                                it!= items.end(); it++){
        bool blank = false;
        if (strlen(it->c_str()) == 0){
            //empty rows must be taken into account (getLocalBounds())
            //    but not drawn
            blank = true;
            sb_text.setString("BLANK");
        }
        else{
            sb_text.setString(it->c_str());
        }
        sb_text.setPosition(sf::Vector2f(_left+LEFT_MARGIN, height));
        height += sb_text.getLocalBounds().height+VERTICAL_LINE_SPACING;
        if (!blank)
            window.draw(sb_text);
    }
}

string& Sidebar::operator [](int index){
    return items[index];
}





#endif // SINGLE_BALL_ALL_FILES_H
