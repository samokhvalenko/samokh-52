#include <stdio.h>
#include <stdlib.h>

#include "event.h"
#include "user.h"
#include "automata.h"

struct player_s
{
    char name[100];
    char reaction[100];
};

struct press_s
{
    char name[100];
    char reaction[100];
};

struct administration_s
{
    char name[100];
    char reaction[100];
};

player_t user_new_player(const char * name)
{
    player_t self = malloc(sizeof(struct player_s));
    strcpy(self->name, name);
    return self;
}

press_t user_new_press(const char * name)
{
    press_t self = malloc(sizeof(struct press_s));
    strcpy(self->name, name);
    return self;
}

administration_t user_new_admin(const char * name)
{
    administration_t self = malloc(sizeof(struct administration_s));
    strcpy(self->name, name);
    return self;
}

void user_free_player(player_t self)
{
    free(self);
}

void user_free_press(press_t self)
{
    free(self);
}

void user_free_admin(administration_t self)
{
    free(self);
}

int user_near_win_player_react(game_auto_t sender, void * receiver)
{
    player_t pl = (player_t)receiver;
    strcpy(pl->reaction, "is near to win");
    printf("Player %s %s\n", pl->name, pl->reaction);
    return near_to_win;
}

int user_win_player_react(game_auto_t sender, void * receiver)
{
    player_t pl = (player_t)receiver;
    strcpy(pl->reaction, "win!!!!!");
    printf("Player %s %s\n", pl->name, pl->reaction);
    return win;
}

int user_jack_player_react(game_auto_t sender, void * receiver)
{
    player_t pl = (player_t)receiver;
    strcpy(pl->reaction, "win JACKPOT!!!!!");
    printf("Player %s %s\n", pl->name, pl->reaction);
    return jackpot;
}

static void user_press_reaction(game_auto_t sender, void * receiver)
{
    press_t pr = (press_t)receiver;
    strcpy(pr->reaction, "press knows");
    printf("%s %s\n", pr->name, pr->reaction);
}

static void user_admin_reaction(game_auto_t sender, void * receiver)
{
    administration_t ad = (administration_t)receiver;
    strcpy(ad->reaction, "administration knows");
    printf("%s %s\n", ad->name, ad->reaction);
}

react_f user_get_cb_alm_win(player_t self)
{
    return user_near_win_player_react;
}

react_f user_get_cb_win(player_t self)
{
    return user_win_player_react;
}

react_f user_get_cb_jackpot_player(player_t self)
{
    return user_jack_player_react;
}

react_f user_get_cb_jackpot_press(press_t self)
{
    return user_press_reaction;
}

react_f user_get_cb_jackpot_admin(administration_t self)
{
    return user_admin_reaction;
}
