#include <stdio.h>
int run(int moves[], int movesLen, int res[], int resLen);
int main()
{
	int arr[6] = {5, 203, 5, 5, 203};
	int brr[6] = {-10, -10, -10, -10, -10, -10};
	int a = 6, b = 6;
	int c = run(arr, a, brr, b);
	for (a = 0; a < b; a++)
		printf(" %d ", brr[a]);
	printf("\n %d ", c);
	return 0;
}
int run(int moves[], int movesLen, int res[], int resLen)
{
	enum pos{Q0_pos = -4, Q1_pos, Q2_pos, Q3_pos} start_pos;
	enum State { INIT_STATE = -10, BREAK_STATE, POP_STATE, CONTINUE_STATE, REPEAT_STATE, STOP_STATE};
	enum State startState = INIT_STATE;
	enum State currentState = startState;
	start_pos = Q0_pos;
	enum pos current_pos = start_pos;
	int i, j = 0, g;
	int arr[4][4] = {5, POP_STATE, STOP_STATE, 551,
		STOP_STATE, POP_STATE, 552, REPEAT_STATE,
		CONTINUE_STATE, 555, STOP_STATE, 550,
		STOP_STATE, 553, BREAK_STATE, BREAK_STATE};
	int brr[4][4] = {Q0_pos, Q1_pos, 0, Q2_pos,
		0, Q2_pos, Q1_pos, Q2_pos,
		Q3_pos, Q3_pos, 0, Q1_pos,
		0, Q0_pos, 0, 0};
	for (i = 0; i < movesLen; i++)
	{
		currentState = startState;
		switch (moves[i])
		{
				case 5: g = 0; break;
				case 13: g = 1; break;
				case 23: g = 2; break;
				case 203: g = 3; break;
				default: g = 4; currentState = STOP_STATE; break;
        };
		if (g != 4 && arr[current_pos + 4][g] > 0)
		{
			res[j] = arr[current_pos + 4][g];
			j++;
		}
		else
			currentState = arr[current_pos + 4][g];
		if (currentState == STOP_STATE)
		{
			i = movesLen;
			int a = j;
			for (j = a; j < resLen; j++)
				res[j] = 0;
			return a;
		}
		if (currentState == POP_STATE && j != 0)
		{
			j--;
			res[j] = 0;
		}
		else if(currentState == POP_STATE && j == 0)
            res[j] = 0;
		if (currentState == REPEAT_STATE)
			i--;
		if (currentState == BREAK_STATE)
		{
			i = movesLen;
			int a = j;
			for (j = a; j < resLen; j++)
				res[j] = 0;
			return a;
		}
		if (j == resLen)
			i = movesLen;
		current_pos = brr[current_pos + 4][g];
	}
	int c = j;
	while (j++ < resLen)
	{
		res[j - 1] = 0;
	}
	return c;

}
