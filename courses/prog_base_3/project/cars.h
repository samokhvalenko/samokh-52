#ifndef CARS_H_INCLUDED
#define CARS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "roads.h"
#include "house.h"
#include "textures.h"
#define PI 3.1415
#define road_destroying_speed 5

using namespace sf;

class Car {

public:
	float w, h, dx, dy,x,y;
	bool isMove;
	Sprite sprite;
	Vector2f pos_mov;
	Vector2f mov_v;
	float angle;
	int rand_flag;
	int road_is_riding;
	int type;
	int car_cash;
	bool flag, is_road_l, is_road_r, is_road_d, house_flag, road_flag, road_rided;
	Car( float X, float Y, int car_type, Sprites *spr){
        isMove = false;
		x = X; y = Y;
		mov_v = Vector2f(1, 0);
		type = car_type;
		if(type == 1){
            sprite = spr->car_sprite_1;
            car_cash = 150;
		}
		if(type == 2){
            sprite = spr->car_sprite_2;
            car_cash = 250;
		}
		if(type == 3){
            sprite = spr->car_sprite_3;
            car_cash = 400;
		}
		sprite.setOrigin(Vector2f(19, 10));
        sprite.setPosition(x, y);
        flag = false;
        road_is_riding = -1;
        road_rided = false;
        road_flag = true;
        house_flag = false;
        angle = 0;
	}
	void update(Roads * roads, Houses *houses, Player *player)
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

        if(is_house(houses, Vector2f( x, y - 60), IS_MOUSE) && house_flag == false){
            std::cout << "\nIs house: " << is_house(houses, Vector2f( x, y - 60), IS_MOUSE);
            player->cash += car_cash + 30 * (houses->houses_count - 0.5);
            house_flag = true;
        }
        if(!is_house(houses, Vector2f( x, y - 60), IS_MOUSE)){
            house_flag = false;
        }

        //std::cout << "\nRoad: " << roads->is_road(Vector2f(x, y), IS_REPAIRING);
        //std::cout << "\nRoad is riding: " << road_is_riding;

        if(roads->is_road(Vector2f(x, y), IS_REPAIRING) != road_is_riding){
            road_rided == false;
            road_is_riding = roads->is_road(Vector2f(x, y), IS_REPAIRING);
            roads->roads[road_is_riding]->state-=100 * (road_destroying_speed/roads->roads[road_is_riding]->state);
            road_rided = true;
        }

		sprite.setPosition(x, y);
		sprite.setRotation(angle / PI * 180);

	}

	void set_mov(Vector2f pos){
	    pos_mov = pos;
	}

	float getWidth(){
		return w;
	}

	float getHeight(){
		return h;
	}

	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){
		return y;
	}

};

class Cars{
public:
    int cars_count;
    std::vector< Car *> cars;
    Cars(){
        cars_count = 0;
    }

    void update(Roads * roads, Houses *houses, Player *player){
        for(int i = 0; i < cars_count; i++)
            cars[i]->update(roads, houses, player);

    }

    void draw_cars(RenderWindow &window){
        for(int i = 0; i < cars_count; i++){
            window.draw(cars[i]->sprite);
        }
    }
};

#endif // CARS_H_INCLUDED
