#include <stdio.h>
#include <stdlib.h>

#include "event.h"
#include "list.h"
#include "automata.h"

struct game_auto_s
{
    list_t * event_almostWin;
    list_t * event_win;
    list_t * event_jackpot;
};

game_auto_t game_auto_new()
{
    game_auto_t self = malloc(sizeof(struct game_auto_s));
    self->event_almostWin = list_new();
    self->event_win = list_new();
    self->event_jackpot = list_new();
    return self;
}

void automata_free(game_auto_t self)
{
    int count1 = list_get_count(self->event_almostWin);
    int count2 = list_get_count(self->event_win);
    int count3 = list_get_count(self->event_jackpot);

    for (int i = 0; i < count1; i++)
    {
        event_t * ev = list_pop_back(self->event_almostWin);
        free(ev);
    }
    for (int i = 0; i < count2; i++)
    {
        event_t * ev = list_pop_back(self->event_win);
        free(ev);
    }
    for (int i = 0; i < count3; i++)
    {
        event_t * ev = list_pop_back(self->event_jackpot);
        free(ev);
    }
    list_free(self->event_almostWin);
    list_free(self->event_win);
    list_free(self->event_jackpot);
    free(self);
}


void game_auto_sub_win(game_auto_t self, void * receiver, react_f callback)
{
    event_t * sb = malloc(sizeof(struct event_s));
    sb->receiver = receiver;
    sb->callback = callback;
    list_push_back(self->event_almostWin, sb);
}

void automata_sub_win(game_auto_t self, void * receiver, react_f callback)
{
    event_t * sb = malloc(sizeof(struct event_s));
    sb->receiver = receiver;
    sb->callback = callback;
    list_push_back(self->event_win, sb);
}

void automata_sub_jackpot(game_auto_t self, void * receiver, react_f callback)
{
    event_t * sb = malloc(sizeof(struct event_s));
    sb->receiver = receiver;
    sb->callback = callback;
    list_push_back(self->event_jackpot, sb);
}

void automata_send_mes(game_auto_t self, list_t * list)
{
    for (int i = 0; i<list_get_count(list); i++)
    {
        event_t * ev = list_get_el(list, i);
        if (NULL != ev->callback)
        {
            react_f fn = ev->callback;
            fn(self, ev->receiver);
        }
    }
}

void automata_run(game_auto_t  self)
{
    int arr[3];
    for(int i = 0; i<3; i++)
    {
        arr[i] = rand() % 10;
    }
    printf("%d %d %d\n", arr[1], arr[2], arr[3]);
    if(arr[1] == arr[2] && arr[2] == arr[3] && arr[1] != 7)
        automata_send_mes(self, self->event_win);
    else if(arr[1] == arr[2] || arr[2] == arr[3] || arr[1] == arr[3])
        automata_send_mes(self, self->event_almostWin);

    if(arr[1] == 7 && arr[2] == 7 && arr[3] == 7)
        automata_send_mes(self, self->event_jackpot);
}
