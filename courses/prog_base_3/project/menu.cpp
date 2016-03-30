#include <SFML/Graphics.hpp>

using namespace sf;

void menu(RenderWindow &window){

    Texture menuTexture1, menuTexture2, menuTexture3, menuTexture1_2, menuTexture2_2, menuTexture3_2, menuBackground;

    menuTexture1.loadFromFile("new_game.png");
	menuTexture2.loadFromFile("load_game.png");
	menuTexture3.loadFromFile("exit.png");

	menuTexture1_2.loadFromFile("new_game2.png");
	menuTexture2_2.loadFromFile("load_game2.png");
	menuTexture3_2.loadFromFile("exit2.png");
	//If you want to see normal background, just uncomment the line under this text
	//menuBackground.loadFromFile("menu_background.jpg");
    menuBackground.loadFromFile("menu_background_for_Hadyniak.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;

	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
	    menu1.setTexture(menuTexture1);
	    menu2.setTexture(menuTexture2);
	    menu3.setTexture(menuTexture3);

		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(135, 40, 220, 30).contains(Mouse::getPosition(window))){
            menuNum = 1;
            menu1.setTexture(menuTexture1_2);
        }
		if (IntRect(130, 100, 150, 30).contains(Mouse::getPosition(window))){
            menuNum = 2;
            menu2.setTexture(menuTexture2_2);
        }
		if (IntRect(130, 150, 45, 30).contains(Mouse::getPosition(window))){
            menuNum = 3;
            menu3.setTexture(menuTexture3_2);
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
                window.close();
                isMenu = false;
			if (menuNum == 2) {
                window.close();
                isMenu = false;
            }
			if (menuNum == 3)  {
			     window.close();
			     isMenu = false;
            }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}
