#include <SFML/Graphics.hpp>
#include "menu.h"

using namespace sf;

void game_start(RenderWindow &window){
    while(window.isOpen()){
        window.clear(Color::Black);

        Texture back_game_texture;
        back_game_texture.loadFromFile("back_game_texture.png");

        Sprite back_game_sprite(back_game_texture);

        back_game_sprite.setPosition(0, 0);

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            menu(window);
        }

        window.draw(back_game_sprite);

        window.display();
    }
}
