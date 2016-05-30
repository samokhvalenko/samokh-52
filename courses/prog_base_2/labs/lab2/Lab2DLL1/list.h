#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct list_s * list_t;
list_t list_new( int size);

void list_fill();

int list_getsize(list_t self);

int list_getelem(list_t self, int index);

#endif // LIST_H_INCLUDED
