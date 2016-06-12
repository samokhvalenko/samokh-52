#ifndef HOUSE_H_INCLUDED
#define HOUSE_H_INCLUDED

#include <cstdlib>

enum status {IS_ROAD = 1, IS_HOUSE = 2, IS_PLAYER = 3, IS_MOUSE = 4, FACTORY = 5, GAS = 6};



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

};

bool cmp(House* h1, House* h2);

class Houses{
public:
    std::vector< House *> houses;

    Houses(){

    }

    void houses_sort(){
        std::sort(houses.begin(), houses.end(), cmp);
    }

    void draw_houses(RenderWindow &window){

        for(int i = 0; i < houses.size(); i++){
            window.draw(houses[i]->house_sprite);
        }
    }

    bool is_house(Vector2f pos, status status){

        if(status == IS_HOUSE){
            pos.y = pos.y + 30;
            pos.x = pos.x + 55;
            for(int i = 0; i < houses.size(); i++){
                if(houses[i]->house_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.x = pos.x - 55;
            for(int i = 0; i < houses.size(); i++){
                if(houses[i]->house_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.y = pos.y - 30;
            pos.x = pos.x + 90;
            for(int i = 0; i < houses.size(); i++){
                if(houses[i]->house_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
        }
        if(status == FACTORY){
            pos.y = pos.y + 50;
            pos.x = pos.x + 106;
            for(int i = 0; i < houses.size(); i++){
                if(houses[i]->house_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.x = pos.x - 106;
            for(int i = 0; i < houses.size(); i++){
                if(houses[i]->house_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.y = pos.y - 50;
            pos.x = pos.x - 30;
            for(int i = 0; i < houses.size(); i++){
                if(houses[i]->house_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
        }
        if(status == GAS){
            pos.y = pos.y + 50;
            pos.x = pos.x + 120;
            for(int i = 0; i < houses.size(); i++){
                if(houses[i]->house_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.x = pos.x - 120;
            for(int i = 0; i < houses.size(); i++){
                if(houses[i]->house_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.y = pos.y - 50;
            pos.x = pos.x - 30;
            for(int i = 0; i < houses.size(); i++){
                if(houses[i]->house_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
        }
        else{
            for(int i = 0; i < houses.size(); i++){
                if(houses[i]->house_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
        }

        return false;
}
};

#endif // HOUSE_H_INCLUDED
