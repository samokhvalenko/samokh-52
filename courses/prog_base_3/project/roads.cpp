#include <SFML/Graphics.hpp>
#include "menu.h"

using namespace sf;

class Road{

    float dx, dy, x, y, speed;
    Image road_image;
    Texture road_texture;
    Sprite road_sprite;

    Road(Sprite s, float X, float Y){
        road_sprite = s;
        x = X;
        y = Y;
        road_sprite.setTextureRect(IntRect(263, 130, 37, 37));

    }


};

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

    Road roads[30];
    int roads_count = 0;

    int i;
    bool isMove = false;

    float dX = 0;
    float dY = 0;

    //time = time/800;

    while(window.isOpen()){

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            menu(window);
        }

        while(IntRect(800, 100, 37, 37).contains(Mouse::getPosition(window))){
            Vector2i pixelPos = Mouse::getPosition(window);
            Vector2f pos = window.mapPixelToCoords(pixelPos);
            if(Mouse::isButtonPressed(Mouse::Left)){

            }

        }

        window.draw(back_game_sprite);
        window.draw(road_sprite);
        for(int i = 0; i < roads_count)
            window.draw(roads[i]);

        window.display();
    }
}
