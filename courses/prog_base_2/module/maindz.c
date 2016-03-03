#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arraydz.h"
#include "time.h"
#include <locale.h>

int main(void){
	srand(time(NULL));
	int size;
	int elem;
    int index;

	printf ("Please enter size array\n");
	scanf("%i" , &size);
	list_t * arr = list_new(size);

    list_random(arr, 100);
    list_print(arr);

    printf ("Please enter new element\n");
    scanf("%i", &elem);

    printf ("Please enter index\n");
    scanf("%i", &index);

    list_add(arr, index, elem);
    list_print(arr);

    printf ("Please enter index of element wich you want to delete\n");
    scanf("%i", &index);

    list_del(arr, index);
    list_print(arr);

    printf("Size = %i\n", list_length(arr));

    printf("Amount of positive elements: %i\n", list_count_pos(arr));

    printf("Amount of negative elements: %i\n", list_count_neg(arr));

    printf("Amount of nul elements: %i\n", list_count_null(arr));

    list_remove(&arr);

    if(arr == NULL)
        printf("success");
	return 0;
}
