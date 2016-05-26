#ifndef ROADS_H_INCLUDED
#define ROADS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "textures.h"


class Road{
public:
    float w, h, dx, dy,x,y, speed;
    int dir;
    Sprite road_sprite;
    float state;

    Road(float X, float Y, Sprites *spr){
        road_sprite.setTexture(spr->Sprites::road_texture);
        road_sprite.setTextureRect(IntRect(585, 130, 37, 37));
        road_sprite.setPosition(X, Y);
        state = 100;

    }
};


void road_update(Road *road, Texture &crashed_texture)
{
    road->state = road->state * 0.99994;
    if(road->state < 50){
        road->road_sprite.setTexture(crashed_texture);
        road->road_sprite.setTextureRect(IntRect(585, 130, 37, 37));
    }
}

class Roads{
public:
    int roads_count;
    std::vector< Road *> roads;
    Texture road_texture;

    Roads(){
        road_texture.loadFromFile("roads.png");
    }
};

void draw_roads(Roads *roads, RenderWindow &window){
    for(int i = 0; i < roads->roads_count; i++){
        window.draw(roads->roads[i]->road_sprite);
    }
}

bool is_road(Roads *roads, Vector2f pos){
    for(int i = 0; i < roads->roads_count; i++){
        if(roads->roads[i]->road_sprite.getGlobalBounds().contains(pos))
            return true;
    }
    return false;
}

#endif // ROADS_H_INCLUDED
