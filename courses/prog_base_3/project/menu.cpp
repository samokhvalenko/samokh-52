#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "score.h"
#include "pre_game.h"
using namespace sf;

void menu(RenderWindow &window){

    Text new_game, instructions, score_table, exit;

    Sprite menu_bg;
    Texture menuBackground;

    bool escape_flag = true;

    Font font;
    font.loadFromFile("arial.ttf");

    new_game.setString("New game");
    new_game.setFont(font);
    new_game.setCharacterSize(30);
    new_game.setColor(Color::Black);
    new_game.setPosition(100, 30);

    score_table.setString("High score table");
    score_table.setFont(font);
    score_table.setCharacterSize(30);
    score_table.setColor(Color::Black);
    score_table.setPosition(100, 90);

    instructions.setString("Instructions");
    instructions.setFont(font);
    instructions.setCharacterSize(30);
    instructions.setColor(Color::Black);
    instructions.setPosition(100, 150);

    exit.setString("Exit");
    exit.setFont(font);
    exit.setCharacterSize(30);
    exit.setColor(Color::Black);
    exit.setPosition(100, 210);

	menuBackground.loadFromFile("menu_background.jpg");
	menu_bg.setTexture(menuBackground);

	while (window.isOpen())
	{
	    window.clear(Color::White);

	    new_game.setCharacterSize(30);
	    score_table.setCharacterSize(30);
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
                escape_flag = true;
            }
        }
        if (IntRect(100, 90, 220, 30).contains(Mouse::getPosition(window))){
            score_table.setCharacterSize(40);
            if (Mouse::isButtonPressed(Mouse::Left)){
                //std::cout << "Show scores";
                show_scores(window);
                escape_flag = true;
            }
        }
		if (IntRect(100, 150, 150, 30).contains(Mouse::getPosition(window))){
            instructions.setCharacterSize(40);
            if (Mouse::isButtonPressed(Mouse::Left)){
                //todo
            }

        }
		if (IntRect(100, 210, 45, 30).contains(Mouse::getPosition(window))){
            exit.setCharacterSize(40);
            if (Mouse::isButtonPressed(Mouse::Left)){
                //std::cout << "\nExit";
                window.close();
            }

        }

        if(Keyboard::isKeyPressed(Keyboard::Escape) && !escape_flag){
            fflush(stdout);
            //std::cout << "\nExit escape";
            window.close();
            return;
        }


        if(!Keyboard::isKeyPressed(Keyboard::Escape))
            escape_flag = false;

		window.draw(menu_bg);
		window.draw(new_game);
		window.draw(instructions);
		window.draw(score_table);
		window.draw(exit);

		window.display();
	}
}
