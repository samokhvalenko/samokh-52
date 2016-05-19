#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "menu.h"

//#define SRPX 1200
//#define SRPY 100

#define SRPX 700
#define SRPY 100



enum status {ISROAD = 1};
int drag_n_drop(RenderWindow &window, void * class_d_d, Sprite road_sprite_gorizontal, status status);
using namespace sf;


class Road{
public:
    float w, h, dx, dy,x,y, speed;
    int dir;
    Image road_image;
    Texture road_texture, crashed_texture;
    Sprite road_sprite;
    float state;

    Road(float X, float Y){
        road_texture.loadFromFile("roads.png");
        road_sprite.setTexture(road_texture);
        road_sprite.setTextureRect(IntRect(585, 130, 37, 37));
        road_sprite.setPosition(X, Y);
        state = 100;

    }
};

void road_update(Road *road, Texture &crashed_texture)
{
    road->state = road->state * 0.99994;
    if(road->state < 50){
        road->road_sprite.setTexture(crashed_texture);
        road->road_sprite.setTextureRect(IntRect(585, 130, 37, 37));
    }
}

class Roads{
public:
    int roads_count;
    std::vector< Road *> roads;
    Texture road_texture;
    bool isRoad;

    Roads(){
        road_texture.loadFromFile("roads.png");
        isRoad = true;
    }
};

void draw_roads(Roads *roads, RenderWindow &window){
    for(int i = 0; i < roads->roads_count; i++){
        window.draw(roads->roads[i]->road_sprite);
    }
}

bool is_road(Roads *roads, Vector2f pos){
    for(int i = 0; i < roads->roads_count; i++){
        if(roads->roads[i]->road_sprite.getGlobalBounds().contains(pos))
            return true;
    }
    return false;
}

void game_start(RenderWindow &window){
    Clock clock;

    Texture back_game_texture; // setting our background
    back_game_texture.loadFromFile("back_game_texture.png");

    Texture road_texture, crashed_road_texture;// creating texture for road. road`s texture will be loaded in this place.
    road_texture.loadFromFile("roads.png");
    crashed_road_texture.loadFromFile("roads_crashed.png");

    Sprite road_sprite_gorizontal;
    road_sprite_gorizontal.setTexture(road_texture);
    road_sprite_gorizontal.setTextureRect(IntRect(585, 130, 37, 37));
    road_sprite_gorizontal.setPosition(SRPX, SRPY);

    Sprite ngS_h_r2bom;
    Texture ngT_h_r2bom;
    ngT_h_r2bom.loadFromFile("ng_h_r2bom.png");
    ngS_h_r2bom.setTexture(ngT_h_r2bom);
    ngS_h_r2bom.setPosition(300, 300);

    Vector2f net_pos;

    Roads *roads = new Roads();

    roads->roads_count = 0;

    float x, y, X = 800, Y = 600;

    int flag_new_game = 1;
    bool isMove = false;
    bool oneSpritePT = false;

    while(window.isOpen()){
        clock.restart();
        float time = clock.getElapsedTime().asMicroseconds();
        time = time/800;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

		/*Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

        if (Mouse::isButtonPressed(Mouse::Right) && isMove){
            x = pos.x;
            y = pos.y;
            X = div(x, 37).quot * 37;
            Y = div(y, 37).quot * 37;
            roads->roads[roads->roads_count-1]->road_sprite.setPosition(Vector2f(X, Y));
            isMove = false;
            oneSpritePT = false;
        }
        if (Mouse::isButtonPressed(Mouse::Left) && !isMove){
            if (road_sprite_gorizontal.getGlobalBounds().contains(pos.x, pos.y))
            {
                if(oneSpritePT == false){
                    roads->roads.push_back(new Road(SRPX, SRPY));
                    roads->roads_count++;
                }
                isMove = true;
                oneSpritePT = true;
            }
		}
        if (isMove) {
            roads->roads[roads->roads_count-1]->road_sprite.setPosition(pixelPos.x, pixelPos.y);
        }*/
        if(Mouse::isButtonPressed(Mouse::Left) && !isMove){
            isMove = drag_n_drop(window, roads,road_sprite_gorizontal, ISROAD);
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            menu(window);
        }

        window.clear(Color::White);

        std::cout << roads->roads_count;

        //help func for gamer
        if(flag_new_game == 1){
            window.draw(ngS_h_r2bom);
        }
        //help func for gamer

        window.draw(road_sprite_gorizontal);

        draw_roads(roads, window);
        window.display();
        }
}

int drag_n_drop(RenderWindow &window, void * class_d_d, Sprite road_sprite_gorizontal, status status){
    bool isMove = false;
    bool oneSpritePT = false;
    float x, y, X = 800, Y = 600;

    if(status == ISROAD){
        Roads *tmp = new Roads();
        tmp = (Roads*)class_d_d;
        while(1){

            Vector2i pixelPos = Mouse::getPosition(window);
            Vector2f pos = window.mapPixelToCoords(pixelPos);

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            if (Mouse::isButtonPressed(Mouse::Right) && isMove){
                x = pos.x;
                y = pos.y;
                X = div(x, 37).quot * 37;
                Y = div(y, 37).quot * 37;
                tmp->roads[tmp->roads_count-1]->road_sprite.setPosition(Vector2f(X, Y));
                isMove = false;
                oneSpritePT = false;
                return false;
            }

            if (Mouse::isButtonPressed(Mouse::Left) && !isMove){
                if (road_sprite_gorizontal.getGlobalBounds().contains(pos.x, pos.y))
                {
                    if(oneSpritePT == false){
                        tmp->roads.push_back(new Road(SRPX, SRPY));
                        tmp->roads_count++;
                    }
                    isMove = true;
                    oneSpritePT = true;
                }
            }

            if (isMove) {
                tmp->roads[tmp->roads_count-1]->road_sprite.setPosition(pixelPos.x, pixelPos.y);
            }
            window.clear(Color::White);

            window.draw(road_sprite_gorizontal);
            draw_roads(tmp, window);
            window.display();
        }
    }
}
