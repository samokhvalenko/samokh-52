#ifndef HOUSE_H_INCLUDED
#define HOUSE_H_INCLUDED

class House{
public:
    float w, h, dx, dy,x,y, speed;
    int dir;
    Image road_image;
    Texture road_texture, crashed_texture;
    Sprite house_sprite;

    House(float X, float Y, Sprites *spr){
        house_sprite.setTexture(spr->Sprites::house_texture);
        house_sprite.setPosition(X, Y);

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

void draw_houses(Houses * houses, RenderWindow &window){
    for(int i = 0; i < houses->houses_count; i++){
        window.draw(houses->houses[i]->house_sprite);
    }
}

bool is_house(Houses * houses, Vector2f pos){
    //std::cout << "\nX :" << pos.x << "\nY :" << pos.y;
    for(int i = 0; i < houses->houses_count-1; i++){
        if(houses->houses[i]->house_sprite.getGlobalBounds().contains(pos))
            return true;
    }
    return false;
}

#endif // HOUSE_H_INCLUDED
