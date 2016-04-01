#include <SFML/Graphics.hpp>
#include "menu.h"

using namespace sf;

void game_start(RenderWindow &window){
    window.clear(Color::Black);

    Texture back_game_texture; // setting our background
    back_game_texture.loadFromFile("back_game_texture.png");
    Sprite back_game_sprite(back_game_texture);
    back_game_sprite.setPosition(0, 0);

    Texture road_texture;// creating texture for road. road`s texture will be loaded in this place.
    road_texture.loadFromFile("roads.png");

    Sprite road_sprite;
    road_sprite.setTexture(road_texture);
    road_sprite.setTextureRect(IntRect(263, 130, 37, 37));
    road_sprite.setPosition(800, 100);

    while(window.isOpen()){

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            menu(window);
        }

        window.draw(back_game_sprite);
        window.draw(road_sprite);

        window.display();
    }
}
