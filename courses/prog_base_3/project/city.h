#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "textures.h"
#include "d_d.h"

class City{
public:
    float w, h, dx, dy,x,y;
    int dir;
    Texture city_texture;
    Sprite city_sprite;
    float state;

    City(float X, float Y){
        city_sprite.setTexture(Sprites::city_texture);
        city_sprite.setPosition(X, Y);
    }
};


#endif // CITY_H_INCLUDED
