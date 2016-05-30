#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "event.h"
#include "automata.h"

typedef struct player_s * player_t;
typedef struct press_s * press_t;
typedef struct administration_s * administration_t;

player_t user_new_player(const char * name);
press_t user_new_press(const char * name);
administration_t user_new_admin(const char * name);

enum status {near_to_win = 1, win, jackpot} status_g;

react_f user_get_cb_alm_win(player_t self);
react_f user_get_cb_win(player_t self);
react_f user_get_cb_jackpot_player(player_t self);
react_f user_get_cb_jackpot_press(press_t self);
react_f user_get_cb_jackpot_admin(administration_t self);

#endif // USER_H_INCLUDED
