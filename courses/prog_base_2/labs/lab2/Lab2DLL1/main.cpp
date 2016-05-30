#include "main.h"
#include <stdio.h>
// a sample exported function
void DLL_EXPORT list_check(list_t self) {
    int mid = 0;
    for(int i = 0; i < list_getsize(self); i++){
        mid = mid + list_getelem(self, i);
    }
    mid = mid / list_getsize(self);
    if( mid >= 0)
        list_react(1);
    else if(mid < 0)
        list_react(0);
}

void DLL_EXPORT list_react(int react) {
    if( react == 1)
        printf("\nPositive\n");
    else if(react == 0)
        printf("\nNegative\n");
}

// insert another exported functions here, add DLL_EXPORT to all of them

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
