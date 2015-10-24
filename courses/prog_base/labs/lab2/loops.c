#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double calc(int n, int m)
{
    int i,j;
    double x, y;
    x=0;
    y=0;
    for (j=1; j<=m; j++)
        {
            y = cos( ( j * 3,14 ) / 2 ) + y;
        }
    for (i=1; i<=n; i++)
        {
            x = x + (1+i)*y;
        }
    return x;
}
