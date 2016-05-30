#include <stdlib.h>
#include <stdio.h>

#include "list.h"

struct list_s{
    int size;
    char * arr;
};

list_t list_new( int size){
    list_t self;
    self = malloc(sizeof(struct list_s));
    self->size = size;
    self->arr = malloc(sizeof(char)*size);
    return self;
}

void list_free(list_t self){
    free(self->arr);
    free(self);
}

void list_fill(list_t self){
    for(int i = 0; i < self->size; i++){
        printf(" Enter value please ");
        scanf("%i", &self->arr[i]);
    }
}

void list_add(list_t self, int elem, int index){
    self->arr[index] = elem;
}

void list_print(list_t self){
    printf("List:\n");
    for(int i = 0; i < self->size; i++){
        printf("%i ", self->arr[i]);
    }
    printf("\n");
}

int list_getsize(list_t self){
    return self->size;
}

int list_getelem(list_t self, int index){
    return self->arr[index];
}

