#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "menu.h"
#include "view.h"
#include "textures.h"
#include "roads.h"

enum status {IS_ROAD = 1, IS_CITY = 2};

void draw_all(RenderWindow &window, Sprites *spr){
    window.clear(Color::White);
    window.draw(spr->back_game_sprite);
    /*for(int i = 0; i < 50; i++){
        window.draw(spr->back_game_sprites[i]);
    }*/
    window.draw(spr->rectangle);
    window.draw(spr->rect_road);
    window.draw(spr->road_sprite_gorizontal);
    window.draw(spr->house_sprite);
    window.draw(spr->house_1_w_t);
}

void side_panel_move(Sprites *spr, time_t x, time_t y, View &view){
    spr->road_sprite_gorizontal.move(x, y);
    spr->rectangle.move(x, y);
    spr->house_sprite.move(x, y);
    spr->rect_road.move(x, y);
    spr->house_1_w_t.move(x, y);
    view.move(x, y);
}

bool drag_n_drop(RenderWindow &window, void * class_d_d, Sprites *spr, status status){
    bool isMove = false;
    bool OSPT = false;
    float x, y, X = 800, Y = 600;

    if(status == IS_ROAD){
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

            if (Mouse::isButtonPressed(Mouse::Right) && !spr->isObj(pos)){
                x = pos.x;
                y = pos.y;
                X = div(x, 37).quot * 37;
                Y = div(y, 37).quot * 37;
                tmp->roads[tmp->roads_count-1]->road_sprite.setPosition(Vector2f(X, Y));
                isMove = false;
                OSPT = false;
                return false;
            }

            if (Mouse::isButtonPressed(Mouse::Left) && !isMove){
                if (spr->road_sprite_gorizontal.getGlobalBounds().contains(pos.x, pos.y))
                {
                    if(OSPT == false){
                        tmp->roads.push_back(new Road(SRPX, SRPY, spr));
                        tmp->roads_count++;
                    }
                    isMove = true;
                    OSPT = true;
                }
            }

            if (isMove) {
                tmp->roads[tmp->roads_count-1]->road_sprite.setPosition(pos.x, pos.y);
            }
            window.clear(Color::White);
            draw_all(window, spr);
            draw_roads(tmp, window);
            window.display();
        }
    }
}

void game_start(RenderWindow &window){
    Font font;
    font.loadFromFile("arial.ttf");
    Clock clock;
    Vector2f net_pos;
    Sprites *spr = new Sprites(font);
    Roads *roads = new Roads();
    roads->roads_count = 0;

    Vector2i localPosition;
    Vector2f localPosf;

    float x, y, X = 800, Y = 600;
    //view.reset(sf::FloatRect(0, 0, 1366,768));
    view.reset(sf::FloatRect(0, 0, 1920,1080));
    bool isMove = false;
    float a;

    while(window.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        localPosition = Mouse::getPosition(window);
        localPosf = window.mapPixelToCoords(localPosition);

        if (localPosition.x < 10 && localPosf.x > 0 && view.getCenter().x > screen_width/2 + 3 ){
                side_panel_move(spr, -0.2*time, 0, view);
        }
		if (localPosition.x > window.getSize().x-50 && (view.getCenter().x + screen_width/2) + 2 < spr->back_game_image.getSize().x){
                side_panel_move(spr, 0.2*time, 0, view);
        }
		if (localPosition.y > window.getSize().y-100 && (view.getCenter().y + screen_heigh/2) + 5 < spr->back_game_image.getSize().y) {
                side_panel_move(spr, 0, 0.2*time, view);
        }
		if (localPosition.y < 15 && view.getCenter().y > screen_heigh/2 + 2) {
                side_panel_move(spr, 0, -0.2*time, view);
        }
        std::cout << view.getCenter().y << "\n";

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if(Mouse::isButtonPressed(Mouse::Left) && !isMove && spr->road_sprite_gorizontal.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            isMove = drag_n_drop(window, roads, spr, IS_ROAD);
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            view.setCenter(0, 0);
            //view.reset(sf::FloatRect(0, 0, 1366,768));
            view.reset(sf::FloatRect(0, 0, 1920,1080));
            window.setView(view);
            menu(window);
        }
		window.setView(view);

        window.clear(Color::White);

        std::cout << roads->roads_count;
        draw_all(window, spr);
        draw_roads(roads, window);
        window.display();
        }
}
