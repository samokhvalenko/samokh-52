#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
    int i,j;
    int n=1;
    int m=2;
    double x, y, z;
    x=0;
    y=0;
    z=0;
    for (j=1; j<=m; j++)
    {
        y = cos( ( j * 3,14 ) / 2 ) + y;

    }
    for (i=1; i<=n; i++)
        {
            x = z + (1+i)*y;
            z=x;
        }
    printf("%lf", y);
    return 0;
}
