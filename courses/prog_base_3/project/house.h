#ifndef HOUSE_H_INCLUDED
#define HOUSE_H_INCLUDED

class House{
public:
    float w, h, dx, dy,x,y, speed;
    int dir;
    Image road_image;
    Texture road_texture, crashed_texture;
    Sprite road_sprite;

    House(float X, float Y, Sprites *spr){
        road_sprite.setTexture(spr->Sprites::house_texture);
        road_sprite.setPosition(X, Y);

    }
};

class Houses{
public:
    int houses_count;
    std::vector< House *> houses;
    Texture house_texture;

    Houses(){
        house_texture.loadFromFile("house_small.png");
    }
};

#endif // HOUSE_H_INCLUDED
