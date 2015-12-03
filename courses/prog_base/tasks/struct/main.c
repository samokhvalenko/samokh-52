#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Letter
{
    int letLen;
    char theme[20];
    char SenName[20];
};

void print(struct Letter * pVar)
{
    printf ("Changed array's fields: %i %s %s", pVar->letLen, pVar->theme, pVar->SenName);
}

void change(struct Letter * pVar, const char * newValue)
{
    strcpy(pVar->theme, newValue);
}

int count(int size, struct Letter letters[size])
{
    int val = 0, i;
    for(i = 0; i < size; i++)
    {
        if( letters[i].letLen >= 140 )
        val ++;
    }
    return val;
}

int main()
{
    fflush(stdin);
    int size = 4, val, i;
    struct Letter letters[size];
    char newVal[20];
    strcpy(letters[0].theme, "I"); strcpy(letters[1].theme, "CAN'T"); strcpy(letters[2].theme, "DO"); strcpy(letters[3].theme, "THIS");
    strcpy(letters[0].SenName, "Stas"); strcpy(letters[1].SenName, "Hadyniak"); strcpy(letters[2].SenName, "Dovakin"); strcpy(letters[3].SenName, "Zgurovskiy");
    for(i = 0; i < size; i++)
    {
       letters[i].letLen = 80 + rand() % 500 ;
    }
    for(i = 0; i < size; i++)
    {
       printf("Letter index %i lengh is %i; Letter theme is %s; Sender name is %s\n", i, letters[i].letLen, letters[i].theme, letters[i].SenName);
    }
    val = count(size, letters);
    printf("Count of letters with more then 140 words is %i\n", val);
    printf("enter the letter's theme index\n");
    scanf("%i", &i);
    printf("enter new theme less then 15 symbols\n");
    fflush(stdin);
    gets(newVal);
    change(&letters[i], newVal);
    print(&letters[i]);
    return 0;
}
