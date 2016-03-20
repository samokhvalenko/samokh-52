#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef int (*CallBackFunc)(char * str, int index, int count);
typedef void (*CallBackFunc1)(char * str);
void longCB2 (char * str);
void longCB1 (char * str);
int shortCB2 (char * str, int index, int count);
int shortCB1 (char * str, int index, int count);
void process(char * str, CallBackFunc shortCB, CallBackFunc1 longCB);

int main()
{
    CallBackFunc1 long1 = longCB1;
    CallBackFunc1 long2 = longCB2;
    CallBackFunc short1 = shortCB1;
    CallBackFunc short2 = shortCB2;
    char str[300];
    gets(str);
    process(str, short1, long1);
    process(str, short2, long2);
    //printf("\nHello world!\n");
    return 0;
}

void process(char * str, CallBackFunc shortCB, CallBackFunc1 longCB){
    int len = 0, i = 0, count = 0, index = 0;;
    char str_out[100];
    int j;
    while(i < strlen(str)){
        len = 0;
        j = 0;
        str_out[j+1] = '\0';
        for(j = 0; str[i] != '.';j++){
            len++;
            str_out[j] = str[i];
            i++;
        }
        index++;
        i++;
        str_out[j] = '\0';
        if(len >= 20)
            longCB(str_out);
        if(len <= 5){
            count = shortCB(str_out, index, count);
        }
    }
    printf("\nAmount of small sentences: %i", count);
}

void longCB2 (char * str){
    printf("\nThis sentence is longer than 20 symbols %s,\n but it`s printing in another CB-function :)\nI will print every word of it in a new line \n", str);
    for(int i = 0; str[i] != '\0'; i++){
        printf("%c", str[i]);
        if(str[i] == ' ')
            printf("\n");
    }
}
void longCB1 (char * str){
    printf("\nThis sentence is longer than 20 symbols: %s\n", str);
}
int shortCB2 (char * str, int index, int count){
    printf("\nHere is our small sentence and his index: %i %s\n", index, str);
    count++;
    return count;
}
int shortCB1 (char * str, int index, int count){
    count++;
    //printf("\nAmount of small sentences: %i", count);
    return count;
}
