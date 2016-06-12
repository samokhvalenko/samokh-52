#ifndef FACTORY_H_INCLUDED
#define FACTORY_H_INCLUDED

#include <cstdlib>

enum status_f {OTHER_F = 2, IS_FACTORY = 5, IS_HOUSE_F, FOR_CAR_f, GAS_F};

class Factory{
public:
    float dx, dy;
    Sprite fact_sprite;
    int oil;

    Factory(float X, float Y, Sprites *spr){
        fact_sprite.setTexture(spr->Sprites::fact_texture);
        fact_sprite.setPosition(X, Y);
        dx = X;
        std::cout << "\nX coord: " << dx;
        dy = Y;
        std::cout << "\nY coord: " << dy;

    }
};

bool cmp2(Factory* h1, Factory* h2);

class Factories{
public:
    int fact_count;
    std::vector< Factory *> factories;

    Factories(){

    }

    void factories_sort(){
        std::sort(factories.begin(), factories.end(), cmp2);
    }

    void draw_factories(RenderWindow &window){

        for(int i = 0; i < factories.size(); i++){
            window.draw(factories[i]->fact_sprite);
        }
    }

    bool is_factory(Vector2f pos, status_f status){
        if(status == IS_FACTORY){
            pos.y = pos.y + 40;
            pos.x = pos.x + 55;
            for(int i = 0; i < factories.size(); i++){
                if(factories[i]->fact_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.x = pos.x - 55;
            for(int i = 0; i < factories.size(); i++){
                if(factories[i]->fact_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.x = pos.x + 90;
            for(int i = 0; i < factories.size(); i++){
                if(factories[i]->fact_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
        }
        else if(status == IS_HOUSE_F){
            pos.y = pos.y + 30;
            pos.x = pos.x + 55;
            for(int i = 0; i < factories.size(); i++){
                if(factories[i]->fact_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.x = pos.x - 55;
            for(int i = 0; i < factories.size(); i++){
                if(factories[i]->fact_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.x = pos.x + 90;
            for(int i = 0; i < factories.size(); i++){
                if(factories[i]->fact_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
        }
        else if(status == GAS_F){
            pos.x = pos.x + 128;
            for(int i = 0; i < factories.size(); i++){
                if(factories[i]->fact_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.x = pos.x - 128;
            for(int i = 0; i < factories.size(); i++){
                if(factories[i]->fact_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
            pos.x = pos.x - 10;
            for(int i = 0; i < factories.size(); i++){
                if(factories[i]->fact_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
        }
        else{
            for(int i = 0; i < factories.size(); i++){
                if(factories[i]->fact_sprite.getGlobalBounds().contains(pos))
                    return true;
            }
        }
    return false;
}
};
#endif // FACTORY_H_INCLUDED
