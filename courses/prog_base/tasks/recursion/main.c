#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int recursiveDich(char * pStart, int sum, int status,int len, int first, int last)
{
    if(status == len || *pStart == '\0')
    {
        sum = first * last;
        return sum;
    }
    else if( *pStart == ' ')
    {
        pStart++;
        recursiveDich(pStart,sum, status, len, first, last);
    }
    else
    {
        if(status == 0)
            first = (int)*pStart;
        if(status != 0 && *pStart != ' ')
            last = (int)*pStart;
        printf(" %i ", (int)*pStart);
        pStart++;
        status++;
        recursiveDich(pStart,sum, status, len, first, last);
    }
}

int main()
{
    int sum = 0, status = 0, first, last;
    char string[30];
    printf("Enter string, less then 30 symbols\n");
    gets(string);
    int len = strlen(string);
    char * pStart = &string;
    sum = recursiveDich( pStart, sum, status, len, 0, 0);
    printf("\n %i", sum);
    return 0;
}
