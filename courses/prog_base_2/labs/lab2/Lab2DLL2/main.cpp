#include "main.h"
#include "stdio.h"

// a sample exported function
void DLL_EXPORT list_check(list_t self){
    int sum = 0;
    for(int i = 0; i < list_getsize(self); i++){
        sum = sum + list_getelem(self, i);
    }
    list_react(sum);
}

void DLL_EXPORT list_react(int react){
    if(react > 255)
        printf("\nOVERFLOW\n");
    else
        printf("\nNO OVERFLOW\n");
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
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
