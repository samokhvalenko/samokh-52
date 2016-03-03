#include "arraydz.h"
#include "time.h"
#define MAX_ARRAY_SIZE 50


struct list_s{
	int *arr;
	int size;
};

list_t * list_new(int size) {
	if (size <= 0 || size >= MAX_ARRAY_SIZE)
		return NULL;
    list_t * self = malloc(sizeof(struct list_s));
    self->arr = malloc( size  * sizeof(int));
    self->size = size;
    return self;
}

void list_random(list_t * arr, unsigned max){
	int i;
	for(i = 0; i < arr->size; i++)
		arr->arr[i] = -50 + rand() % max;

}

int list_length(list_t * arr)
{
	return arr->size;
}

void list_print(list_t * arr){
	int i;
	for(i = 0 ; i < arr->size; i++)
		printf ("%i ", arr->arr[i]);
	printf("\n");
}

void list_remove(list_t ** arr){

	free((*arr)->arr);
	free(*arr);
	*arr = NULL;
}


int list_add(list_t * arr, int index , int elem ){

if(index > arr->size || index < 0){
	return 1;
}
if(arr->size+1 >= MAX_ARRAY_SIZE){
    return 0;
}
if(index == arr->size){
    arr->size++;
    arr->arr[index] = elem;
}
else{
    int i;
    arr->size++;
    for(i = arr->size-1; i >= index; i--){
        arr->arr[i+1] = arr->arr[i];
    }
    arr->arr[index] = elem;
}
return 0;
}

int list_del(list_t * arr , int index){
    if(index < 0 || index >= arr->size)
    {
        printf("\nThere is no element with this index\n");
        return 0;
    }
    int i;
    for(i = index; i <= arr->size - 1; i++)
    {
        arr->arr[i] = arr->arr[i+1];
    }
    arr->size--;
    return 0;
}

int list_count_pos(list_t * arr){
    int i;
    int count = 0;
    for(i = 0; i < arr->size; i++){
        if(arr->arr[i] > 0)
            count++;
    }
    return count;
}

int list_count_neg(list_t * arr){
    int i;
    int count = 0;
    for(i = 0; i < arr->size; i++){
        if(arr->arr[i] < 0)
            count++;
    }
    return count;
}

int list_count_null(list_t * arr){
    int i;
    int count = 0;
    for(i = 0; i < arr->size; i++){
        if(arr->arr[i] == 0)
            count++;
    }
    return count;
}
