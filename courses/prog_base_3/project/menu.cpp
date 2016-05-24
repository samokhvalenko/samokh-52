#include <SFML/Graphics.hpp>
#include "game.h"
using namespace sf;

void menu(RenderWindow &window){

    Texture menuTexture1, menuTexture2, menuTexture3, menuTexture1_2, menuTexture2_2, menuTexture3_2, menuBackground;

    menuTexture1.loadFromFile("new_game.png");// see names of files
	menuTexture2.loadFromFile("load_game.png");
	menuTexture3.loadFromFile("exit.png");

	menuTexture1_2.loadFromFile("new_game2.png");// with bigger letters
	menuTexture2_2.loadFromFile("load_game2.png");
	menuTexture3_2.loadFromFile("exit2.png");

	menuBackground.loadFromFile("menu_background.jpg");

	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);

	menu1.setPosition(100, 30); // sets the position of sprite
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(0, 0);

	while (window.isOpen())
	{
	    window.clear(Color::White);
	    menu1.setTexture(menuTexture1);
	    menu2.setTexture(menuTexture2);
	    menu3.setTexture(menuTexture3);

	    sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


		if (IntRect(135, 40, 220, 30).contains(Mouse::getPosition(window))){
            menu1.setTexture(menuTexture1_2);
            if (Mouse::isButtonPressed(Mouse::Left)){
                game_start(window);
            }
        }
		if (IntRect(130, 100, 150, 30).contains(Mouse::getPosition(window))){
            menu2.setTexture(menuTexture2_2);
            if (Mouse::isButtonPressed(Mouse::Left))
                window.close();
        }
		if (IntRect(130, 150, 45, 30).contains(Mouse::getPosition(window))){
            menu3.setTexture(menuTexture3_2);
            if (Mouse::isButtonPressed(Mouse::Left))
                window.close();
        }

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}
