#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int c,h,i,j,size,size1;
    size=14;
    size1=15;
    char arr[]="Hel4lo3w2ord";
    char brr[]="He5llo1wo4rd1";
    for(i=0;i<size;i++)
        {
        if((arr[i]>='a' && arr[i]<='z') || (arr[i]>='A' && arr[i]<='Z'))
            {
                arr[i]=arr[i];
            }
        else
           {
                for(h=i;h<size-1;h++)
                    arr[h]=arr[h+1];
           }

        }
     for(j=0;j<size1;j++)
        {
            if((brr[j]>='a' && brr[j]<='z') || (brr[j]>='A' && brr[j]<='Z'))
            {
                brr[j]=brr[j];
            }
            else
            {
                for(c=j;c<size1-1;c++)
                    brr[c]=brr[c+1];
            }
        }
    for(i=0;i<size;i++)
        printf("%c", arr[i]);
    for(j=0;j<size1;j++)
        printf("%c", brr[j]);
    strcmp(arr, brr);
}
