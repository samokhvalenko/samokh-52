#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int * status = malloc(sizeof(char));
    status = 0;
    int * i = malloc(sizeof(char));
    *i = 0;
    int * first = malloc(sizeof(char));
    int * last = malloc(sizeof(char));
    char * string = malloc(sizeof(char) * 30);
    printf("Enter string, less then 30 symbols\n");
    gets (string);
    for( *i = 0; string[*i] != '\0'; (*i)++)
     printf(" %i ", (int)string[*i]);
    for(*i = 0; *i < strlen(string); (*i)++)
    {
        while(' ' == string[*i])
            (*i)++;
        if(status == 0)
            first = (int)string[*i];
        status ++;
        if(status != 0)
        while(string[*i] != '\0' || *i != strlen(string))
        {
            if(' ' != string[*i])
                last = (int) string [*i];
            (*i)++;
        }
        if(string[*i] == '\0')
            break;
    }
    printf("\n %i", (int)first);
    printf("\n %i", (int)last);
    printf("\nFirst el - last el = %i \n", ((int)first - (int)last));
    free(string);
    free(last);
    free(first);
    free(status);
    free(i);
    return 0;
}
