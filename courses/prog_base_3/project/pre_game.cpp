#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace sf;

std::string name_enter(RenderWindow &window){

    Font font;

    std::string str;
    String text;

    font.loadFromFile("arial.ttf");

    Text name, text_ent, too_many_letters;

    bool flag = false;
    float timer = 100;
    name.setFont(font);
    name.setCharacterSize(30);
    name.setColor(Color::Black);
    name.setPosition(500, 300);

    RectangleShape rect;
    rect.setFillColor(Color::Magenta);
    rect.setOutlineThickness(5);
    rect.setOutlineColor(Color::Black);
    rect.setSize(Vector2f(120, 40));
    rect.setPosition(500, 300);

    text_ent.setFont(font);
    text_ent.setString("Enter your name. Less then 8 letters please. When you will be ready, press \"spase\"");
    text_ent.setCharacterSize(30);
    text_ent.setColor(Color::Black);
    text_ent.setPosition(50, 200);

    too_many_letters.setFont(font);
    too_many_letters.setString("To many letters");
    too_many_letters.setCharacterSize(40);
    too_many_letters.setColor(Color::Red);
    too_many_letters.setPosition(730, 300);

    std::string s = "";

    while(window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered){
                if(Keyboard::isKeyPressed(Keyboard::BackSpace) && s.size()!=0){
                    if (!s.empty())
                        s.pop_back();
                }
                else if (s.size() >= 7) {
                    flag = true;
                    timer = 100;
                }
                else if (event.text.unicode < 128 && s.size() < 7 && !flag) {
                    s.push_back((char)event.text.unicode);
                }
                if(Keyboard::isKeyPressed(Keyboard::Space) && s.size()!=0){
                    return s;
                }
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Escape))
            return "escape_code";

        window.clear(Color::Green);
        name.setString(s);
        window.draw(rect);
        if(flag){
            window.draw(too_many_letters);
            timer = timer * 0.7;
            if(timer < 10)
                flag = false;
        }
        window.draw(name);
        window.draw(text_ent);
        window.display();
    }
}
