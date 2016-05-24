#ifndef TEXTURES_H_INCLUDED
#define TEXTURES_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define SRPX 1300
#define SRPY 100
#define ngS_h_r2bomX 300
#define ngS_h_r2bomY 300

using namespace sf;

class Sprites{
public:
    Texture back_game_texture; // setting our background
    Texture road_texture, crashed_road_texture;// creating texture for road. road`s texture will be loaded in this place.
    Sprite road_sprite_gorizontal;
    Sprite ngS_h_r2bom;
    Texture ngT_h_r2bom;
    Sprite back_game_sprite;
    Texture city_texture;
    Sprite city_sprite_side_panel;
    RectangleShape rectangle;

    Sprites(){
        back_game_texture.loadFromFile("back_game_texture.png");
        back_game_sprite.setTexture(back_game_texture);
        back_game_sprite.setPosition(0, 0);
        road_texture.loadFromFile("roads.png");
        crashed_road_texture.loadFromFile("roads_crashed.png");
        road_sprite_gorizontal.setTexture(road_texture);
        road_sprite_gorizontal.setTextureRect(IntRect(585, 130, 37, 37));
        road_sprite_gorizontal.setPosition(SRPX, SRPY);
        ngT_h_r2bom.loadFromFile("ng_h_r2bom.png");
        ngS_h_r2bom.setTexture(ngT_h_r2bom);
        ngS_h_r2bom.setPosition(ngS_h_r2bomX, ngS_h_r2bomY);
        city_texture.loadFromFile("city.png");
        city_sprite_side_panel.setTexture(city_texture);
        rectangle.setSize(Vector2f(100, 768));
        rectangle.setPosition(1266, 0);

    }

    void draw_bgs(RenderWindow &window){
        window.draw(back_game_sprite);
        window.draw(rectangle);
    }

    bool isObj(Sprite sprite){
        if(sprite.getGlobalBounds() == road_sprite_gorizontal.getGlobalBounds());
            return true;
        if(sprite.getGlobalBounds() == rectangle.getGlobalBounds());
            return true;
        return false;
    }
};

#endif // TEXTURES_H_INCLUDED
