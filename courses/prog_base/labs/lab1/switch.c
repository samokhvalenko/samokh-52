#include <math.h>

int exec(int op, int a, int b) {
  int result;
  #define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
   #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
   int c;
   int PI;
   PI = 3.14;
    c = abs(b) % 8;
   if (op < 0)
    {
        int d;
        d=a;
        a=b;
        b=d;
        op=-op;
    }

        switch ( abs(op) )
        {
        case 0:
            result = - a;
            break;
        case 1:
            result = a + b;
            break;
        case 2:
            result = a - b;
            break;
        case 3:
            result = a * b;
            break;
        case 4:
            result = a / b;
            break;
        case 5:
            result = abs (a);
            break;
        case 6:
            result = pow ( a, b);
            break;
        case 7:
        case 13:
        case 77:
            result = a % b;
            break;
        case 8:
            result = max ( a, b);
            break;
        case 9:
            result = min ( a, b);
            break;
        case 10:
            switch (c)
                    {
                    case 0:
                         result = abs(a) * sizeof(char);
                         break;
                    case 1:
                         result = abs(a) * sizeof(signed char);
                         break;
                    case 2:
                         result = abs(a) * sizeof(short);
                         break;
                    case 3:
                         result = abs(a) * sizeof(unsigned int);
                         break;
                    case 4:
                         result = abs(a) * sizeof(long);
                         break;
                    case 5:
                         result = abs(a) * sizeof(unsigned long long);
                         break;
                    case 6:
                         result = abs(a) * sizeof(float);
                         break;
                    case 7:
                         result = abs(a) * sizeof(double);
                         break;
                    }
        case 11:
            result = PI * ((a + b) % 6) / b;
            break;
        default:
            if ( op < 100)
                {
                    result = (abs(op) % abs(a+1)) + (abs(op) % abs( b + 1));
                }
            else if ( op>= 100 )
                {
                    result = -1;
                }
                break;
            }
  return result;
