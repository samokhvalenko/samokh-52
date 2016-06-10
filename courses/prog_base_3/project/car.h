#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "roads.h"
#include "house.h"
#include "textures.h"
#include "cars.h"
#define PI 3.1415
#define road_destroying_speed 7

using namespace sf;

class Cars;

class Car {

private:
	float w, h, dx, dy,x,y;
	bool isMove;

	Vector2f pos_mov;
	Vector2f mov_v;
	float angle;
	int rand_flag;
	int road_is_riding;
	int type;
	int car_cash;
	bool flag, is_road_l, is_road_r, is_road_d, house_flag, road_flag, road_rided;
public:
    Sprite sprite;
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

	void update(Roads * roads, Houses *houses, Player *player, Cars *cars);


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

#endif // CAR_H_INCLUDED
