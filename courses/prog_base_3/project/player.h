#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <cstdlib>

#include "textures.h"
#include "roads.h"
#include "house.h"
#include "factory.h"

using namespace sf;

/*class Worker {

public:
	float w, h, dx, dy,x,y, speed;
	bool isMove,isSelect;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Vector2f pos_mov;
	Worker( float X, float Y){
        isMove = false; isSelect = false;
		image.loadFromFile("worker.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(132, 96, 16, 24));

	}
	void update(Roads *roads, float time)
	{
		if (!isMove)
            speed = 0;
		sprite.setPosition(x, y);
	}

	void set_mov(Vector2f pos){
	    pos_mov = pos;
	}

	float getWidth(){
		return w;
	}

	float getHeight(){
		return h;
	}

	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){
		return y;
	}
    void move_worker(RenderWindow &window, float time, float &CurrentFrame, Houses * houses, Roads *roads){

        float player_nh_pos_x, player_nh_pos_y;
        float distance = sqrt((pos_mov.x - x)*(pos_mov.x - x) + (pos_mov.y - y)*(pos_mov.y - y));

        player_nh_pos_x = x + 0.001 *time*(pos_mov.x - x) / distance;
        player_nh_pos_y = y + 0.001 *time*(pos_mov.y - y) / distance;

        if (distance > 2 && isMove){
            x += 0.01*time *(pos_mov.x - x) / distance;
            y += 0.01*time *(pos_mov.y - y) / distance;
        }

        if(houses->is_house(Vector2f(player_nh_pos_x, player_nh_pos_y), IS_PLAYER)){
            x -= 0.01*time *(pos_mov.x - x) / distance;
            y -= 0.01*time *(pos_mov.y - y) / distance;
        }
        if(y < pos_mov.y && distance > 2){
            CurrentFrame += 0.003*time / 2;
            if (CurrentFrame > 5)
                CurrentFrame -= 5;
            sprite.setTextureRect(IntRect(132 + 24* (int)(CurrentFrame), 96, 16, 24));
        }
        else if(y > pos_mov.y && distance > 2){
            CurrentFrame += 0.003*time / 2;
            if (CurrentFrame > 5)
                CurrentFrame -= 5;
            sprite.setTextureRect(IntRect(132 + 24* (int)(CurrentFrame), 1, 16, 24));
        }
        update(roads, time);
    }
};*/



class Player{
public:
    int cash;
    int oil;
    Text cash_t;
    Text cash_t2;
    Text oil_t;
    Text oil_t2;
    Text t_name;
    int score;
    std::string name;
    Player(std::string p_name){
        name = p_name;
        score = 0;
        cash = 2000;
        oil = 120;

        t_name.setString("Player:\n" + p_name);
        t_name.setCharacterSize(20);
        t_name.setColor(Color::Black);
        t_name.setStyle(sf::Text::Bold);
        t_name.setPosition(1100, 2);

        cash_t.setString("Cash: ");
        cash_t.setCharacterSize(20);
        cash_t.setColor(Color::Blue);
        cash_t.setStyle(sf::Text::Bold);
        cash_t.setPosition(960, 2);

        cash_t2.setCharacterSize(20);
        cash_t2.setColor(Color::Blue);
        cash_t2.setStyle(sf::Text::Bold);
        cash_t2.setPosition(1025, 2);

        oil_t.setString("Oil: ");
        oil_t.setCharacterSize(20);
        oil_t.setColor(Color::Blue);
        oil_t.setStyle(sf::Text::Bold);
        oil_t.setPosition(960, 25);

        oil_t2.setCharacterSize(20);
        oil_t2.setColor(Color::Blue);
        oil_t2.setStyle(sf::Text::Bold);
        oil_t2.setPosition(1025, 25);

    }

    void update(Factories *facts){
        char n_str[20];
        sprintf(n_str,"%d",cash);
        cash_t2.setString(n_str);

        oil += facts->factories.size() * 1;

        sprintf(n_str,"%d",oil);
        oil_t2.setString(n_str);

    }
};


#endif // CITY_H_INCLUDED
