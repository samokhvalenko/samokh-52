#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void copytoMat(int mat[4][4]);

void fillRand(int mat[4][4])
{
  int i, j;
  for(i=0; i<4; i++)
   {
    for(j=0; j<4; j++)
     {
      mat[i][j] = -999 + rand() % 1999;
     }
   }
}
void rotateCCW90(int mat[4][4])
{
int arr[4][4];
int matr[4][4];
int i, j;
for(i=0; i<4; i++)
   {
    for(j=0; j<4; j++)
     {
        matr[i][j]=mat[j][3-i];
     }
   }
copytoMat(arr);
}
void flipV(int mat[4][4])
{
int arr[4][4];
int matr[4][4];
int i, j;
for(i=0; i<4; i++)
   {
    for(j=0; j<4; j++)
     {
         matr[i][j]=mat[3-i][j];
     }
   }
copytoMat(arr);
}
void transposSide(int mat[4][4])
{
int arr[4][4];
int matr[4][4];
int i, j;
for(i=0; i<4; i++)
   {
    for(j=0; j<4; j++)
     {
        matr[i][j]=mat[3-j][3-i];
     }
   }
copytoMat(arr);
}
void copytoMat(int mat[4][4])
{
  int matr[4][4];
  int i, j;
  for(i=0; i<4; i++)
   {
    for(j=0; j<4; j++)
        mat[i][j]=matr[i][j];
   }
}
