#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

#include <time.h>

#include "list.h"

typedef void (*check)(list_t self);

int main(void) {

    check l_ch = NULL;

    int size;

    srand(time(NULL));
    int dll_num;

    printf("Enter the size of list\n");
    scanf("%i", &size);

    printf("\nChoose the number of dll please\n");
    scanf("%i", &dll_num);

    HINSTANCE hLib;

    if( dll_num == 1){
        hLib = LoadLibrary("Lab2DLL1.dll");
    }
    else if( dll_num == 2){
        hLib = LoadLibrary("Lab2DLL2.dll");
    }

    l_ch = (check)GetProcAddress(hLib, "list_check");

    list_t arr = list_new(size);

    for(int i = 0; i < size; i++){
        list_add(arr, rand() % 10, i);
    }
    list_print(arr);

    while(1){
        list_fill(arr);
        list_print(arr);

        l_ch(arr);
    }

    list_free(arr);

    return 0;
}
