#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "cars.h"
#include "car.h"
#define PI 3.1415
#define road_destroying_speed 7

bool Cars::is_car(Vector2f pos){
        for(int i = 0; i < cars.size(); i++){
            if(cars[i]->sprite.getGlobalBounds().contains(pos))
                return true;
        }
        return false;
    }

void Car::update(Roads * roads, Houses *houses, Player *player, Cars *cars)
	{
	    rand_flag = rand() % 2 + 1;
	    is_road_l = roads->is_road(Vector2f(x  + road_heigh * cos(angle + PI / 2), y + road_width * sin(angle + PI / 2)), FOR_CAR);
        is_road_r = roads->is_road(Vector2f(x  + road_heigh * cos(angle - PI / 2), y + road_width * sin(angle - PI / 2)), FOR_CAR);
        is_road_d = roads->is_road(Vector2f(x  + road_heigh * cos(angle - PI), y + road_width * sin(angle - PI)), FOR_CAR);

	    if (roads->is_road(Vector2f(x + (int)(road_width/2+1) * mov_v.x, y + (int)(road_width/2+1) * mov_v.y), FOR_CAR)){
            road_flag = true;
	    }
	    else if(is_road_r && is_road_l && rand_flag == 1){
            angle -= PI / 2;
            mov_v = Vector2f(cos(angle), sin(angle));
            road_flag = true;
        }
        else if(is_road_l && is_road_r && rand_flag == 2){
            angle += PI / 2;
            mov_v = Vector2f(cos(angle), sin(angle));
            road_flag = true;
        }
        else if(is_road_l && !is_road_r){
            angle += PI / 2;
            mov_v = Vector2f(cos(angle), sin(angle));
            road_flag = true;
        }
        else if(is_road_r && !is_road_l){
            angle -= PI / 2;
            mov_v = Vector2f(cos(angle), sin(angle));
            road_flag = true;
        }
        else if(is_road_d){
            angle -= PI;
            mov_v = Vector2f(cos(angle), sin(angle));
            flag = true;
            road_flag = true;
        }
        else if(!is_road_d && !is_road_l && !is_road_r){
            road_flag = false;
        }

        if(road_flag){
            if(!cars->is_car(Vector2f(x + 50*mov_v.x, y + 50*mov_v.y))){
                if(mov_v.x < 0.9 && mov_v.x > 0)
                    mov_v.x = 0;
                if(mov_v.x > -0.9 && mov_v.x < 0)
                    mov_v.x = 0;
                if(mov_v.y < 0.9 && mov_v.y > 0)
                    mov_v.y = 0;
                if(mov_v.y > -0.9 && mov_v.y < 0)
                    mov_v.y = 0;
                x += 0.01*250 * mov_v.x;
                y += 0.01*250 * mov_v.y;
            }
            else{
                angle -= PI;
                mov_v = Vector2f(cos(angle), sin(angle));
                flag = true;
                road_flag = true;
            }
        }
        if(houses->is_house(Vector2f( x, y - 60), IS_MOUSE) && house_flag == false){
            std::cout << "\nIs house: " << houses->is_house(Vector2f( x, y - 60), IS_MOUSE);
            player->cash += car_cash + 30 * (houses->houses_count - 0.5);
            house_flag = true;
        }
        if(!houses->is_house(Vector2f( x, y - 60), IS_MOUSE)){
            house_flag = false;
        }

        if(roads->is_road(Vector2f(x-mov_v.x * road_width, y- mov_v.y * road_heigh), IS_REPAIRING) != road_is_riding){
            road_rided = false;
            road_is_riding = roads->is_road(Vector2f(x-mov_v.x * road_width, y - mov_v.y * road_heigh), IS_REPAIRING);
            roads->roads[road_is_riding]->state-=100 * (road_destroying_speed/roads->roads[road_is_riding]->state);
            road_rided = true;
        }

		sprite.setPosition(x, y);
		sprite.setRotation(angle / PI * 180);
}

bool cmp(House* h1, House* h2){
        return h1->dy < h2->dy;
}
