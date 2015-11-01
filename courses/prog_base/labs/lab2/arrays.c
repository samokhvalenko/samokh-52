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
    max=checkRand1(arr, size);
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
        result=result + arr[i];
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
int meanIndex(int arr[], int size)
{
    int i;
    float mean, meanval;
    mean=meanValue(arr, size);
    meanval=mean-arr[0];
    for(i=1; i<size; i++)
    {
        if(meanval<mean-arr[i])
            meanval=meanval;
        else
            meanval=mean-arr[i];
    }
    return ;
}
int maxIndex(int arr[], int size)
{

}
int maxOccurance(int arr[], int size)
{

}
int diff(int arr1[], int arr2[], int res[], int size)
{
    int i,j,z,result;
    for(i=0;i<size;i++)
        for(j=0;j<size;j++)
            for(z=0;z<size;z++)
            {
                res[z]=arr1[i]-arr2[j];
                if(res[z]=0)
                    result++;
                else
                    return 0;
            }
    if(result=size)
        return 1;
}









