#include <math.h>

int satisfies(int a, int b, int c) {
   int result;
   #define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
   #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
   int modmin, sum2;
   double d;
   int e;
   int f;
   int g;
   int result1 = 0;
        if (a < 0) result1++;
        if (b < 0) result1++;
        if (c < 0) result1++;
    if (result1 == 3)
    {
    modmin = abs (min ( a, min ( b,c ) ) );
    sum2 = a + b + c - min( a, min ( b, c ) );
    d = ( log(modmin) / log(2) );
    e = (int) d;
    f = d - e;
    g = abs (sum2);
        if ( sum2 < 256 && modmin < 256 && f == 0 )
            {
                result = 1;
            }
        else if ( g < 16 || (g - modmin) < 16 )
            {
                result = 1;
            }
        else
        {
            result = 0;
        }
    }
    else if (result1 == 2 || result1 == 1 )
    {
        if ( result1 == 1 && min (a, min( b,c ) ) > 256)
        {
            result = 1;
        }
        else if ( result1 == 2 && 4*(a + b + c - max( a, max( b,c ) ) ) > 256 )
        {
            result = 1;
        }
        else
        {
            result = 0;
        }
    }
    else
        {
            if ( min ( a, min( b,c ) ) == 0 )
            {
                result = 0;
            }
            else if (max( a, max( b,c ) ) % min( a, min( b,c ) ) == 0 || (max( a, max( b,c ) ) == 0 && min( a, min( b,c ) ) != 0) )
            {
                result = 1;
            }
        }

   return result;

}
