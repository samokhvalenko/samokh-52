#ifndef TEXTURES_H_INCLUDED
#define TEXTURES_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define SRPX 1270
#define SRPY 25
#define SHPX 1266
#define SHPY 80
#define ngS_h_r2bomX 300
#define ngS_h_r2bomY 300
#define BGSC 50
#define width 2500
#define heigh 1500
#define screen_width 1920
#define screen_heigh 1080
//#define screen_width 1366
//#define screen_heigh 768

using namespace sf;

class Sprites{
public:
    Texture back_game_texture;
    Texture road_texture, crashed_road_texture;
    Sprite road_sprite_gorizontal;
    Sprite ngS_h_r2bom;
    Texture ngT_h_r2bom;
    Sprite back_game_sprite;
    RectangleShape rectangle, rect_road;
    Image back_game_image;
    Texture house_texture;
    Sprite house_sprite;
    Text house_1_w_t;
    Sprite back_game_sprites[BGSC];

    Sprites(Font font){
        back_game_image.loadFromFile("TGX0.png");
        back_game_texture.loadFromImage(back_game_image);
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
        rectangle.setSize(Vector2f(100, 768));
        rectangle.setFillColor(Color(191, 168, 32));
        rectangle.setOutlineThickness(5);
        rectangle.setOutlineColor(Color::Black);
        rectangle.setPosition(1266, 0);
        rect_road.setSize(Vector2f(37, 37));
        rect_road.setFillColor(Color::Black);
        rect_road.setOutlineThickness(5);
        rect_road.setOutlineColor(Color::Black);
        rect_road.setPosition(1270, 25);
        house_texture.loadFromFile("house_small.png");
        house_sprite.setTexture(house_texture);
        house_sprite.setPosition(SHPX, SHPY);
        font.loadFromFile("arial.ttf");
        house_1_w_t.setString("House for 1 worker");
        house_1_w_t.setFont(font);
        house_1_w_t.setCharacterSize(100);
        house_1_w_t.setColor(Color::Black);
        house_1_w_t.setPosition(1266, 120);

    }

    void draw_bgs(RenderWindow &window){
        window.draw(back_game_sprite);
        window.draw(rectangle);
    }

    bool isObj( Vector2f pos){
        if(rectangle.getGlobalBounds().contains(pos.x, pos.y))
            return true;
        return false;
    }
};

#endif // TEXTURES_H_INCLUDED
