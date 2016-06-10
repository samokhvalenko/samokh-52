#ifndef HOUSE_H_INCLUDED
#define HOUSE_H_INCLUDED

#include <cstdlib>

enum status {IS_ROAD = 1, IS_HOUSE = 2, IS_PLAYER = 3, IS_MOUSE = 4};

class House{
public:
    float dx, dy;
    Sprite house_sprite;

    House(float X, float Y, Sprites *spr){
        house_sprite.setTexture(spr->Sprites::house_texture);
        house_sprite.setPosition(X, Y);
        dx = X;
        std::cout << "\nX coord: " << dx;
        dy = Y;
        std::cout << "\nY coord: " << dy;

    }

    House(){
    }
};

bool cmp(House* h1, House* h2){
        return h1->dy < h2->dy;
}


class Houses{
public:
    int houses_count;
    std::vector< House *> houses;
    Texture house_texture;

    Houses(){

    }
    void houses_sort(){
        std::sort(houses.begin(), houses.end(), cmp);
    }
};

void draw_houses(Houses * houses, RenderWindow &window){

    for(int i = 0; i < houses->houses_count; i++){
        window.draw(houses->houses[i]->house_sprite);
    }
}

bool is_house(Houses * houses, Vector2f pos, status status){

    if(status == IS_HOUSE){
        pos.y = pos.y + 30;
        pos.x = pos.x + 55;
        for(int i = 0; i < houses->houses_count; i++){
            if(houses->houses[i]->house_sprite.getGlobalBounds().contains(pos))
                return true;
        }
        pos.x = pos.x - 55;
        for(int i = 0; i < houses->houses_count; i++){
            if(houses->houses[i]->house_sprite.getGlobalBounds().contains(pos))
                return true;
        }
    }
    else{
        for(int i = 0; i < houses->houses_count; i++){
            if(houses->houses[i]->house_sprite.getGlobalBounds().contains(pos))
                return true;
        }
    }

    return false;
}

#endif // HOUSE_H_INCLUDED
