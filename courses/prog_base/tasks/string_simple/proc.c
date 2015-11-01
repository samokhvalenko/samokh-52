#include <stdio.h>
#include <string.h>
#include <math.h>

char * process(char * resultStr, const char * text[], int linesNum, const char * extraStr)
{
	const char * textLines;
	int flag = 1;
	int c;
	int i, j, err, wordNumber = 0, wordLen = 0;
	for (i = 0; i < linesNum; i++)
	{
		wordNumber = 0;
		err = 0;
		textLines = text[i];
		for(j = 0;textLines[j] != '\0';j++)
		{
			if(textLines[j] == ' ')
			{
				err = (wordLen > 4)?1:0;
				wordNumber++;
				wordLen = 0;
			}
			else
				wordLen++;
		}
		if  (wordNumber > 5 && err == 0)
		{
			j = 0;
			while (j <= (log10((double) wordNumber) - 1))
			{
				j++;
			}
			i = linesNum;
			resultStr[j + 1] = ' ';
			resultStr[j + 2] = '\0';
			while (j >= 0)
			{
				resultStr[j] = wordNumber % 10 + 48;
				wordNumber /= 10;
				j--;
			}
			c = strlen ( resultStr );
			for(j = 0; extraStr [j] != ' '; j++ )
			{
				resultStr[c++] = extraStr[j];
			}
			resultStr[c] = '\0';

		}
	}
	if (err == 1)
	{
	    resultStr[0] = '\0';
		strcat(resultStr, "NULL");
	}
		return resultStr;
}