#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "menu.h"
#include "view.h"
#include "textures.h"
#include "city.h"
#include "roads.h"
#include "house.h"

void move_player(Player * player, RenderWindow &window, Vector2f pos);

void draw_all(RenderWindow &window, Sprites *spr, Houses * houses, Roads * roads, Player * player){
    window.clear(Color::White);
    window.draw(spr->back_game_sprite);

    draw_roads(roads, window);
    draw_houses(houses, window);
    window.draw(spr->rectangle);
    window.draw(spr->rect_road);
    window.draw(spr->road_sprite_gorizontal);
    window.draw(spr->house_sprite);
    window.draw(spr->house_1_w_t);
    window.draw(player->sprite);
}

void side_panel_move(Sprites *spr, time_t x, time_t y, View &view){
    spr->road_sprite_gorizontal.move(x, y);
    spr->rectangle.move(x, y);
    spr->house_sprite.move(x, y);
    spr->rect_road.move(x, y);
    spr->house_1_w_t.move(x, y);
    view.move(x, y);
}

bool drag_n_drop(RenderWindow &window, Roads* roads, Houses * houses, Sprites *spr, Player *player, status status){
    bool isMove = true;
    //bool OSPT = false;
    float x, y, X = 800, Y = 600;
    Vector2i pixelPos = Mouse::getPosition(window);
    Vector2f pos = window.mapPixelToCoords(pixelPos);

    if(status == IS_ROAD){
        while(1){
            Sprite road_sprite;
            Texture road_texture;
            pixelPos = Mouse::getPosition(window);
            pos = window.mapPixelToCoords(pixelPos);
            road_texture.loadFromFile("roads.png");
            road_sprite.setTexture(road_texture);
            road_sprite.setTextureRect(IntRect(585, 127, 37, 40));
            x = pos.x;
            y = pos.y;
            X = div(x, 37).quot * 37;
            Y = div(y, 40).quot * 40;
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            if (Mouse::isButtonPressed(Mouse::Right) && !spr->isSidepanel(pos, 37) && !is_road(roads, pos) && !is_house(houses, pos, IS_ROAD)){

                roads->roads.push_back(new Road(X, Y, spr));
                roads->roads_count++;
                roads->roads[roads->roads_count-1]->road_sprite.setPosition(Vector2f(X, Y));
            }

            if (Mouse::isButtonPressed(Mouse::Left)){
                if (spr->road_sprite_gorizontal.getGlobalBounds().contains(pos.x, pos.y))
                {
                    isMove = true;
                }
                else{
                    return false;
                }
            }

            if (isMove) {
                road_sprite.setPosition(X, Y);
            }
            window.clear(Color::White);
            draw_all(window, spr, houses, roads, player);
            window.draw(road_sprite);
            window.display();
        }
    }
    if(status == IS_HOUSE)
    while(1){
            Sprite house_sprite;
            Texture house_texture;

            house_texture.loadFromFile("house_small.png");
            house_sprite.setTexture(house_texture);

            pixelPos = Mouse::getPosition(window);
            pos = window.mapPixelToCoords(pixelPos);
            Event event;
            x = pos.x;
            y = pos.y;
            /*X = div(x, 105).quot * 105;
            Y = div(y, 120).quot * 120;*/
            X = div(x, 37).quot * 37;
            Y = div(y, 40).quot * 40;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            if (Mouse::isButtonPressed(Mouse::Right) && !spr->isSidepanel(pos, 37) && !is_road(roads, pos) && !is_house(houses, pos, IS_HOUSE)){
                houses->houses.push_back(new House(X, Y, spr));
                houses->houses_count++;
                houses->houses[houses->houses_count-1]->house_sprite.setPosition(Vector2f(X, Y));
            }

            if (Mouse::isButtonPressed(Mouse::Left)){
                if (spr->house_sprite.getGlobalBounds().contains(pos.x, pos.y))
                {
                    isMove = true;
                }
                else{
                    return false;
                }
            }

            if (isMove) {
                house_sprite.setPosition(X, Y);
            }
            window.clear(Color::White);
            draw_all(window, spr, houses, roads, player);
            window.draw(house_sprite);
            window.display();
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

    Player *player = new Player(0, 0);

    Vector2i localPosition;
    Vector2f localPosf;
    //player move
    float distance = 0, x_mov, y_mov;
    //player move
    view.reset(sf::FloatRect(0, 0, screen_width, screen_heigh));
    bool isMove = false;

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
        //player move
        if(Mouse::isButtonPressed(Mouse::Left) && player->sprite.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            player->isSelect = true;
            //player->isMove = true;
        }

        if(Mouse::isButtonPressed(Mouse::Right) && player->isSelect){
            x_mov = localPosf.x;
            y_mov = localPosf.y;
            player->isMove = true;
        }
        distance = sqrt((x_mov - player->x)*(x_mov - player->x) + (y_mov - player->y)*(y_mov - player->y));
        if (distance > 2){
            player->x += 0.1*time *(x_mov - player->x) / distance;
            player->y += 0.1*time *(y_mov - player->y) / distance;
        }
        else {
            player->isMove = false;
            //std::cout << "\npriehali\n";
        }
        //player move
        if(Mouse::isButtonPressed(Mouse::Left) && !isMove && spr->road_sprite_gorizontal.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            isMove = drag_n_drop(window, roads, houses, spr, player, IS_ROAD);
        }
        if(Mouse::isButtonPressed(Mouse::Left) && !isMove && spr->house_sprite.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            isMove = drag_n_drop(window, roads, houses, spr, player, IS_HOUSE);
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            view.setCenter(0, 0);
            view.reset(sf::FloatRect(0, 0, screen_width, screen_heigh));
            window.setView(view);
            menu(window);
        }


        window.clear(Color::White);

        //std::cout << roads->roads_count;
        draw_all(window, spr, houses, roads, player);
        player->update(time);
        window.draw(player->sprite);
        window.setView(view);
        window.display();
    }
}

void move_player(Player * player, RenderWindow &window, Vector2f pos){

    std::cout << "Is select: " << player->isSelect;
    Clock clock;

    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time / 800;
    float distance = 0;
    player->isMove = true;

    distance = sqrt((pos.x - player->x)*(pos.x - player->x) + (pos.y - player->y)*(pos.y - player->y));//считаем дистанцию (длину от точки А до точки Б). формула длины вектора

    if (distance > 2){//этим условием убираем дергание во время конечной позиции спрайта
        player->x += 0.1*time*(pos.x - player->x) / distance;//идем по иксу с помощью вектора нормали
        player->y += 0.1*time*(pos.y - player->y) / distance;//идем по игреку так же
    }
    else {
        player->isMove = false; std::cout << "priehali\n";
    }//говорим что уже никуда не идем и выводим веселое сообщение в консоль
}
