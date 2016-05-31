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
#include "house.h"

enum status {IS_ROAD = 1, IS_HOUSE = 2};

void draw_all(RenderWindow &window, Sprites *spr, Houses * houses, Roads * roads){
    window.clear(Color::White);
    window.draw(spr->back_game_sprite);
    window.draw(spr->rectangle);
    window.draw(spr->rect_road);
    window.draw(spr->road_sprite_gorizontal);
    window.draw(spr->house_sprite);
    window.draw(spr->house_1_w_t);
    draw_houses(houses, window);
    draw_roads(roads, window);
}

void side_panel_move(Sprites *spr, time_t x, time_t y, View &view){
    spr->road_sprite_gorizontal.move(x, y);
    spr->rectangle.move(x, y);
    spr->house_sprite.move(x, y);
    spr->rect_road.move(x, y);
    spr->house_1_w_t.move(x, y);
    view.move(x, y);
}

bool drag_n_drop(RenderWindow &window, Roads* roads, Houses * houses, Sprites *spr, status status){
    bool isMove = false;
    bool OSPT = false;
    float x, y, X = 800, Y = 600;

    if(status == IS_ROAD){
        while(1){

            Vector2i pixelPos = Mouse::getPosition(window);
            Vector2f pos = window.mapPixelToCoords(pixelPos);

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            std::cout << "\nIs house: " << is_house(houses, pos);
            std::cout << "\nIs road: " << is_road(roads, pos);
            if (Mouse::isButtonPressed(Mouse::Right) && !spr->isSidepanel(pos) && !is_road(roads, pos) && !is_house(houses, pos)){
                x = pos.x;
                y = pos.y;
                X = div(x, 37).quot * 37;
                Y = div(y, 37).quot * 37;
                roads->roads[roads->roads_count-1]->road_sprite.setPosition(Vector2f(X, Y));
                isMove = false;
                OSPT = false;
                return false;
            }

            if (Mouse::isButtonPressed(Mouse::Left) && !isMove){
                if (spr->road_sprite_gorizontal.getGlobalBounds().contains(pos.x, pos.y))
                {
                    if(OSPT == false){
                        roads->roads.push_back(new Road(SRPX, SRPY, spr));
                        roads->roads_count++;
                    }
                    isMove = true;
                    OSPT = true;
                }
            }

            if (isMove) {
                roads->roads[roads->roads_count-1]->road_sprite.setPosition(pos.x, pos.y);
            }
            window.clear(Color::White);
            draw_all(window, spr, houses, roads);
            window.display();
        }
    }
    if(status == IS_HOUSE){
        while(1){

            Vector2i pixelPos = Mouse::getPosition(window);
            Vector2f pos = window.mapPixelToCoords(pixelPos);

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            if (Mouse::isButtonPressed(Mouse::Right) && !spr->isSidepanel(pos) && !is_road(roads, pos) && !is_house(houses, pos)){
                x = pos.x;
                y = pos.y;
                X = div(x, 37).quot * 37;
                Y = div(y, 37).quot * 37;
                houses->houses[houses->houses_count-1]->house_sprite.setPosition(Vector2f(X, Y));
                isMove = false;
                OSPT = false;
                return false;
            }

            if (Mouse::isButtonPressed(Mouse::Left) && !isMove){
                if (spr->house_sprite.getGlobalBounds().contains(pos.x, pos.y))
                {
                    if(OSPT == false){
                        houses->houses.push_back(new House(SRPX, SRPY, spr));
                        houses->houses_count++;
                    }
                    isMove = true;
                    OSPT = true;
                }
            }

            if (isMove) {
                houses->houses[houses->houses_count-1]->house_sprite.setPosition(pos.x, pos.y);
            }
            window.clear(Color::White);
            draw_all(window, spr, houses, roads);
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
    Houses *houses = new Houses();
    houses->houses_count = 0;
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
        //std::cout << view.getCenter().y << "\n";

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if(Mouse::isButtonPressed(Mouse::Left) && !isMove && spr->road_sprite_gorizontal.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            isMove = drag_n_drop(window, roads, houses, spr, IS_ROAD);
        }
        if(Mouse::isButtonPressed(Mouse::Left) && !isMove && spr->house_sprite.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            isMove = drag_n_drop(window, roads, houses, spr, IS_HOUSE);
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
        draw_all(window, spr, houses, roads);
        draw_roads(roads, window);
        window.display();
        }
}
