#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>


void Graph1(HANDLE hConsole, int zoom, COORD pos, int OX, int OY);
void clearScreen(HANDLE hConsole, COORD pos);
void Graph2(HANDLE hConsole, int zoom, COORD pos, int OX, int OY);
void DecartLines(HANDLE hConsole, int zoom, COORD pos, int OX, int OY);
void cursPos( int X, int Y);

int main (void)
{
	int zoom = 5;
	int exit = 0;
	int OX = 39;
	int OY = 13;
	int graphnum = 1;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	char ch;
	while(exit == 0){
		clearScreen(hConsole, pos);
		DecartLines(hConsole, zoom, pos, OX, OY);
		if (graphnum % 2 == 1)
			Graph1(hConsole, zoom, pos, OX, OY);
		else
			Graph2(hConsole, zoom, pos, OX, OY);
		printf("\nw - up, s - down, a - left\nd - right, + zoom in, - zoom out\ng - change graph, x - exit");
		ch = getch();
		switch (ch)
		{
			case 'g' :
            graphnum++;
			break;
			case 'd' :
            OX--;
			break;
			case 'a' :
            OX++;
			break;
			case 's' :
            OY--;
			break;
			case 'w' :
            OY++;
			break;
			case '+' :
            zoom++;
			break;
			case '-' :
            zoom--;
			break;
			case 'x' :
            exit = 1;
            cursPos(0, 25);
			break;
			default : break;
		}
	}
	int color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	SetConsoleTextAttribute(hConsole, color);
	pos.Y = 25;
	SetConsoleCursorPosition(hConsole, pos);
	puts(" ");
	return EXIT_SUCCESS;
}

void cursPos( int X, int Y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = X;
    pos.Y = Y;
    SetConsoleCursorPosition(hConsole, pos);
}

void DecartLines(HANDLE hConsole, int zoom, COORD pos, int OX, int OY)
{
    if (OX > 79)
		OX = 79;
	if (OX < 0)
		OX = 0;
	if (OY > 24)
		OY = 24;
	if (OY < 0)
		OY = 0;
	pos.X = OX;
	if (zoom < 1)
		zoom = 1;
	int color = FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN;
	SetConsoleTextAttribute(hConsole, color);
	for (pos.Y = 0; pos.Y < 25; pos.Y++)
	{
		SetConsoleCursorPosition(hConsole, pos);
		if (pos.Y % zoom == OY % zoom)
			printf("+");
		else
			printf("|");
	}
	pos.Y = OY;
	for (pos.X = 0; pos.X < 80; pos.X++)
	{
		SetConsoleCursorPosition(hConsole, pos);
		if (pos.X % zoom == OX % zoom)
			printf("+");
		else
			printf("-");
	}
}
void clearScreen(HANDLE hConsole, COORD pos)
{
	int i, j;
	int color = FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, color);

	for (i = 0; i < 25; i++)
		for (j = 0; j < 80; j++)
		{
			pos.X = j;
			pos.Y = i;
			SetConsoleCursorPosition(hConsole, pos);
				printf(" ");
		}
}
void Graph1(HANDLE hConsole, int zoom, COORD pos, int OX, int OY)
{
	int color = FOREGROUND_BLUE | FOREGROUND_GREEN |  BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, color);

	double z;
	if (zoom > 0)
		z = (double)zoom;
	else
		z = 1 / (1 - (double)zoom);
	for (pos.X = 0; pos.X < 80; pos.X++)
	{
		pos.Y = -round(z * 3 * sin(2  * ((pos.X - OX) / z )) - 2) + OY ;
		if (pos.Y < 26 && pos.Y > -1)
		{
			SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
		}
	}
	color = FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, color);
	cursPos(0, 0);
	SetConsoleCursorPosition(hConsole, pos);
	printf("F(x) = 3 * sin(2 * x) - 2");
}
void Graph2(HANDLE hConsole, int zoom, COORD pos, int OX, int OY)
{
	int color = FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_GREEN;
	SetConsoleTextAttribute(hConsole, color);

	double z;
	if (zoom > 0)
		z = (double)zoom;
	else
		z = 1 / (1 - (double)zoom);
	for (pos.X = 0; pos.X < 80; pos.X++)
	{
	    if((pos.X - OX) == 0)
            pos.X++;
		pos.Y = -round(z *  (1 / (3 * ((pos.X - OX) / z )))) + OY;
		if (pos.Y < 25 && pos.Y > -1)
		{
			SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
		}
	}
	color = FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	SetConsoleTextAttribute(hConsole, color);
	cursPos(0, 0);
	SetConsoleCursorPosition(hConsole, pos);
	printf("F(x) = 1/(3 * x)");
}
