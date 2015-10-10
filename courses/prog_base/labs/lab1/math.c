#include <math.h>

double calc(double x, double y, double z) {
    double a;
    if (x-y <= 0 || x < 0 || x+y == 0 || (cos(y)/sin(x)+1) == 0 )
    {
        return NAN;
    }
    else
    {
        a = pow(x, y + 1) / pow(x - y, 1 / z) + y / ( 4 * (x + y)) + (sqrt(fabs(cos(y)/sin(x))+1) );
    }
return a;

}
