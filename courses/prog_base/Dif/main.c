#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void strM ( char * str_in, char * str_out, int num);

int main(int argc, char ** argv)
{
    FILE * fr = NULL;
    FILE * fr1 = NULL;
    if( argc != 3)
    {
        printf("Error, invalid amount of arguments\nMust be name of input and output files");
        return 0;
    }
    fr = fopen(argv[1], "r");
    if(NULL == fr)
        return 0;
    fr1 = fopen (argv[2], "w");
    if(NULL == fr1)
        return 0;
    char string[1000];
    int num = 0;
    int i;
    int point;
    char arr[1000];
    while (!feof(fr))
    {
        point = 0;
        fscanf(fr, "%c", &string[i]);
        if(isdigit(string[i]) != 0 || string[i]== '.'|| string[i]== ' ' || string[i]== '\n')
        {
            printf("%c", string[i]);
            arr[num] = string[i];
            num++;
        }
        i++;
    }
    puts(" ");
    for(i = 0; i < num; i++)
    {
        fprintf(fr1, "%c", arr[i]);
    }
    fclose(fr);
    fclose(fr1);
    return 0;
}

