#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "event.h"

typedef struct list_s list_t;

list_t * list_new();

void list_free(list_t * self);

void list_push_back(list_t * self, event_t * ptr);

event_t * list_pop_back(list_t * self);

int list_get_count(list_t * self);

event_t * list_get_el(list_t * self, int index);


#endif // LIST_H_INCLUDED
