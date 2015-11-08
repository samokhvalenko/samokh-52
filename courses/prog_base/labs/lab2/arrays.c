#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

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
    for(i=0; i<size; i++)
    {
        if (arr[i] > max)
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
    int i;
    int max = maxValue(arr, size);
    for (i = 0; i < size; i++)
		if (arr[i] == max)
			return i;
}
int maxOccurance(int arr[], int size)
{
	int i ,j;
	int q = 1, p = 1;
	int max = arr[0];
	for (i = 0; i < size; i++){
		for (j = i + 1; j < size; j++)
			if (arr[j] == arr[i])
				p++;
		if (p >= q)
		{
			q = p;
			max = arr[i];
		}
		if(p == q && arr[i] > max)
			max = arr[i];

		p = 1;
	}
	return max;
}
int diff(int arr1[], int arr2[], int res[], int size)
{
    int i,result;
    for(i=0;i<size;i++)
        {
            res[i]=arr1[i]-arr2[i];
            if(res[i]=0)
                result++;
            else
                return 0;
            }
    if(result=size)
        return 1;
}
void _div(int arr1[], int arr2[], int res[], int size)
{
    int i,j,z;
    for(i=0;i<size;i++)
        {
            res[i]=arr1[i]/arr2[i];
        }
}
int lteq(int arr1[], int arr2[], int size)
{
    int i;
	for (i = 0; i < size; i++)
		if (arr1[i] > arr2[i])
			return 0;
	return 1;
}
void lor(int arr1[], int arr2[], int res[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		res[i] = arr1[i] || arr2[i];
}








