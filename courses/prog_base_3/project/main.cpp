#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"

using namespace sf;


int main()
{
    RenderWindow window(VideoMode(1366, 768), "Road Master", Style::Fullscreen);
    //RenderWindow window(VideoMode(800, 700), "Road Master");

    window.setFramerateLimit(30);
    menu(window);
    return 0;
}
