#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* ������ ���� � �� �������� */
char  *dic[][40] = {
  "a", "b",
  "c", "D",
  "E", "F",
  "G", "H",
  "", ""  /* ����, ����������� ������ */
};

int main(void)
{
  char word[80], ch;
  char **p;

  do {
    puts("vved: ");
    scanf("%s", word);

    p = (char **)dic;

    /* ����� ����� � ������� � ����� ��� �������� */
    do {
      if(!strcmp(*p, word)) {
        puts("val:");
        puts(*(p+1));
        break;
      }
      if(!strcmp(*p, word)) break;
      p = p + 2;  /* ����������� �� ������ */
    } while(*p);
    if(!*p) puts("sl v clvnk no");
    printf("will you? (y/n): ");
    scanf(" %c%*c", &ch);
  } while(toupper(ch) != 'N');

  return 0;
}
