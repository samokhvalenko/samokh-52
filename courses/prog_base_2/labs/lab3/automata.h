#ifndef AUTOMATA_H_INCLUDED
#define AUTOMATA_H_INCLUDED

#include "list.h"

typedef struct game_auto_s * game_auto_t;

typedef void (*react_f)(game_auto_t, void *);

game_auto_t game_auto_new();
void automata_free(game_auto_t self);

void game_auto_sub_win(game_auto_t self, void * receiver, react_f callback);
void automata_sub_win(game_auto_t self, void * receiver, react_f callback);
void automata_sub_jackpot(game_auto_t self, void * receiver, react_f callback);
void automata_send_mes(game_auto_t self, list_t * list);
void automata_run(game_auto_t  self);

#endif // AUTOMATA_H_INCLUDED
