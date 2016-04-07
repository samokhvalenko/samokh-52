#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "menu.h"

using namespace sf;

class Road{
public:
    float w, h, dx, dy,x,y, speed;
    int dir;
    Image road_image;
    Texture road_texture, crashed_texture;
    Sprite road_sprite;
    float state;

    Road(float X, float Y, Texture &road_texture){
        road_sprite.setTexture(road_texture);
        road_sprite.setTextureRect(IntRect(585, 130, 37, 37));
        road_sprite.setPosition(X, Y);
        state = 100;

    }
};

void update(Road *road, Texture &crashed_texture)
	{
        road->state = road->state * 0.99991;
        if(road->state < 50){
            road->road_sprite.setTexture(crashed_texture);
            road->road_sprite.setTextureRect(IntRect(585, 130, 37, 37));
        }
	}

void game_start(RenderWindow &window){
    Clock clock;

    Texture back_game_texture; // setting our background
    back_game_texture.loadFromFile("back_game_texture.png");
    //Sprite back_game_sprite(back_game_texture);
    //back_game_sprite.setPosition(0, 0);

    Texture road_texture, crashed_road_texture;// creating texture for road. road`s texture will be loaded in this place.
    road_texture.loadFromFile("roads.png");
    crashed_road_texture.loadFromFile("roads_crashed.png");

    Sprite road_sprite_gorizontal;
    road_sprite_gorizontal.setTexture(road_texture);
    road_sprite_gorizontal.setTextureRect(IntRect(585, 130, 37, 37));
    road_sprite_gorizontal.setPosition(100, 100);

    Vector2f net_pos;

    std::vector< Road *> roads;
    int roads_count = 0;

    float x, y, X = 800, Y = 600;

    int i;
    bool isMove = false;
    bool oneSpritePT = false;

    while(window.isOpen()){
        clock.restart();
        float time = clock.getElapsedTime().asMicroseconds();
        time = time/800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

        if (Mouse::isButtonPressed(Mouse::Right) && isMove){
            x = pos.x;
            y = pos.y;
            X = div(x, 37).quot * 37;
            Y = div(y, 37).quot * 37;
            roads[roads_count-1]->road_sprite.setPosition(Vector2f(X, Y));
            isMove = false;
            oneSpritePT = false;
        }
        if (Mouse::isButtonPressed(Mouse::Left) && !isMove){
            if (road_sprite_gorizontal.getGlobalBounds().contains(pos.x, pos.y))
            {
                if(oneSpritePT == false){
                    roads.push_back(new Road(100, 100, road_texture));
                    roads_count++;
                }
                isMove = true;
                oneSpritePT = true;
            }
		}
        if (isMove) {
            roads[roads_count-1]->road_sprite.setPosition(pixelPos.x, pixelPos.y);
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            menu(window);
        }
        window.clear(Color(255,255,255));

        //window.draw(back_game_sprite);
        window.draw(road_sprite_gorizontal);
        if(roads_count > 0){
            for(i = 0; i < roads_count; i++){
                window.draw(roads[i]->road_sprite);
                update(roads[i], crashed_road_texture);
            }
        }
        window.display();
    }
}
