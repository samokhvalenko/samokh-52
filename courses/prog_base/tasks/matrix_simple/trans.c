#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void fillRand(int mat[4][4])
{
  int i, j;
  time_t t;
  srand((unsigned) time(&t));
  for(i=0; i<4; i++)
   {
    for(j=0; j<4; j++)
     {
      mat[i][j] = -999 + rand() % 1999;
     }
   }
}
void rotateCCW90(int mat[4][4], int matr[4][4])
{
int i, j;
for(i=0; i<4; i++)
   {
    for(j=0; j<4; j++)
     {
        matr[i][j]=mat[j][3-i];
     }
   }
}
void flipV(int mat[4][4], int matr[4][4])
{
int i, j;
for(i=0; i<4; i++)
   {
    for(j=0; j<4; j++)
     {
         matr[i][j]=mat[3-i][j];
     }
   }
}
void transposSide(int mat[4][4], int matr[4][4])
{
int i, j;
for(i=0; i<4; i++)
   {
    for(j=0; j<4; j++)
     {
        matr[i][j]=mat[3-j][3-i];
     }
   }
}
