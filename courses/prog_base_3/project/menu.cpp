#include <SFML/Graphics.hpp>

using namespace sf;

void menu(RenderWindow &window){

    Texture menuTexture1, menuTexture2, menuTexture3, menuBackground;
    menuTexture1.loadFromFile("new_game.png");
	menuTexture2.loadFromFile("load_game.png");
	menuTexture3.loadFromFile("exit.png");
	menuBackground.loadFromFile("menu_background.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(130, 50, 200, 30).contains(Mouse::getPosition(window))) { menu1.setColor(Color(19, 0, 255)); menuNum = 1; }
		if (IntRect(130, 100, 150, 30).contains(Mouse::getPosition(window))) { menu2.setColor(Color(19, 0, 255)); menuNum = 2; }
		if (IntRect(130, 150, 45, 30).contains(Mouse::getPosition(window))) { menu3.setColor(Color(19, 0, 255)); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
                //ride(window);
			if (menuNum == 2) {
                //add_way(window);
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
