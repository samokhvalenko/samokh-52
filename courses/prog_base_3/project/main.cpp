#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"
#include "sqlite3.h"

using namespace sf;


int main()
{
    RenderWindow window(VideoMode(1366, 768), "Road Master", Style::Fullscreen);
    //RenderWindow window(VideoMode(1920, 1080), "Road Master", Style::Fullscreen);
    //RenderWindow window(VideoMode(1366, 768), "Road Master");
    //RenderWindow window(VideoMode(800, 700), "Road Master");

    window.setFramerateLimit(25);
    menu(window);
    return 0;
}
