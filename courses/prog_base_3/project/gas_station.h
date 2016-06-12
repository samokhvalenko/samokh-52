#ifndef GAS_STATION_H_INCLUDED
#define GAS_STATION_H_INCLUDED

#include <cstdlib>


class Gas_station{
public:
    float dx, dy;
    Sprite gas_sprite;

    Gas_station(float X, float Y, Sprites *spr){
        gas_sprite.setTexture(spr->Sprites::gas_texture);
        gas_sprite.setPosition(X, Y);
        dx = X;
        dy = Y;
    }
};

class Gas_stations{
public:
    std::vector< Gas_station *> stations;

    Gas_stations(){

    }

    void draw_stations(RenderWindow &window){

        for(int i = 0; i < stations.size(); i++){
            window.draw(stations[i]->gas_sprite);
        }
    }

    bool is_station(Vector2f pos, status_f status){
        bool st_left = false, st_right = false, on_st = false;

        for(int i = 0; i < stations.size(); i++){
            if(stations[i]->gas_sprite.getGlobalBounds().contains(pos))
                return true;
        }

        if(status == IS_HOUSE_F){
            for(int i = 0; i < stations.size(); i++){
                st_left = stations[i]->gas_sprite.getGlobalBounds().contains(Vector2f(pos.x - 30, pos.y + 50));
                st_right =  stations[i]->gas_sprite.getGlobalBounds().contains(Vector2f(pos.x + 110, pos.y + 50));
                on_st = stations[i]->gas_sprite.getGlobalBounds().contains(Vector2f(pos.x, pos.y + 50));
                //std::cout <<"\nLeft: " << st_left << " Right: " << st_right << " On station: " << on_st;
                if(st_left || st_right || on_st)
                    return true;
            }

        }
        if(status == IS_FACTORY){
            for(int i = 0; i < stations.size(); i++){
                st_left = stations[i]->gas_sprite.getGlobalBounds().contains(Vector2f(pos.x - 20, pos.y + 80));
                st_right =  stations[i]->gas_sprite.getGlobalBounds().contains(Vector2f(pos.x + 110, pos.y + 80));
                on_st = stations[i]->gas_sprite.getGlobalBounds().contains(Vector2f(pos.x + 20, pos.y + 100));
                //std::cout <<"\nLeft: " << st_left << " Right: " << st_right << " On station: " << on_st;
                if(st_left || st_right || on_st)
                    return true;
            }

        }
        if(status == GAS_F){
            for(int i = 0; i < stations.size(); i++){
                st_right =  stations[i]->gas_sprite.getGlobalBounds().contains(Vector2f(pos.x + 130, pos.y));
                st_left = stations[i]->gas_sprite.getGlobalBounds().contains(Vector2f(pos.x - 20, pos.y));
                on_st = stations[i]->gas_sprite.getGlobalBounds().contains(Vector2f(pos.x + 20, pos.y-5));
                //std::cout <<"\nLeft: " << st_left << " Right: " << st_right << " On station: " << on_st;
                if(st_left || st_right || on_st)
                    return true;
            }

        }
    return false;
}
};

#endif // GAS_STATION_H_INCLUDED
