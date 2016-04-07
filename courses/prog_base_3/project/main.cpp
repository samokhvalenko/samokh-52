#include <SFML/Graphics.hpp>
#include <iostream>

#include "menu.h"

using namespace sf;


int main()
{
    RenderWindow window(VideoMode(1366, 768), "Road Master", sf::Style::Fullscreen);
    menu(window);
    return 0;
}
