#ifndef CARS_H_INCLUDED
#define CARS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "roads.h"
#include "house.h"
#include "city.h"
#include "car.h"
#include "textures.h"
#define PI 3.1415
#define road_destroying_speed 7

using namespace sf;

class Cars{
public:
    std::vector< Car *> cars;
    Cars(){

    }

    void update(Roads * roads, Houses *houses, Player *player, Cars *cars_c){
        for(int i = 0; i < cars.size(); i++)
            cars[i]->update(roads, houses, player, cars_c);

    }

    void draw_cars(RenderWindow &window){
        for(int i = 0; i < cars.size(); i++){
            window.draw(cars[i]->sprite);
        }
    }

    void buy_car(int type, Sprites *spr){
        cars.push_back(new Car(19, 250, type, spr));
    }

    bool is_car(Vector2f pos);
};

#endif // CARS_H_INCLUDED
