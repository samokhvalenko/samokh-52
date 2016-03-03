#ifndef ARRAY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#define MAX_ARRAY_SIZE 50

typedef struct list_s list_t;
list_t * list_new(int size);
void list_random(list_t * arr, unsigned max);
void list_print(list_t * arr);
void list_remove(list_t ** arr);
int list_length(list_t * arr);
int list_add(list_t * arr , int index , int elem);
int list_del(list_t * arr , int index);
int list_count_pos(list_t * arr);
int list_count_neg(list_t * arr);
int list_count_null(list_t * arr);


#endif
