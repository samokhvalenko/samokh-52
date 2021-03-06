#ifndef ROADS_H_INCLUDED
#define ROADS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cstdlib>
#include "textures.h"
#include "player.h"
#define road_heigh 40
#define road_width 37

enum status_r {FOR_CAR = 1, OTHER = 2, IS_REPAIRING = 3, NOTH = 0, FACT_R = 4};

class Road{
public:
    float w, h, dx, dy,x,y, speed;
    int dir;
    Texture road_texture;
    Sprite road_sprite;
    float state;
    bool state_b;
    float to_rep;
    Texture crashed_texture;

    Road(float X, float Y, Sprites *spr){
        crashed_texture.loadFromFile("roads_crashed.png");
        road_sprite.setTexture(spr->Sprites::road_texture);
        road_texture = spr->Sprites::road_texture;
        road_sprite.setTextureRect(IntRect(585, 127, road_width, road_heigh));
        road_sprite.setPosition(X, Y);
        state = 100;
        state_b = 1;
        to_rep = 0.9999;

    }

    void road_update(int num)
    {
        state = state * to_rep;
        if(state < 50){
            road_sprite.setTexture(crashed_texture);
            road_sprite.setTextureRect(IntRect(585, 127, road_width, road_heigh));
            state_b = 0;
        }
        if(state >= 50){
            road_sprite.setTexture(road_texture);
            road_sprite.setTextureRect(IntRect(585, 127, road_width, road_heigh));
            state_b = 1;
        }
        if( state >= 100)
        {
            to_rep = 0.9999;
        }
    }
};

class Roads{
public:
    int broken_road_rep_price;
    int all_road_rep_price;
    std::vector< Road *> roads;

    Roads(){

        broken_road_rep_price = 0;
        all_road_rep_price = 0;
    }

    void rs_update(float time, Sprites *spr){
        for( int i = 0; i < roads.size(); i++){
            roads[i]->road_update(i);
        }
        char str[20];
        update_all_r_prices();
        update_br_prices();
        char all_str[20];
        char br_str[20];
        sprintf(all_str, "%d", all_road_rep_price);
        sprintf(br_str, "%d", broken_road_rep_price);
        spr->rep_all_r_price.setString(all_str);
        spr->rep_br_price.setString(br_str);
    }

    void repair_broken_roads(Player *player){
        if(player->cash >= broken_road_rep_price){
            for(int i = 0; i < roads.size(); i++){
                if(roads[i]->state_b == 0)
                    roads[i]->state = 100;
            }
            player->cash-=broken_road_rep_price;
        }
    }

    void repair_all_roads(Player *player){
        if(player->cash >= all_road_rep_price){
            for(int i = 0; i < roads.size(); i++){
                roads[i]->state = 100;
            }
            player->cash-=all_road_rep_price;
        }
    }

    void draw_roads(RenderWindow &window){
        for(int i = 0; i < roads.size(); i++){
            window.draw(roads[i]->road_sprite);
        }
}

    void update_br_prices(){
        int broken_roads_price = 0, br_count = 1;
        float coef = 5;

        for(int i = 0; i < roads.size(); i++){
            if(roads[i]->state_b == 0){
                broken_roads_price+=50;
                br_count++;
            }
        }

        broken_road_rep_price = broken_roads_price;
    }

    void update_all_r_prices(){
        int all_roads_price = 0, all_count = 1;
        float coef = 5;

        for(int i = 0; i < roads.size(); i++){
            if(roads[i]->state_b == 0){
                all_roads_price+=50;
                all_count++;
            }
            else if(roads[i]->state_b == 1){
                all_roads_price+=25;
            }
        }

        all_roads_price = all_roads_price;
        all_road_rep_price = all_roads_price;
    }

    int is_road(Vector2f pos, status_r status){
        for(int i = 0; i < roads.size(); i++){
            if(roads[i]->road_sprite.getGlobalBounds().contains( pos)){
                if(status == IS_REPAIRING){
                    return i;
                }
                else if(status == OTHER)
                    return true;
                else if(status == FOR_CAR && roads[i]->state_b == 1)
                    return true;
            }
        }
        return false;
    }

    bool check_roads(Vector2f pos){

        if(check_r_up(pos) || check_l_up(pos) || check_r_down(pos) || check_l_down(pos))
            return false;
        return true;

    }
    bool check_r_up(Vector2f pos){
        if(is_road(Vector2f(pos.x + road_width, pos.y), OTHER) && is_road(Vector2f(pos.x, pos.y - road_heigh), OTHER) && is_road(Vector2f(pos.x + road_width, pos.y - road_heigh), OTHER))
            return true;
        return false;
    }

    bool check_r_down(Vector2f pos){
        if(is_road(Vector2f(pos.x + road_width, pos.y), OTHER) && is_road(Vector2f(pos.x, pos.y + road_heigh), OTHER) && is_road(Vector2f(pos.x + road_width, pos.y + road_heigh), OTHER))
            return true;
        return false;
    }

    bool check_l_up(Vector2f pos){
        if(is_road(Vector2f(pos.x - road_width, pos.y), OTHER) && is_road(Vector2f(pos.x, pos.y - road_heigh), OTHER) && is_road(Vector2f(pos.x - road_width, pos.y - road_heigh), OTHER))
            return true;
        return false;
    }

    bool check_l_down(Vector2f pos){
        if(is_road(Vector2f(pos.x - road_width, pos.y), OTHER) && is_road(Vector2f(pos.x, pos.y + road_heigh), OTHER) && is_road(Vector2f(pos.x - road_width, pos.y + road_heigh), OTHER))
            return true;
        return false;
    }

};

#endif // ROADS_H_INCLUDED
