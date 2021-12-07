#include "animate.h"
#include "constants.h"
#include "system.h"
#include <iostream>

using namespace std;

animate::animate() : _info(new Graph_info), system(_info), sidebar(WORK_PANEL, SIDE_BAR)

{
    cout << "animate CTOR: TOP" << endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graphing Calculator");
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.

    //System will be implemented to manage a vector of objects to be animated.
    //  at that point, the constructor of the System class will take a vector
    //  of objects created by the animate object.
    //  animate will

    window.setFramerateLimit(60);

    mouseIn = true;

    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);

    cout << "Geme CTOR. preparing to load the font." << endl;
    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("../arial.ttf"))
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("Initial String for myTextLabel", font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color::Green);
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - myTextLabel.getLocalBounds().height - 5));

    cout << "animate instantiated successfully." << endl;
}

void animate::Draw()
{
    //Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn)
    {
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

void animate::update()
{
    //cause changes to the data for the next frame
    system.Step(command, _info);
    command = 0;
    if (mouseIn)
    {
        //mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5,
                               sf::Mouse::getPosition(window).y - 5);

        //mouse location text for sidebar:
        sidebar[SB_HEIGHT] = mouse_pos_string(window);
    }

    for (int i = 0; i < eqList.size(); i++)
    {
        sidebar[SB_EQ_LIST + (2 * i)] = eqList[i];
    }

    myTextLabel.setString("f(x) = " + _info->equation);
}
void animate::render()
{
    window.clear();
    Draw();
    window.display();
}

void animate::processEvents()
{
    sf::Event event;
    float mouseX, mouseY;

    //load-save
    fstream f;
    int k = SB_EQ_LIST;
    string load;

    while (window.pollEvent(event)) //or waitEvent
    {
        // check the type of the event...
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::TextEntered:
            if (event.text.unicode == 102 || event.text.unicode == 70){  //F key
                sidebar[SB_ACTION] = "Enter equation";
                input = true;
                equation = "";
                sidebar[SB_EQUATION] = "Equations: ";
            } 
            else if(input){
                if (equation.length() > 0 && event.text.unicode == 8){
                    equation = equation.substr(0, equation.length()-1);
                    sidebar[SB_EQUATION] = "Equations: " + equation;
                }
                else{
                    equation += static_cast<char>(event.text.unicode);
                    sidebar[SB_EQUATION] += static_cast<char>(event.text.unicode);
                }
            }
            break;
        // key pressed
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                if (!input){
                    sidebar[SB_ACTION] = "PANNING UP";
                    command = 8;
                    _info->origin.y -= 5;
                }
                break;
            case sf::Keyboard::Down:
                if (!input){
                    sidebar[SB_ACTION] = "PANNING DOWN";
                    command = 2;
                    _info->origin.y += 5;
                }
                break;
            case sf::Keyboard::Left:
                if (!input){
                    sidebar[SB_ACTION] = "PANNING LEFT";
                    command = 4;
                    _info->origin.x -= 5;
                }
                break;
            case sf::Keyboard::Right:
                if (!input){
                    sidebar[SB_ACTION] = "PANNING RIGHT";
                    command = 6;
                    _info->origin.x += 5;
                }
                break;
            case sf::Keyboard::I:
                if (!input){
                    sidebar[SB_ACTION] = "ZOOM IN";
                    _info->scale.x += 5;
                    _info->scale.y += 5;
                }
                break;
            case sf::Keyboard::O:
                if (!input){
                    sidebar[SB_ACTION] = "ZOOM OUT";
                    _info->scale.x -= 5;
                    _info->scale.y -= 5;
                }
                break;
            case sf::Keyboard::R:
                if (!input){
                    sidebar[SB_ACTION] = "RESET HISTORY";
                    sidebar[SB_EQUATION]= "Equations: ";
                    while (!eqList.empty())
                    {
                        eqList.pop_back();
                    }
                    for (int i = SB_EQ_LIST; i <= SB_EQ_LIST + 2 * (SB_EQ_LIMIT - 1); i += 2)
                    {
                        sidebar[i] = "";
                    }
                }
                break;
            case sf::Keyboard::L:
                if (!input){
                    sidebar[SB_ACTION] = "LOAD";
                    sidebar[SB_EQUATION]= "Equations: ";
                    f.open("history.txt");
                    if (f.fail())
                    {
                        cout << "ERROR: FAIL to open file." << endl;
                        exit(1);
                    }
                    //--reset--
                    while (!eqList.empty())
                    {
                        eqList.pop_back();
                    }
                    for (int i = SB_EQ_LIST; i <= SB_EQ_LIST + 2 * (SB_EQ_LIMIT - 1); i += 2)
                    {
                        sidebar[i] = "";
                    }
                    //-------
                    if (f.is_open())
                    {
                        while (getline(f, load))
                        {
                            eqList.push_back(load);
                            if (eqList.size() > 10)
                            {
                                eqList.erase(eqList.begin());
                            }
                        }
                        f.close();
                    }
                }
                break;
            case sf::Keyboard::S:
                if (!input){
                    sidebar[SB_ACTION] = "SAVE";
                    f.open("history.txt");
                    if (f.fail())
                    {
                        cout << "ERROR: FAIL to open file." << endl;
                        exit(1);
                    }
                    if (f.is_open())
                    {
                        for (int i = 0; i < eqList.size(); i++)
                        {
                            f << eqList[i] << endl;
                        }
                        f.close();
                    }
                }
                break;
            case sf::Keyboard::Enter:
                _info->equation = equation;
                eqList.push_back(equation);
                if (eqList.size() > 10)
                {
                    eqList.erase(eqList.begin());
                }
                equation = "";
                input = false;
                break;
            case sf::Keyboard::Escape:
                sidebar[SB_ACTION] = "ESC: EXIT";
                window.close();
                break;
            }
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
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sidebar[SB_ACTION] = "LEFT CLICK ";
                for (int i = SB_EQ_LIST; i <= SB_EQ_LIST + 2 * (SB_EQ_LIMIT - 1); i += 2)
                {
                    for (int j = sidebar.position()[i + 2].y - 15; j < sidebar.position()[i + 2].y + 15; j++)
                    {
                        //position = i+2 because of the spacings
                        if (sf::Mouse::getPosition(window).y == j && sf::Mouse::getPosition(window).x > WORK_PANEL)
                        {
                            if (sidebar[i] != "")
                                _info->equation = sidebar[i];
                        }
                    }
                }
            }
            else
            {
                sidebar[SB_EQUATION] = "RIGHT CLICK ";
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
    cout << endl
         << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
}

string mouse_pos_string(sf::RenderWindow &window)
{
    return "(" +
           to_string(sf::Mouse::getPosition(window).x) +
           ", " +
           to_string(sf::Mouse::getPosition(window).y) +
           ")";
}
