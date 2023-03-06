#include <iostream>
#include"SFML/Graphics.hpp"
#include<queue>
using namespace std;
float M_PI = 3.1415926535;
void killJosephus(queue<int>& Q, int skip) {
    int temp, killed;
    for (int i = 0;i < skip;i++) {
        temp = Q.front();
        Q.pop();
        Q.push(temp);
    }
    killed = Q.front();
    Q.pop();
    cout << "player " << killed << " killed" << endl;
}
int main() {

    int total = 0, skip = 0;                                              //take user input
    cout << "enter total number of soldiers: "; cin >> total;
    if (total <= 0) {
        while (total < 0) {
            cout << "enter total soldiers again: "; cin >> total; cout << endl;
        }
    }
    cout << endl;
    cout << "enter soldiers to skip(positive): ";
    cin >> skip;
    if (skip <= 0) {
        while (skip < 0) {
            cout << "enter skip again: "; cin >> skip; cout << endl;
        }
    }

    queue<int> Q;

    for (int i = 1;i <= total;i++) {
        Q.push(i);
    }

    string particularsol; int temp;
    sf::RenderWindow window(sf::VideoMode(1400, 1400), "Test");            //create window
    int numberofsoldiers;
    float* x, * y;                                            //initialize arrays for circle dimensions
    sf::Font font;
    if (!font.loadFromFile("C:/font/Pacifico.ttf"))                //check if font file opens
        return EXIT_FAILURE;
    sf::Text text;
    text.setFont(font);                                 //set font                  
    sf::Event e;
    sf::Text title;                                    //create winner text variable
    title.setCharacterSize(32);                        //set size of font
    title.setFont(font);
    title.setPosition(400, 400);

    //set position of font in screen

    bool flag = false;
    while (window.isOpen()) {                           //open window and start displaying
        flag = false;
        while (window.pollEvent(e)) {

            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                flag = true;                                //sets flag as a condition
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            if (flag && Q.size() != 1)                      //conditions of continuing killing people
                killJosephus(Q, skip);                    //<;) evil evil
        }
        numberofsoldiers = Q.size();
        double degrees = 0;
        x = new float[numberofsoldiers];
        y = new float[numberofsoldiers];
        double radius = 400;
        int parameter = 700;
        if (Q.size() > 50) {
            title.setCharacterSize(18);
            if (Q.size() > 100)
                title.setCharacterSize(8);
        }
        for (int i = 0;i < numberofsoldiers;i++) {            //divides circle in n parts and sets corodinates in x and y array
            degrees = i * (360 / numberofsoldiers);
            float radian = (degrees * (M_PI / 180));
            x[i] = parameter + radius * cos(radian);
            y[i] = parameter + radius * sin(radian);
        }
        for (int i = 0;i < Q.size();i++) {                //print n number of soldier 
            particularsol = to_string(Q.front());
            temp = Q.front();
            Q.pop();
            Q.push(temp);
            title.setString(particularsol);
            title.setPosition(x[i], y[i]);
            title.setCharacterSize(32);
            window.draw(title);
        }
        window.draw(title);
        window.display();

        window.clear();
        if (Q.size() == 1) {


            sf::Text win;                      //set size of font
            win.setFont(font);
            string winner1 = to_string(Q.front());
            string msg = "winner is ";
            win.setString(msg);
            win.setPosition(600, 600);
            win.setCharacterSize(50);
            win.setFillColor(sf::Color::White);
            window.draw(win);
            win.setString(winner1);
            win.setPosition(800, 600);
            win.setFillColor(sf::Color::White);
            window.draw(win);

            window.display();
            system("pause");
        }
    }

    cout << endl << "player " << Q.front() << " freed!!!" << endl << endl;


    return 0;
}