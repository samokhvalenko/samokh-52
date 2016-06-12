#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "db.h"
using namespace sf;
bool cmp1(Player* p1, Player* p2);

void show_scores(RenderWindow &window){
    Font font;
    font.loadFromFile("arial.ttf");
    db_t * db = db_new("players.db");
    std::vector <Player *> players;
    db_get_players(db, &players);
    db_free(db);
    for(int i = 0; i < players.size(); i++){
        std::cout << "\nPlayer name: " << players[i]->name;
        std::cout << "\nPlayer score: " << players[i]->score;
    }

    std::sort(players.begin(), players.end(), cmp1);

    Text name("Player name", font, 45);
    name.setPosition(400, 20);
    name.setColor(Color::Black);

    Text score("Player score", font, 45);
    score.setPosition(700, 20);
    score.setColor(Color::Black);
    char str[10];
    Text name_text[players.size()];
    Text score_text[players.size()];
    for(int i = 0; i < players.size(); i++){
        name_text[i].setFont(font);
        name_text[i].setColor(Color::Black);
        name_text[i].setCharacterSize(40);
        name_text[i].setString(players[i]->name);
        name_text[i].setPosition(450, (i + 2) * 50);

        score_text[i].setFont(font);
        score_text[i].setColor(Color::Black);
        score_text[i].setCharacterSize(40);
        sprintf(str, "%d", players[i]->score);
        score_text[i].setString(str);
        score_text[i].setPosition(700, (i + 2) * 50);
    }


    while(1){

        window.clear(Color::White);

        for(int i = 0; i < players.size(); i++){
            window.draw(name_text[i]);
            window.draw(score_text[i]);

        }

        if(Keyboard::isKeyPressed(Keyboard::Escape))
            return;
        window.draw(name);
        window.draw(score);

        window.display();

    }
}

bool cmp1(Player* p1, Player* p2){
        return p1->score > p2->score;
}
