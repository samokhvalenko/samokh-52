#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "menu.h"

class Car
{
public:
    Texture car_texture;
    Sprite car_sprite;
    float x, y, w, h, dx, dy, speed ;
    int dir;
    Car()
    {
        car_texture.loadFromFile("cars.png");
        car_sprite.setTextureRect(IntRect(125, 66, 10, 25));

    }

    void update(float time)
    {
        switch (dir)
        {
        case 0:
            dx = speed;
            dy = 0;
            break;
        case 1:
            dx = -speed;
            dy = 0;
            break;
        case 2:
            dx = 0;
            dy = speed;
            break;
        case 3:
            dx = 0;
            dy = -speed;
            break;
        }

        x += dx*time;
        y += dy*time;

        speed = 0;
        sprite.setPosition(x,y);
    }
};
