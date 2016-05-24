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

            if (Mouse::isButtonPressed(Mouse::Right) && !spr->isObj(tmp->roads[tmp->roads_count-1]->road_sprite)){
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
            spr->Sprites::draw_bgs(window);
            window.draw(spr->rectangle);
            window.draw(spr->road_sprite_gorizontal);
            draw_roads(tmp, window);
            window.display();
        }
    }
}

void game_start(RenderWindow &window){
    Clock clock;
    Vector2f net_pos;
    Sprites *spr = new Sprites();
    Roads *roads = new Roads();
    roads->roads_count = 0;

    Vector2i localPosition;

    float x, y, X = 800, Y = 600;
    view.reset(sf::FloatRect(0, 0, 1366,768));
    bool isMove = false;

    while(window.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        localPosition = Mouse::getPosition(window);

        if (localPosition.x < 3){
                view.move(-0.2*time, 0);
                spr->road_sprite_gorizontal.move(-0.2*time, 0);
                spr->rectangle.move(-0.2*time, 0);
        }
		if (localPosition.x > window.getSize().x-10) {
                view.move(0.2*time, 0);
                spr->road_sprite_gorizontal.move(0.2*time, 0);
                spr->rectangle.move(0.2*time, 0);
        }
		if (localPosition.y > window.getSize().y-10) {
                view.move(0, 0.2*time);
                spr->road_sprite_gorizontal.move(0, 0.2*time);
                spr->rectangle.move(0, 0.2*time);
        }
		if (localPosition.y < 3) {
                view.move(0, -0.2*time);
                spr->road_sprite_gorizontal.move(0, -0.2*time);
                spr->rectangle.move(0, -0.2*time);
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if(Mouse::isButtonPressed(Mouse::Left) && !isMove){
            isMove = drag_n_drop(window, roads, spr, IS_ROAD);
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            view.setCenter(0, 0);
            view.reset(sf::FloatRect(0, 0, 1366,768));
            window.setView(view);
            menu(window);
        }
		window.setView(view);

        window.clear(Color::White);

        std::cout << roads->roads_count;
        spr->Sprites::draw_bgs(window);
        window.draw(spr->road_sprite_gorizontal);
        draw_roads(roads, window);
        window.display();
        }
}
