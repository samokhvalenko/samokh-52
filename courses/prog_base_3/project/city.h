#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "textures.h"

using namespace sf;

class Player {

public:
	float w, h, dx, dy,x,y, speed;
	int dir, playerScore, health;
	bool isMove,isSelect;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player( float X, float Y){
		dir = 0; speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
        isMove = false; isSelect = false;
		image.loadFromFile("worker.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(180, 96, 16, 24));
        //sprite.setOrigin(w / 2, h / 2);
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0:
		    dx = speed;
		    dy = 0;
		    break;
		case 1:
		    dx = -speed;
		    dy = 0;
		    break;
		case 2:
		    dx = 0;
		    dy = speed;
		    break;
		case 3:
		    dx = 0;
		    dy = -speed;
		    break;
		}

		x += dx*time;
		y += dy*time;
		if (!isMove)
            speed = 0;
		sprite.setPosition(x, y);

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


#endif // CITY_H_INCLUDED
