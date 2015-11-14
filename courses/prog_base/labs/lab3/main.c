#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

void workZonePrintHello();
int scanningCommand( int com);
void PrintVertical(int horPos, int verPos, int verPos2);
void PrintHorizontal(int horPos, int verPos, int horPos2);
void ClearThisPlease( int horPos, int verPos, int horPos2, int verPos2);
void color(int tcolor);
void cursPos( int X, int Y);
int choseCom(int com);
void Help();
void NullAll();
void ElChange();
void FillRand(int size);
void BackPrint();
void PrintSum();
void PositVal();
void ComMovL();
void CyclMovL();
void Powering();
void FirstMax();
void MaxToMinPlace();
void ReturnLast();


int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int masLen, com;
    workZonePrintHello();
    cursPos( 0, 5);
    color(1);
    printf("Chose the name of a\ncommand. Do this\n with numbers. Chose\nHelp if you need\nthe explanation\n");
    cursPos( 0, 12);
    printf("0.Help 1.NullAll 2.ElChange 3.FillRand 4.BackPrint 5.PrintSum 6.PositVal \n7.ComMovL 8.CyclMovL 9.Powering 10.FirstMax. 11.MaxToMinPlace\n12.ReturnLast ");
    cursPos( 0, 10);
    com = scanningCommand(com);
    choseCom(com);
    cursPos( 25, 23);
}

char *name[][40] = {
  "1.NullAll","2.ElChange","3.FillRand","4.BackPrint","5.PrintSum","6.PositVal","7.ComMovL","8.CyclMovL","9.Powering","10.FirstMax","11.MaxToMinPlace","12.ReturnLast", "", ""  };

  char *str[][40] = {
  "changes all elements to 0","changes element on ind X to value Y","Fills mass by random numbers","prints mass to reverse","prints sum of all elements",
  "prints positive elements value","moves left on X positions, new vals == 0 ","moves mass left, new vals != 0","Raises mass to the power X","prints first max element","replaces max and min elements","returns last changes", "", ""  };

int choseCom( int com)
{
    int i, X, size, Y = 12;
    char **p;
    char **z;
    p = (char **)name;
    z = (char **)str;
    switch (com)
    {
        case 0:
            ClearThisPlease(12, 0, 25, 80);
            cursPos( 0, 12);
            color(1);
            for(i = 0; i < 12; i++)
            {
                cursPos( 0, Y);
                puts(*p++);
                Y++;
            }
            Y = 12;
            for(i = 0; i < 12; i++)
            {
                cursPos( 30, Y);
                puts(*z++);
                Y++;
            }
            color(4);
            for (Y = 12;Y < 24; Y++)
            {
                cursPos( 20, Y);
                printf("==>>>");
            }
            break;
        case 3:
            FillRand(size);
            break;
    }
}

void FillRand(int size)
{
    time_t t;
    int i, X = 5, Y = 30;
    srand((unsigned) time(&t));
    ClearThisPlease(5, 0, 11, 20);
    cursPos( 0, 5);
    printf("Enter the size\nof massive");
    cursPos( 0, 7);
    scanf("%i", &size);
    cursPos( 0, 8);
    printf("%i", size);
    int mas[size];
    cursPos( 25, 6);
    for(i=0; i<size; i++)
    {
        mas[i] = (1 + rand() % 99);
        printf(" %i ", mas[i]);
        Y++;
    }
}

void workZonePrintHello()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int i,j, verPos, horPos, horPos2, verPos2;
    ClearThisPlease( 0, 0, 25, 80);
    color(3);
    PrintHorizontal( 0, 1, 80);
    PrintHorizontal( 0, 4, 80);
    PrintHorizontal( 0, 11, 80);
    PrintVertical( 20, 2, 11);
    color(1);
    cursPos( 20, 0);
    printf("Welcome, master");
    cursPos( 0, 2);
    printf("Here is a work\nzone for you");
    cursPos( 23, 2);
    printf("Here will be an information about your massive");
    cursPos( 23, 3);
    printf("and information about changes in it");
    color(0);
}

int scanningCommand( int com)
{
    scanf("%i", &com);
    return com;
}

void PrintVertical(int horPos, int verPos, int verPos2)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int i;
    for (i = verPos; i < verPos2; i++)
    {
        cursPos( horPos, i);
        printf("|*|");
    }
}

void PrintHorizontal(int horPos, int verPos, int horPos2)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int i;
    for (i = horPos; i < horPos2; i++)
    {
        cursPos( i, verPos);
        printf("*");
    }
}

void ClearThisPlease( int horPos, int verPos, int horPos2, int verPos2)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int i,j;
    for (i = horPos; i < horPos2; i++)
		for (j = verPos; j < verPos2; j++)
		{
			cursPos( j, i);
			putchar(' ');
			if ( i == 24 && j==80)
                cursPos( 25, 0);
		}
}

void color(int tcolor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    const int FI_FR = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const int FI = FOREGROUND_INTENSITY | BACKGROUND_BLUE;
    const int DefaultColor = 7;
    const int FY = FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const int BG =  FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    switch(tcolor)
    {
        case 1:
            SetConsoleTextAttribute(hConsole, FI_FR);
            break;
        case 2:
            SetConsoleTextAttribute(hConsole, FI);
            break;
        case 0:
            SetConsoleTextAttribute(hConsole, DefaultColor);
            break;
        case 3:
            SetConsoleTextAttribute(hConsole, FY);
            break;
        case 4:
            SetConsoleTextAttribute(hConsole, BG);
            break;
    }
}

void cursPos( int X, int Y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = X;
    pos.Y = Y;
    SetConsoleCursorPosition(hConsole, pos);
}
