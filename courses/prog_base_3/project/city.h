#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "textures.h"
#include "roads.h"
#include "house.h"

using namespace sf;

class Worker {

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

};

void move_worker(Worker * worker, RenderWindow &window, float time, float &CurrentFrame, Houses * houses, Roads *roads){

    float player_nh_pos_x, player_nh_pos_y;
    float distance = sqrt((worker->pos_mov.x - worker->x)*(worker->pos_mov.x - worker->x) + (worker->pos_mov.y - worker->y)*(worker->pos_mov.y - worker->y));

    player_nh_pos_x = worker->x + 0.001 *time*(worker->pos_mov.x - worker->x) / distance;
    player_nh_pos_y = worker->y + 0.001 *time*(worker->pos_mov.y - worker->y) / distance;

    if (distance > 2 && worker->isMove){
        worker->x += 0.01*time *(worker->pos_mov.x - worker->x) / distance;
        worker->y += 0.01*time *(worker->pos_mov.y - worker->y) / distance;
    }

    if(is_house(houses, Vector2f(player_nh_pos_x, player_nh_pos_y), IS_PLAYER)){
        worker->x -= 0.01*time *(worker->pos_mov.x - worker->x) / distance;
        worker->y -= 0.01*time *(worker->pos_mov.y - worker->y) / distance;
    }
    if(worker->y < worker->pos_mov.y && distance > 2){
        CurrentFrame += 0.003*time / 2;
        if (CurrentFrame > 5)
            CurrentFrame -= 5;
        worker->sprite.setTextureRect(IntRect(132 + 24* (int)(CurrentFrame), 96, 16, 24));
    }
    else if(worker->y > worker->pos_mov.y && distance > 2){
        CurrentFrame += 0.003*time / 2;
        if (CurrentFrame > 5)
            CurrentFrame -= 5;
        worker->sprite.setTextureRect(IntRect(132 + 24* (int)(CurrentFrame), 1, 16, 24));
    }
    worker->update(roads, time);
}

class Player{
public:
    int cash;
    Text cash_t;
    Text cash_t2;
    Text t_name;
    long int score;
    std::string name;
    Player(std::string p_name){
        name = p_name;
        score = 0;
        cash = 20000;

        cash_t.setString("Cash: ");
        cash_t.setCharacterSize(20);
        cash_t.setColor(Color::Blue);
        cash_t.setStyle(sf::Text::Bold);
        cash_t.setPosition(1270, 600);

        t_name.setString(p_name);
        t_name.setCharacterSize(20);
        t_name.setColor(Color::Black);
        t_name.setStyle(sf::Text::Bold);
        t_name.setPosition(1270, 580);

        cash_t2.setCharacterSize(20);
        cash_t2.setColor(Color::Blue);
        cash_t2.setStyle(sf::Text::Bold);
        cash_t2.setPosition(1270, 620);

    }

    void update(){
        char n_str[20];
        cash_t2.setString(itoa(cash, n_str, 10));

    }
};


#endif // CITY_H_INCLUDED
