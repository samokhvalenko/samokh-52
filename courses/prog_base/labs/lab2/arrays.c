#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

float meanValue(int arr[], int size);
void fillRand1(int arr[], int size);
int maxValue(int arr[], int size);

int main()
{
    int max;
    int size = 9;
    int arr[size];
    fillRand1(arr, size);
    maxValue(arr, size);
    printf("%i", max);
    return 0;
}

void fillRand1(int arr[], int size)
{
    int i;
    time_t t;
    srand((unsigned) time(&t));
    for(i=0; i<size; i++)
    {
        arr[i] = 1 + rand() % 99;
    }
}
int checkRand1(int arr[], int size)
{
    int i;
    int result=0;
    for(i=0; i<size; i++)
    {
        if( arr[i]<=99 && arr[i]>=1 )
            result++;
    }
    if( result==size)
        return 1;
    else
        return 0;
}
float meanValue(int arr[], int size)
{
    int i;
    float x, result=0;
    for(i=0; i<size; i++)
    {
        result=result + arr[1];
    }
    x=result/size;
    return x;
}
int maxValue(int arr[], int size)
{
    int i, max=arr[0];
    for(i=1; i<size; i++)
    {
        if ( max>arr[i])
            max=max;
        else
            max=arr[i];
    }
    return max;
}
//int meanIndex(int arr[], int size)
/*{
   meanValue(arr, size);
    #define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
    int i;
    for(i=0; i<size; i++)

}*/
