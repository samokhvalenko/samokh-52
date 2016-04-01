#include <SFML/Graphics.hpp>
#include <iostream>

#include "menu.h"

using namespace sf;


int main()
{
    RenderWindow window(VideoMode(900, 600), "Road Master");

    window.setFramerateLimit(15); // limit of frames, couse sfml do not have it.

    while(window.isOpen()){ // main cycle of our project
        menu(window);
        window.clear(Color::Black);
        window.display();
    }
    return 0;
}
