#include <SFML/Graphics.hpp>
#include "game.h"
using namespace sf;

void menu(RenderWindow &window){

    Text new_game, instructions, exit;

    Sprite menu_bg;
    Texture menuBackground;

    Font font;
    font.loadFromFile("arial.ttf");

    new_game.setString("New game");
    new_game.setFont(font);
    new_game.setCharacterSize(30);
    new_game.setColor(Color::Black);
    new_game.setPosition(100, 30);

    instructions.setString("Instructions");
    instructions.setFont(font);
    instructions.setCharacterSize(30);
    instructions.setColor(Color::Black);
    instructions.setPosition(100, 90);

    exit.setString("Exit");
    exit.setFont(font);
    exit.setCharacterSize(30);
    exit.setColor(Color::Black);
    exit.setPosition(100, 150);

	menuBackground.loadFromFile("menu_background.jpg");
	menu_bg.setTexture(menuBackground);

	while (window.isOpen())
	{
	    window.clear(Color::White);

	    new_game.setCharacterSize(30);
	    instructions.setCharacterSize(30);
	    exit.setCharacterSize(30);

	    sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


		if (IntRect(100, 30, 220, 30).contains(Mouse::getPosition(window))){
            new_game.setCharacterSize(40);
            if (Mouse::isButtonPressed(Mouse::Left)){
                game_start(window);
            }
        }
		if (IntRect(100, 90, 150, 30).contains(Mouse::getPosition(window))){
            instructions.setCharacterSize(40);
            if (Mouse::isButtonPressed(Mouse::Left))
                window.close();
        }
		if (IntRect(100, 150, 45, 30).contains(Mouse::getPosition(window))){
            exit.setCharacterSize(40);
            if (Mouse::isButtonPressed(Mouse::Left))
                window.close();
        }

		window.draw(menu_bg);
		window.draw(new_game);
		window.draw(instructions);
		window.draw(exit);

		window.display();
	}
}
