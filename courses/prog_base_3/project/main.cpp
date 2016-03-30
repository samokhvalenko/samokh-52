#include <SFML/Graphics.hpp>
#include <iostream>

#include "menu.h"

using namespace sf;


int main()
{
    RenderWindow window(VideoMode(800, 600), "Road Master");
    while(window.isOpen()){
    menu(window);
    window.clear(Color::Black);
    window.display();
    }
    return 0;
}
