#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "view.h"
#include "cars.h"
#include "db.h"
#include "pre_game.h"
#include "factory.h"
#include "gas_station.h"

#define car_start_pos_x 250
#define car_start_pos_y 19

//void move_worker(Worker * worker, RenderWindow &window, float time, float &CurrentFrame, Houses * houses, Roads *roads);
void drag_n_drop(RenderWindow &window, Roads* roads, Houses * houses, Sprites *spr, Cars *cars, Player *player, Factories *facts, Gas_stations *stations, status status);

void draw_all(RenderWindow &window, Sprites *spr, Houses * houses, Roads * roads, Player * player, Cars *cars, Factories *facts, Gas_stations *stations){
    window.clear(Color::White);
    window.draw(spr->back_game_sprite);
    roads->draw_roads(window);
    cars->draw_cars(window);
    houses->draw_houses(window);
    facts->draw_factories(window);
    stations->draw_stations(window);
    window.draw(spr->high_rect);
    window.draw(spr->side_rectangle);
    window.draw(spr->rect_road);

    window.draw(spr->road_sprite_side_panel);
    window.draw(spr->down_rect);
    window.draw(spr->house_sprite);
    window.draw(spr->house_1_w_t);
    window.draw(player->cash_t);
    window.draw(player->cash_t2);
    window.draw(player->oil_t);
    window.draw(player->oil_t2);
    window.draw(player->t_name);
    window.draw(spr->fact_sprite);
    window.draw(spr->fact_text);
    window.draw(spr->gas_sprite);
    window.draw(spr->gas_text);
    //window.draw(worker->sprite);
    window.draw(spr->rep_br_r);
    window.draw(spr->rep_br);
    window.draw(spr->rep_all_r_r);
    window.draw(spr->rep_all_r);
    window.draw(spr->rep_all_r_price);
    window.draw(spr->rep_br_price);
    window.draw(spr->road_text);
    window.draw(spr->house_text);
    window.draw(spr->car_sprite_1);
    window.draw(spr->car_sprite_2);
    window.draw(spr->car_sprite_3);
    window.draw(spr->car_1_price);
    window.draw(spr->car_2_price);
    window.draw(spr->car_3_price);
}

void side_panel_move(Sprites *spr, time_t x, time_t y, View &view, Player *player){
    spr->road_sprite_side_panel.move(x, y);
    spr->side_rectangle.move(x, y);
    spr->house_sprite.move(x, y);
    spr->rect_road.move(x, y);
    spr->down_rect.move(x, y);
    spr->high_rect.move(x, y);
    spr->house_1_w_t.move(x, y);
    spr->rep_br.move(x, y);
    spr->rep_br_r.move(x, y);
    spr->gas_sprite.move(x, y);
    spr->gas_text.move(x, y);
    spr->rep_all_r_price.move(x, y);
    spr->rep_br_price.move(x, y);
    spr->rep_all_r_r.move(x, y);
    spr->rep_all_r.move(x, y);
    spr->road_text.move(x, y);
    spr->house_text.move(x, y);
    spr->fact_sprite.move(x, y);
    spr->fact_text.move(x, y);
    spr->car_sprite_1.move(x, y);
    spr->car_sprite_2.move(x, y);
    spr->car_sprite_3.move(x, y);
    spr->car_1_price.move(x, y);
    spr->car_2_price.move(x, y);
    spr->car_3_price.move(x, y);
    player->cash_t.move(x, y);
    player->oil_t.move(x, y);
    player->oil_t2.move(x, y);
    player->cash_t2.move(x, y);
    player->t_name.move(x, y);
    view.move(x, y);

}

void game_over(RenderWindow &window, Player *player, int sec){
    Sprite end_game_spr;
    Texture end_game_texture;
    RectangleShape rect;
    Font font;
    font.loadFromFile("arial.ttf");

    Text end_game_text("Game over", font, 50);
    end_game_text.setColor(Color::Red);
    end_game_text.setPosition(490, 300);

    rect.setSize(Vector2f(500, 200));
    rect.setFillColor(Color::Green);
    rect.setOutlineThickness(10);
    rect.setOutlineColor(Color::Black);
    rect.setPosition(383, 250);

    db_t * db = db_new("players.db");

    int score = player->score/sec;

    db_insert_player(db, (char *)player->name.c_str(), score);

    db_free(db);

    while(window.isOpen()){

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            view.setCenter(0, 0);
            view.reset(sf::FloatRect(0, 0, screen_width, screen_heigh));
            window.setView(view);
            menu(window);
        }

        window.draw(rect);
        window.draw(end_game_text);
        window.display();
    }
}

void game_start(RenderWindow &window){

    Music music;
    music.openFromFile("anw1489_20_the-end-2.ogg");
    music.play();

    std::string name = name_enter(window);
    if(name == "escape_code")
        return;
    Player *player = new Player(name);

    Font font;

    std::string str;
    String text;
    font.loadFromFile("arial.ttf");


    Clock clock;

    Vector2f net_pos;

    //Player *player = new Player("Stas");
    player->cash_t.setFont(font);
    player->oil_t.setFont(font);
    player->cash_t2.setFont(font);
    player->oil_t2.setFont(font);
    player->t_name.setFont(font);

    float CurrentFrame = 0;
    float x_st, y_st, time_tmp;
    bool buy_flag = false;

    Sprites *spr = new Sprites(font);

    Houses *houses = new Houses();

    Factories *facts = new Factories();

    Gas_stations *stations = new Gas_stations();

    Roads *roads = new Roads();

    int road_select = 0;

    Cars *cars = new Cars;
    cars->buy_car(1, spr);
    int i;
    for(i = 5; i < 20; i++){
        x_st = road_width * i;
        y_st = road_heigh * 6;
        roads->roads.push_back(new Road(x_st, y_st, spr));
        roads->roads[roads->roads.size()-1]->road_sprite.setPosition(Vector2f(x_st, y_st));
    }

    houses->houses.push_back(new House( 370, 120, spr));


    //Worker *worker = new Worker(0, 0);

    Vector2i localPosition;
    Vector2f localPosf;
    float distance = 0, x_mov, y_mov;
    view.reset(FloatRect(0, 0, screen_width, screen_heigh));
    bool isMove = false, rep_flag = false;

    spr->rep_br.setFont(font);
    spr->rep_all_r.setFont(font);
    spr->rep_all_r_price.setFont(font);
    spr->rep_br_price.setFont(font);
    spr->road_text.setFont(font);
    spr->house_text.setFont(font);
    spr->no_money_text.setFont(font);
    spr->house_or.setFont(font);
    spr->road_nr.setFont(font);
    spr->fact_text.setFont(font);
    spr->gas_text.setFont(font);
    spr->car_1_price.setFont(font);
    spr->car_2_price.setFont(font);
    spr->car_3_price.setFont(font);

    Clock clock2; // starts the clock
    Time elapsed1 = clock2.getElapsedTime();

    int sec  = elapsed1.asSeconds();


    while(window.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/200;
        localPosition = Mouse::getPosition(window);
        localPosf = window.mapPixelToCoords(localPosition);
        elapsed1 = clock2.getElapsedTime();
        sec  = elapsed1.asSeconds();

        if(player->cash < 0){
            game_over(window, player, sec);
        }

        if (localPosition.x < 10 && localPosf.x > 0 && view.getCenter().x > screen_width/2 + 3 ){
                side_panel_move(spr, -0.2*time/3, 0, view, player);

        }
		if (localPosition.x > window.getSize().x-10 && (view.getCenter().x + screen_width/2) + 2 < spr->back_game_image.getSize().x){
                side_panel_move(spr, 0.2*time/3, 0, view, player);

        }
		if (localPosition.y > window.getSize().y-10 && (view.getCenter().y + screen_heigh/2) + 5 < spr->back_game_image.getSize().y) {
                side_panel_move(spr, 0, 0.2*time/3, view, player);
        }
		if (localPosition.y < 15 && view.getCenter().y > screen_heigh/2 + 2){
                side_panel_move(spr, 0, -0.2*time/3, view, player);
        }
        window.setView(view);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        /*if(Mouse::isButtonPressed(Mouse::Left) && worker->sprite.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            worker->isSelect = true;
        }
        if(Mouse::isButtonPressed(Mouse::Left) && worker->isSelect == true && !worker->sprite.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            worker->isSelect = false;
        }*/

        // cars
        if(Mouse::isButtonPressed(Mouse::Left) && spr->car_1spr(localPosf) && !buy_flag)
            if(player->cash >= 1500){
                cars->buy_car(1, spr);
                player->cash-=1500;
                std::cout << "\nFirst car";
                buy_flag = true;
            }
        if(Mouse::isButtonPressed(Mouse::Left) && spr->car_2spr(localPosf) && !buy_flag)
            if(player->cash >= 2500){
                cars->buy_car(2, spr);
                player->cash-=2500;
                std::cout << "\nSecond car";
                buy_flag = true;
            }
        if(Mouse::isButtonPressed(Mouse::Left) && spr->car_3spr(localPosf) && !buy_flag)
            if(player->cash >= 4000){
                cars->buy_car(3, spr);
                player->cash-=4000;
                std::cout << "\nThird car";
                buy_flag = true;
            }
        if(!Mouse::isButtonPressed(Mouse::Left) && buy_flag)
            buy_flag = false;
        //cars

        if(Mouse::isButtonPressed(Mouse::Left) && spr->is_br_road_rep(localPosf) && !rep_flag){
            roads->repair_broken_roads(player);
            std::cout << "\nrep!\n";
            rep_flag = true;
        }

        if(Mouse::isButtonPressed(Mouse::Left) && spr->is_all_road_rep(localPosf) && !rep_flag){
            roads->repair_all_roads(player);
            rep_flag = true;
        }
        if(!Mouse::isButtonPressed(Mouse::Left) && rep_flag)
            rep_flag = false;

        if(Mouse::isButtonPressed(Mouse::Left) && !roads->is_road(localPosf, OTHER))
            spr->road_selected = false;

        if(Mouse::isButtonPressed(Mouse::Left) && roads->is_road(localPosf, IS_REPAIRING)){
            road_select = roads->is_road(localPosf, IS_REPAIRING);
            spr->road_selected = true;
        }

        /*if(Mouse::isButtonPressed(Mouse::Right) && worker->isSelect){
            x_mov = localPosf.x;
            y_mov = localPosf.y;
            worker->set_mov(Vector2f(x_mov,y_mov));
            worker->isMove = true;
        }
        distance = sqrt((worker->pos_mov.x - worker->x)*(worker->pos_mov.x - worker->x) + (worker->pos_mov.y - worker->y)*(worker->pos_mov.y - worker->y));*/
        if(Mouse::isButtonPressed(Mouse::Left) && !isMove && spr->road_sprite_side_panel.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            time_tmp = time;
            drag_n_drop(window, roads, houses, spr, cars, player, facts, stations, IS_ROAD);
            isMove = false;
            time = time_tmp;
        }
        if(Mouse::isButtonPressed(Mouse::Left) && !isMove && spr->house_sprite.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            time_tmp = time;
            drag_n_drop(window, roads, houses, spr, cars, player, facts, stations, IS_HOUSE);
            isMove = false;
            time = time_tmp;
        }
        if(Mouse::isButtonPressed(Mouse::Left) && !isMove && spr->fact_sprite.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            time_tmp = time;
            drag_n_drop(window, roads, houses, spr, cars, player, facts, stations, FACTORY);
            isMove = false;
            time = time_tmp;
        }
        if(Mouse::isButtonPressed(Mouse::Left) && !isMove && spr->gas_sprite.getGlobalBounds().contains(localPosf.x, localPosf.y)){
            time_tmp = time;
            drag_n_drop(window, roads, houses, spr, cars, player, facts, stations, GAS);
            isMove = false;
            time = time_tmp;
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            game_over(window, player, sec);
        }

        draw_all(window, spr, houses, roads, player, cars, facts, stations);
        //worker->move_worker(window, time, CurrentFrame, houses, roads);
        cars->update(roads, houses, player, cars, stations);
        roads->Roads::rs_update(time, spr);
        player->update(facts);

        window.display();
    }
}



void drag_n_drop(RenderWindow &window, Roads* roads, Houses * houses, Sprites *spr, Cars *cars, Player *player, Factories *facts, Gas_stations *stations, status status){
    bool isMove = true;
    Clock clock;
    float x, y, X, Y;
    Vector2i pixelPos = Mouse::getPosition(window);
    Vector2f pos = window.mapPixelToCoords(pixelPos);
    bool flag = false, no_money_flag = false, near_rr_flag = false, not_near_house = false, not_on_road = false, not_on_right_road = false, not_on_house = false, not_on_side_panel = false, not_on_factory = false, not_on_gasst = false;
    float timer = 100, not_near_road_timer = 1;
    bool is_road_up = false, is_road_down = false, is_road_l = false, is_road_r = false, near_road = false, near_road1 = false, near_road2 = false, near_road3 = false;
    if(status == IS_ROAD){
        while(1){
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time/300;
            Sprite road_sprite;
            pixelPos = Mouse::getPosition(window);
            pos = window.mapPixelToCoords(pixelPos);
            road_sprite = spr->road_sprite_side_panel;
            x = pos.x;
            y = pos.y;
            X = div(x, road_width).quot * road_width;
            Y = div(y, road_heigh).quot * road_heigh;
            Event event;
            while (window.pollEvent(event))
                if (event.type == Event::Closed)
                    window.close();
            not_on_side_panel =  !spr->isSidepanel(pos, road_width);
            not_on_house = !houses->is_house(Vector2f(pos.x, pos.y + 80), IS_ROAD);
            not_on_factory = !facts->is_factory(Vector2f(X, Y + 80), OTHER_F);
            if ( not_on_factory && !flag && Mouse::isButtonPressed(Mouse::Right) && not_on_side_panel && !roads->is_road(Vector2f(X, Y), OTHER) && !roads->is_road(pos, OTHER) && not_on_house){
                bool near_roads = false;

                is_road_up = roads->is_road(Vector2f(X, Y - road_heigh), OTHER);
                is_road_down = roads->is_road(Vector2f(X, Y + road_heigh), OTHER);
                is_road_l = roads->is_road(Vector2f(X - road_width, Y), OTHER);
                is_road_r = roads->is_road(Vector2f(X + road_width, Y), OTHER);

                if(is_road_up || is_road_down || is_road_l || is_road_r)
                    near_roads = true;

                if(player->cash >= 150 && near_roads && roads->check_roads(Vector2f(X, Y))){
                    roads->roads.push_back(new Road(X, Y, spr));
                    roads->roads[roads->roads.size()-1]->road_sprite.setPosition(Vector2f(X, Y));
                    flag = true;
                    player->cash-=150;
                }
                else if(player->cash < 150){
                    spr->no_money_text.setPosition(X, Y - 10);
                    no_money_flag = true;
                    timer = 100;
                }
                else if(!near_roads){
                    timer = 100;
                    spr->road_nr.setPosition(X, Y - 10);
                    near_rr_flag = true;
                }
            }

            if( !Mouse::isButtonPressed(Mouse::Right))
                flag = false;

            if (Mouse::isButtonPressed(Mouse::Left)){
                if (spr->road_sprite_side_panel.getGlobalBounds().contains(pos.x, pos.y))
                    isMove = true;
                else
                    return;
            }

            if (isMove)
                road_sprite.setPosition(X, Y);

            window.clear(Color::White);
            player->update(facts);
            draw_all(window, spr, houses, roads, player, cars, facts, stations);
            window.draw(road_sprite);
            window.draw(cars->cars[0]->sprite);
            if(near_rr_flag && timer > 1){
                window.draw(spr->road_nr);
                timer *=0.85;
            }
            if(no_money_flag && timer > 1){
                window.draw(spr->no_money_text);
                timer *=0.85;
            }
            else
                no_money_flag = false;
            window.display();
        }
    }
    if(status == IS_HOUSE)
    while(1){
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time/300;
            Sprite house_sprite;
            house_sprite = spr->house_sprite;
            pixelPos = Mouse::getPosition(window);
            pos = window.mapPixelToCoords(pixelPos);
            Event event;
            x = pos.x;
            y = pos.y;
            X = div(x, road_width).quot * road_width;
            Y = div(y, road_heigh).quot * road_heigh;
            while (window.pollEvent(event))
                if (event.type == Event::Closed)
                    window.close();

            near_road1 = roads->is_road(Vector2f(X, Y + 121), OTHER);
            near_road2 = roads->is_road(Vector2f(X + road_width, Y + 121), OTHER);
            near_road3 = roads->is_road(Vector2f(X + road_width * 2, Y + 121), OTHER);
            not_near_house = !houses->is_house(pos, IS_HOUSE);
            not_on_road = !roads->is_road(Vector2f(X + road_width, Y + 80), OTHER);
            not_on_right_road = !roads->is_road(Vector2f(pos.x + 106 - road_width + 5, pos.y + 80), OTHER);
            if(Mouse::isButtonPressed(Mouse::Right) && !near_road1 && !near_road2 && !near_road3){
                not_near_road_timer = 100;
                spr->house_or.setPosition(X, Y - 10);
                near_road = false;
            }
            not_on_factory = !facts->is_factory(Vector2f(X, Y), IS_HOUSE_F);
            not_on_side_panel = !spr->isSidepanel(pos, road_width);

            if (not_on_factory && !stations->is_station(Vector2f(X, Y), IS_HOUSE_F) && !flag && Mouse::isButtonPressed(Mouse::Right) && not_on_side_panel && not_on_road && not_near_house && near_road1 && not_on_right_road && near_road2 && near_road3){
                 if(player->cash >= 500){
                    houses->houses.push_back(new House(X, Y, spr));
                    houses->houses[houses->houses.size()-1]->house_sprite.setPosition(Vector2f(X, Y));
                    player->cash-=500;
                    houses->houses_sort();
                    flag = true;
                 }
                 else if(player->cash < 500){
                    spr->no_money_text.setPosition(X, Y - 10);
                    no_money_flag = true;
                    timer = 100;
                 }
            }
            if( !Mouse::isButtonPressed(Mouse::Right))
                flag = false;
            if (Mouse::isButtonPressed(Mouse::Left)){
                if (spr->house_sprite.getGlobalBounds().contains(pos.x, pos.y))
                    isMove = true;
                else
                    return;
            }

            if (isMove)
                house_sprite.setPosition(X, Y);
            window.clear(Color::White);
            player->update(facts);
            draw_all(window, spr, houses, roads, player, cars, facts, stations);
            window.draw(house_sprite);
            if(!near_road && not_near_road_timer > 1){
                window.draw(spr->house_or);
                not_near_road_timer *=0.85;
            }
            if(no_money_flag && timer > 1){
                window.draw(spr->no_money_text);
                timer *=0.85;
            }
            else
                no_money_flag = false;
            window.display();
        }
    if(status == FACTORY)
    while(1){
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time/300;
            Sprite fact_sprite;
            fact_sprite = spr->fact_sprite;
            pixelPos = Mouse::getPosition(window);
            pos = window.mapPixelToCoords(pixelPos);
            Event event;
            x = pos.x - 50;
            y = pos.y - 50;
            X = div(x, road_width).quot * road_width;
            Y = div(y, road_heigh).quot * road_heigh;
            while (window.pollEvent(event))
                if (event.type == Event::Closed)
                    window.close();

            near_road1 = roads->is_road(Vector2f(X, Y + 160), OTHER);
            near_road2 = roads->is_road(Vector2f(X + road_width, Y + 160), OTHER);
            near_road3 = roads->is_road(Vector2f(X + road_width * 2, Y + 160), OTHER);
            not_on_side_panel = !spr->isSidepanel(pos, road_width);
            not_on_factory = !facts->is_factory(Vector2f(X, Y), IS_FACTORY);
            not_on_gasst = !stations->is_station(Vector2f(X, Y), IS_FACTORY);

            if (not_on_gasst && not_on_factory && !flag && Mouse::isButtonPressed(Mouse::Right) && not_on_side_panel && !roads->is_road(Vector2f(X, Y), OTHER) && !houses->is_house(Vector2f(X, Y), FACTORY) && near_road1 && near_road2 && near_road3){
                 if(player->cash >= 2000){
                    facts->factories.push_back(new Factory(X, Y, spr));
                    facts->fact_count++;
                    facts->factories[facts->factories.size()-1]->fact_sprite.setPosition(Vector2f(X, Y));
                    player->cash-=2000;
                    houses->houses_sort();
                 }
                 else if(player->cash < 2000){
                    spr->no_money_text.setPosition(X, Y - 10);
                    no_money_flag = true;
                    timer = 100;
                 }
            }
            if( !Mouse::isButtonPressed(Mouse::Right))
                flag = false;
            if (Mouse::isButtonPressed(Mouse::Left)){
                if (spr->fact_sprite.getGlobalBounds().contains(pos.x, pos.y))
                    isMove = true;
                else
                    return;
            }

            if (isMove)
                fact_sprite.setPosition(X, Y);
            window.clear(Color::White);
            player->update(facts);
            draw_all(window, spr, houses, roads, player, cars, facts, stations);
            window.draw(fact_sprite);
            if(!near_road && not_near_road_timer > 1){
                window.draw(spr->house_or);
                not_near_road_timer *=0.85;
            }
            if(no_money_flag && timer > 1){
                window.draw(spr->no_money_text);
                timer *=0.85;
            }
            else
                no_money_flag = false;
            window.display();
        }
    if(status == GAS)
        while(1){
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time/300;
            Sprite gas_sprite;
            gas_sprite = spr->gas_sprite;
            pixelPos = Mouse::getPosition(window);
            pos = window.mapPixelToCoords(pixelPos);
            Event event;
            x = pos.x - 50;
            y = pos.y - 50;
            X = div(x, road_width).quot * road_width;
            Y = div(y, road_heigh).quot * road_heigh;
            while (window.pollEvent(event))
                if (event.type == Event::Closed)
                    window.close();

            near_road1 = roads->is_road(Vector2f(X, Y + 100), OTHER);
            near_road2 = roads->is_road(Vector2f(X + road_width, Y + 100), OTHER);
            near_road3 = roads->is_road(Vector2f(X + road_width * 2, Y + 100), OTHER);
            not_on_factory = !facts->is_factory(Vector2f(X, Y), GAS_F);
            not_on_gasst =  !stations->is_station(Vector2f(X, Y), GAS_F);
            not_on_side_panel = !spr->isSidepanel(pos, road_width);
            not_on_house = !houses->is_house(Vector2f(X, Y), GAS);

            if (not_on_factory && not_on_gasst && !flag && Mouse::isButtonPressed(Mouse::Right) && not_on_side_panel && !roads->is_road(Vector2f(X, Y), OTHER) && not_on_house && near_road1 && near_road2 && near_road3){
                 if(player->cash >= 1500){
                    stations->stations.push_back(new Gas_station(X, Y, spr));
                    stations->stations[stations->stations.size()-1]->gas_sprite.setPosition(Vector2f(X, Y));
                    player->cash-=1500;
                    std::cout << "\nPut station";
                 }
                 else if(player->cash < 1500){
                    spr->no_money_text.setPosition(X, Y - 10);
                    no_money_flag = true;
                    timer = 100;
                 }
            }
            if( !Mouse::isButtonPressed(Mouse::Right))
                flag = false;
            if (Mouse::isButtonPressed(Mouse::Left)){
                if (spr->gas_sprite.getGlobalBounds().contains(pos.x, pos.y))
                    isMove = true;
                else
                    return;
            }

            if (isMove)
                gas_sprite.setPosition(X, Y);
            window.clear(Color::White);
            player->update(facts);
            draw_all(window, spr, houses, roads, player, cars, facts, stations);
            window.draw(gas_sprite);
            if(!near_road && not_near_road_timer > 1){
                window.draw(spr->house_or);
                not_near_road_timer *=0.85;
            }
            if(no_money_flag && timer > 1){
                window.draw(spr->no_money_text);
                timer *=0.85;
            }
            else
                no_money_flag = false;
            window.display();
        }

}
