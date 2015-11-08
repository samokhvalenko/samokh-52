#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	int dont_eat_that_snow = BACKGROUND_RED | BACKGROUND_GREEN; /* Yellow */
    int not_a_nigger = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; /* White */
    int shmal = BACKGROUND_GREEN; /*Green*/
	int i,j,g;
    pos.X = 0;
    pos.Y = 24;
	const long SLEEP_MILLISECONDS = 1;
	for (i = 0; i < 25; i++)
		for (j = 0; j < 81; j++)
		{
			pos.X = j;
			pos.Y = i;
			SetConsoleCursorPosition(hConsole, pos);
			putchar(' ');
		}
	for(pos.X = 0; pos.X < 26;pos.X++)
	{
		for (pos.Y = 24 ; pos.Y >= 0; pos.Y--)
		{
			Sleep(SLEEP_MILLISECONDS);
			SetConsoleCursorPosition(hConsole, pos);

			    switch (( pos.Y + 80 - pos.X ) % 3)
                    {
                        case 0: SetConsoleTextAttribute(hConsole, shmal); break;
                        case 1: SetConsoleTextAttribute(hConsole, not_a_nigger); break;
                        case 2: SetConsoleTextAttribute(hConsole, dont_eat_that_snow); break;
                    }
			printf("*");
		}
		pos.X++;
		for (pos.Y = 0 ; pos.Y <= 24; pos.Y++)
		{
			Sleep(SLEEP_MILLISECONDS);
			SetConsoleCursorPosition(hConsole, pos);
			    switch (( pos.Y + 80 - pos.X ) % 3)
                    {
                        case 0: SetConsoleTextAttribute(hConsole, shmal); break;
                        case 1: SetConsoleTextAttribute(hConsole, not_a_nigger); break;
                        case 2: SetConsoleTextAttribute(hConsole, dont_eat_that_snow); break;
                    }
			printf("*");
		}
	}
	for(pos.X = 26; pos.X < 80; pos.X++)
    {
        for (pos.Y = 24 ; pos.Y >= 0; pos.Y--)
		{
			Sleep(SLEEP_MILLISECONDS);
			SetConsoleCursorPosition(hConsole, pos);
			switch ( (pos.X - pos.Y) )
			{
			    case 26:
                    SetConsoleTextAttribute(hConsole, not_a_nigger);
                    printf("*");
                    break;
                default:
                    if ((pos.X - pos.Y) > 26)
                    switch (( pos.Y + 80 - pos.X ) % 3)
                        {
                            case 0: SetConsoleTextAttribute(hConsole, not_a_nigger); break;
                            case 1: SetConsoleTextAttribute(hConsole, shmal); break;
                            case 2: SetConsoleTextAttribute(hConsole, dont_eat_that_snow); break;
                        }
                    else
                      switch (( pos.Y + 80 - pos.X ) % 3)
                        {
                            case 0: SetConsoleTextAttribute(hConsole, shmal); break;
                            case 1: SetConsoleTextAttribute(hConsole, not_a_nigger); break;
                            case 2: SetConsoleTextAttribute(hConsole, dont_eat_that_snow); break;
                        }
                printf("*");
            }
		}
		pos.X++;
		for (pos.Y = 0 ; pos.Y <= 24; pos.Y++)
		{
			Sleep(SLEEP_MILLISECONDS);
			SetConsoleCursorPosition(hConsole, pos);
			switch ( (pos.X - pos.Y) )
			{
			    case 26:
                    SetConsoleTextAttribute(hConsole, not_a_nigger);
                    printf("*");
                    break;
                default:
                    if ((pos.X - pos.Y) > 26)
                        switch (( pos.Y + 80 - pos.X ) % 3)
                        {
                            case 0: SetConsoleTextAttribute(hConsole, not_a_nigger); break;
                            case 1: SetConsoleTextAttribute(hConsole, shmal); break;
                            case 2: SetConsoleTextAttribute(hConsole, dont_eat_that_snow); break;
                        }
                    else
                      switch (( pos.Y + 80 - pos.X ) % 3)
                        {
                            case 0: SetConsoleTextAttribute(hConsole, shmal); break;
                            case 1: SetConsoleTextAttribute(hConsole, not_a_nigger); break;
                            case 2: SetConsoleTextAttribute(hConsole, dont_eat_that_snow); break;
                        }
			printf("*");
            }
		}
    }
	return 0;
}
