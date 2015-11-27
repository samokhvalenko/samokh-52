#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

void workZonePrintHello();
int scanningCommand( int com, int size, float arr[size], char **p);
void PrintVertical(int horPos, int verPos, int verPos2);
void PrintHorizontal(int horPos, int verPos, int horPos2);
void ClearThisPlease( int horPos, int verPos, int horPos2, int verPos2);
void setTextColor(int tcolor);
void cursPos( int X, int Y);
int choseCom( int com, int size, float arr[size]);
void Help();
void scanningSize();
void NullAll(int size, float arr[size]);
void ElChange(int size, float arr[size]);
void FillRand(int size, float arr[size]);
void ComMoveL(int size, float arr[size]);
void CyclMoveL(int size, float arr[size]);
void Powering(int size, float arr[size]);
void MaxToMinPlace(int size, float arr[size]);
void printArray( int size, float arr[size]);

int main()
{
    fflush(stdin);
    ClearThisPlease( 0, 0, 25, 80);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    workZonePrintHello();
    setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cursPos( 0, 0);
    printf("Welcome, master! Remember to use only numbers and english letters without CAPS");
    cursPos( 0, 2);
    printf("Here is a work\nzone for you");
    cursPos( 23, 2);
    printf("Here will be an information about your massive");
    cursPos( 23, 3);
    printf("and information about changes in it");
    setTextColor(FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    PrintHorizontal( 0, 1, 80);
    PrintHorizontal( 0, 4, 80);
	scanningSize();
    cursPos( 25, 23);
    return 0;
}

void printArr( int size, float arr[size], int y)
{
    int i;
    for(i = 0; i < size; i++)
    {
        cursPos( 24 + i*6, y);
        printf("%.2f ", arr[i]);
    }
}

void scanningSize()
{
    fflush(stdin);
    //workZonePrintHello();
    int size, status = 0, com;
    cursPos(0, 5);
    setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("Enter the\narray's size\nless then 9\n");
    status = scanf("%u", &size);
	if ( size >= 0 && size < 9)
	{
	    float arr[size];
        NullAll(size, arr);
        choseCom(com, size, arr);
	}
	else if(!status){
        workZonePrintHello();
        scanningSize(size);
	}
	else{
        workZonePrintHello();
		scanningSize(size);
	}
}

int choseCom( int com, int size, float arr[size])
{
    char *name[40] = {
    "help\n","nullall\n","elchange\n","fillrand\n","backprint\n","printsum\n","positval\n","commove\n","cyclmove\n","powering\n","firstmax\n","maxtominplace\n", "", ""  };

    char *str[40] = {
    "prints list of commands", "changes all elements to 0","changes element on ind X to value Y","Fills mass by random numbers","prints mass to reverse","prints sum of all elements",
    "prints positive elements value","moves left on X positions, new vals == 0 ","moves mass left, new vals != 0","Raises mass to the power X","prints first max element","replaces max and min elements", "", ""  };

    int i, X, Y = 12, pv = 0, maxInd, minInd;
    float sum = 0, max, min;
    char **p;
    char **z;
    p = (char **)name;
    z = (char **)str;
    com = scanningCommand(com, size, arr, p);
    switch (com)
    {
        case 0:
            ClearThisPlease(12, 0, 25, 80);
            cursPos( 0, 12);
            setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
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
            setTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            for (Y = 12;Y < 24; Y++)
            {
                cursPos( 20, Y);
                printf("==>>>");
            }
            choseCom(com, size, arr);
        case 1:
            NullAll(size, arr);
            choseCom(com, size, arr);
        case 2:
            ElChange(size, arr);
            choseCom(com, size, arr);
        case 3:
            FillRand(size, arr);
            choseCom(com, size, arr);
        case 4:
            ClearThisPlease( 5, 23, 10, 79);
            cursPos( 25, 6);
            for(i = size - 1; i > -1; i--)
            {
                printf("%.2f ", arr[i]);
            }
            choseCom(com, size, arr);
        case 5:
            ClearThisPlease( 5, 23, 10, 79);
            cursPos( 25, 6);
            for(i=0; i<size; i++)
            {
                sum = arr[i] + sum;
            }
            printf("Sum is %.2f ", sum);
            choseCom(com, size, arr);
        case 6:
            for(i=0; i<size; i++)
            {
                if( arr[i] >=0)
                pv++;
            }
            ClearThisPlease( 5, 23, 10, 79);
            cursPos( 25, 6);
            printf("Amount of positive elements is %i ", pv);
            choseCom(com, size, arr);
        case 7:
            ComMoveL( size, arr);
            choseCom(com, size, arr);
        case 8:
            CyclMoveL(size, arr);
            choseCom(com, size, arr);
        case 9:
            Powering(size, arr);
            choseCom(com, size, arr);
        case 10:
            max = arr[0];
            maxInd = 0;
            for(i = 0; i < size; i++)
                if(arr[i] > max)
                {
                    max = arr[i];
                    maxInd = i;
                }
            ClearThisPlease( 5, 23, 10, 79);
            cursPos( 25, 6);
            printf("Max element is %.2f, index is %i", max, maxInd);
            choseCom(com, size, arr);
        case 11:
            MaxToMinPlace(size, arr);
            choseCom(com, size, arr);
    }
}

void MaxToMinPlace(int size, float arr[size])
{
    float max = arr[0];
    float min = arr[0];
    int i, maxInd = 0, minInd = 0;
    for(i = 0; i < size; i++)
        if(arr[i] > max)
        {
            max = arr[i];
            maxInd = i;
        }
    for(i = 0; i < size; i++)
        if(arr[i] < min)
        {
            min = arr[i];
            minInd = i;
        }
    arr[minInd] = max;
    arr[maxInd] = min;
    printArr(size, arr, 6);
}
void NullAll( int size, float arr[size])
{
    int i;
    ClearThisPlease( 5, 23, 10, 79);
    cursPos( 25, 6);
    printArr(size, arr, 6);
}

void ComMoveL(int size, float arr[size])
{
    int com;
    ClearThisPlease(5, 0, 11, 20);
    cursPos(0, 5);
    setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    int m, i;
    printf("Enter the amount\nof moves\nless then size\n");
    scanf("%i", &m);
    if(!m || m <=0 || m >=size)
        choseCom(com, size, arr);
    for(i = 0; i < size; i++)
    {
        arr[i] = arr[i+m];
        if(i > size - m)
            arr[i] = 0;
    }
    //ClearThisPlease( 5, 23, 10, 79);
    printArr(size, arr, 7);
    choseCom(com, size, arr);
}

void CyclMoveL(int size, float arr[size])
{
    int com;
    ClearThisPlease(5, 0, 11, 20);
    cursPos(0, 5);
    setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    int m, i, z;
    float c = arr[0];
    printf("Enter the amount\nof moves\nless then size\n");
    scanf("%i", &m);
    if(!m || m <=0 || m >=size)
        choseCom(com, size, arr);
    for(z = 0; z < m; z++)
    {
        for(i = 0; i < size-1;i++)
            arr[i] = arr[i + 1];
        arr[size-1] = c;
        c = arr[0];
    }
    printArr(size, arr, 7);
    choseCom(com, size, arr);
}

void Powering(int size, float arr[size])
{
    cursPos( 0, 5);
    setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    int status = 0, power, i, com;
    printf("Enter the power,\nless then 5\nbigger then -5\n");
    status = scanf("%i", &power);
	if(!status || power > 5 || power < -5)
        choseCom(com, size, arr);
    ClearThisPlease( 5, 23, 10, 79);
    cursPos( 25, 6);
    for(i = 0; i < size; i++)
        arr[i] = pow(arr[i], power);
    printArr(size, arr, 6);
}

void FillRand(int size, float arr[size])
{
    time_t t;
    int i, X = 5, Y = 30;
    srand( time(&t));
    cursPos( 0, 5);
    setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    ClearThisPlease( 5, 23, 10, 79);
    cursPos( 25, 6);
    ClearThisPlease( 5, 23, 10, 79);
    for(i=0; i<size; i++)
        arr[i] = ((float)rand()/(float)(RAND_MAX) * 50);
    printArr(size, arr, 6);
    cursPos( 0, 5);
}

void ElChange(int size, float arr[size])
{
    int i, X, status = 0;
    float z;
    ClearThisPlease(5, 0, 11, 20);
    cursPos( 0, 5);
    printf("Enter elements\nindex and value,\n (0___99)\n");
    status = scanf("%u", &i);
	if (!status ||i > size || i < 0)
	{
	    cursPos(0, 24);
		printf("you entered wrong value\n");
		ElChange(size, arr);
	}
    status = scanf("%f", &z);
    if ( !status || z < 0 || z > 99)
    {
        cursPos(0, 24);
		printf("you entered wrong value\n");
		ElChange(size, arr);
    }
    arr[i] = z;
    ClearThisPlease( 5, 23, 10, 79);
    printArr(size, arr, 6);
    cursPos( 23, 7);
}

void workZonePrintHello()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    ClearThisPlease( 5, 23, 10, 79);
    ClearThisPlease(5, 0, 11, 20);
    setTextColor(FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    PrintHorizontal( 0, 11, 80);
    PrintVertical( 20, 2, 11);
    setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cursPos( 0, 12);
    printf("0.Help 1.NullAll 2.ElChange 3.FillRand 4.BackPrint 5.PrintSum 6.PositVal \n7.ComMove 8.CyclMove 9.Powering 10.FirstMax. 11.MaxToMinPlace\n12.ReturnLast ");
}


int scanningCommand( int com , int size, float arr[size], char **p)
{
    fflush(stdin);
    char buffer[15];
    int i;
    com = 0;
    ClearThisPlease(5, 0, 11, 20);
    ClearThisPlease( 5, 23, 10, 79);
    cursPos( 0, 5);
    setTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    puts("Enter command: ");
    fgets(buffer, 15,stdin);
    for(com = 0; com < 13; com++)
    {
        if(!strcmp(*p, buffer))
            return com;
        else
            *p++;
    }
    ClearThisPlease(5, 0, 11, 20);
    cursPos( 0, 5);
    printf("Wrong command");
    setTextColor(FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    PrintHorizontal( 0, 1, 80);
    PrintHorizontal( 0, 4, 80);
    PrintHorizontal( 0, 11, 80);
    PrintVertical( 20, 2, 11);
    choseCom(com, size, arr);
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

void setTextColor(int tcolor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    SetConsoleTextAttribute(hConsole, tcolor);
}

void cursPos( int X, int Y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = X;
    pos.Y = Y;
    SetConsoleCursorPosition(hConsole, pos);
}
