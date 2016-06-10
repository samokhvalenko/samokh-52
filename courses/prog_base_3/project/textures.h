#ifndef TEXTURES_H_INCLUDED
#define TEXTURES_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define SRPX 1290
#define SRPY 25
#define SHPX 1266
#define SHPY 100
#define ngS_h_r2bomX 300
#define ngS_h_r2bomY 300
#define BGSC 50
#define width 2500
#define heigh 1500
#define screen_width 1366
#define screen_heigh 768

using namespace sf;

class Sprites{
public:
    Texture back_game_texture;
    Texture road_texture, crashed_road_texture;
    Sprite road_sprite_side_panel;
    Sprite ngS_h_r2bom;
    Texture ngT_h_r2bom;
    Sprite back_game_sprite;
    RectangleShape side_rectangle, rect_road;
    Image back_game_image;
    Texture house_texture;
    Sprite house_sprite;
    Text house_1_w_t;


    Sprite car_sprite_1, car_sprite_2, car_sprite_3;
    Text car_1_price, car_2_price, car_3_price;
    Texture car_texture;

    Text rep_br, rep_all_r, rep_br_price, rep_all_r_price, road_text, house_text, no_money_text, house_or, road_nr;
    RectangleShape rep_br_r, rep_all_r_r;
    bool road_selected;

    Sprites(Font font){
        back_game_image.loadFromFile("TGX0.png");
        back_game_texture.loadFromImage(back_game_image);
        back_game_sprite.setTexture(back_game_texture);
        back_game_sprite.setPosition(0, 0);
        road_texture.loadFromFile("roads.png");
        crashed_road_texture.loadFromFile("roads_crashed.png");
        road_sprite_side_panel.setTexture(road_texture);
        road_sprite_side_panel.setTextureRect(IntRect(585, 127, 37, 40));
        road_sprite_side_panel.setPosition(SRPX, SRPY);
        side_rectangle.setSize(Vector2f(106, 768));
        side_rectangle.setFillColor(Color::Cyan);
        side_rectangle.setOutlineThickness(5);
        side_rectangle.setOutlineColor(Color::Black);
        side_rectangle.setPosition(1260, 0);
        rect_road.setSize(Vector2f(37, 37));
        rect_road.setFillColor(Color::Black);
        rect_road.setOutlineThickness(5);
        rect_road.setOutlineColor(Color::Black);
        rect_road.setPosition(1290, 25);
        house_texture.loadFromFile("house_small.png");
        house_sprite.setTexture(house_texture);
        house_sprite.setPosition(SHPX, SHPY);

        car_texture.loadFromFile("cars.png");
        car_sprite_1.setTexture(car_texture);
        car_sprite_2.setTexture(car_texture);
        car_sprite_3.setTexture(car_texture);

        car_sprite_1.setPosition(1261, 280);
        car_sprite_2.setPosition(1261, 330);
        car_sprite_3.setPosition(1261, 380);

        car_sprite_1.setTextureRect(IntRect(0, 107, 37, 19));
        car_sprite_2.setTextureRect(IntRect(41, 86, 39, 16));
        car_sprite_3.setTextureRect(IntRect(40, 109, 38, 16));

        rep_br.setString("Repair broken\nroads costs");
        rep_br.setCharacterSize(15);
        rep_br.setColor(Color::Black);
        rep_br.setPosition(1270, 710);
        rep_br_r.setSize(Vector2f(90, 50));
        rep_br_r.setFillColor(Color::Yellow);
        rep_br_r.setOutlineThickness(5);
        rep_br_r.setOutlineColor(Color::Black);
        rep_br_r.setPosition(1270, 710);

        rep_all_r.setString("Repair all\nroads costs");
        rep_all_r.setCharacterSize(15);
        rep_all_r.setColor(Color::Black);
        rep_all_r.setPosition(1270, 650);

        rep_all_r_r.setSize(Vector2f(90, 50));
        rep_all_r_r.setFillColor(Color::Yellow);
        rep_all_r_r.setOutlineThickness(5);
        rep_all_r_r.setOutlineColor(Color::Black);
        rep_all_r_r.setPosition(1270, 650);

        rep_br_price.setCharacterSize(15);
        rep_br_price.setColor(Color::Black);
        rep_br_price.setPosition(1270, 740);

        rep_all_r_price.setCharacterSize(15);
        rep_all_r_price.setColor(Color::Black);
        rep_all_r_price.setPosition(1270, 680);

        road_text.setString("Road costs\n  150");
        road_text.setCharacterSize(15);
        road_text.setColor(Color::Black);
        road_text.setPosition(1270, 65);

        house_text.setString("House costs\n  500");
        house_text.setCharacterSize(15);
        house_text.setColor(Color::Black);
        house_text.setPosition(1270, 230);

        no_money_text.setString("Not enough money");
        no_money_text.setCharacterSize(25);
        no_money_text.setColor(Color::Red);

        house_or.setString("House must be built over the road");
        house_or.setCharacterSize(25);
        house_or.setColor(Color::Red);

        road_nr.setString("Road must be built near another road");
        road_nr.setCharacterSize(25);
        road_nr.setColor(Color::Red);

        car_1_price.setString("1500");
        car_1_price.setCharacterSize(15);
        car_1_price.setColor(Color::Black);
        car_1_price.setPosition(1310, 280);

        car_2_price.setString("2500");
        car_2_price.setCharacterSize(15);
        car_2_price.setColor(Color::Black);
        car_2_price.setPosition(1310, 330);

        car_3_price.setString("4000");
        car_3_price.setCharacterSize(15);
        car_3_price.setColor(Color::Black);
        car_3_price.setPosition(1310, 380);

        road_selected = false;
    }

    void draw_bgs(RenderWindow &window){
        window.draw(back_game_sprite);
        window.draw(side_rectangle);
    }

    bool isSidepanel( Vector2f pos, int f_width){
        if(side_rectangle.getGlobalBounds().contains(pos.x + f_width, pos.y))
            return true;
    return false;
    }

    bool is_br_road_rep(Vector2f localPosf){
        if(rep_br_r.getGlobalBounds().contains(localPosf)){
            return true;
        }
        return false;
    }

    bool is_all_road_rep(Vector2f localPosf){
        if(rep_all_r_r.getGlobalBounds().contains(localPosf)){
            return true;
        }
        return false;
    }

};

#endif // TEXTURES_H_INCLUDED
