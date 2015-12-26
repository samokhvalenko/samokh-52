#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char buffer[20];
    char *com;
    char *reg;
    char *reg1;
    int space = 0;
    int ax = 0, bx = 0, cx = 0, a, b, c, d;
    while(1){
        printf("Enter\n");
        fflush(stdin);
        gets(buffer);
        com = strtok(buffer, " ");
        if(!strcmp(com, "mov"))
        {
            reg = strtok(NULL, " ");
            a = atoi(strtok(NULL, " "));
            if( !strcmp("ax", reg))
                ax = a;
            if( !strcmp("bx", reg))
                bx = a;
            if( !strcmp("cx", reg))
                cx = a;
        }
        else if(!strcmp(com, "add"))
        {
            reg = strtok(NULL, " ");
            reg1 = strtok(NULL, " ");
            int *rg1;
            int *rg2;
            if( !strcmp("ax", reg))
                rg1 = &ax;
            if( !strcmp("bx", reg))
                rg1 = &bx;
            if( !strcmp("cx", reg))
                rg1 = &cx;
            if( !strcmp("ax", reg1))
                rg2 = &ax;
            if( !strcmp("bx", reg1))
                rg2 = &bx;
            if( !strcmp("cx", reg1))
                rg2 = &cx;
            *rg1 += *rg2;
        }
        else if(!strcmp(com, "imul"))
        {
            reg = strtok(NULL, " ");
            reg1 = strtok(NULL, " ");
            int *rg1;
            int *rg2;
            if( !strcmp("ax", reg))
                rg1 = &ax;
            if( !strcmp("bx", reg))
                rg1 = &bx;
            if( !strcmp("cx", reg))
                rg1 = &cx;
            if( !strcmp("ax", reg1))
                rg2 = &ax;
            if( !strcmp("bx", reg1))
                rg2 = &bx;
            if( !strcmp("cx", reg1))
                rg2 = &cx;
            *rg1 *= *rg2;
        }
         else if(!strcmp(com, "sub"))
        {
            reg = strtok(NULL, " ");
            reg1 = strtok(NULL, " ");
            int *rg1;
            int *rg2;
            if( !strcmp("ax", reg))
                rg1 = &ax;
            if( !strcmp("bx", reg))
                rg1 = &bx;
            if( !strcmp("cx", reg))
                rg1 = &cx;
            if( !strcmp("ax", reg1))
                rg2 = &ax;
            if( !strcmp("bx", reg1))
                rg2 = &bx;
            if( !strcmp("cx", reg1))
                rg2 = &cx;
            *rg1 -= *rg2;
        }
        else if(!strcmp(com, "out"))
        {
            printf("\n%i %i %i\n", ax, bx, cx);
        }
        else if(!strcmp(com, "exit"))
            return 0;
    }

    return 0;
}
