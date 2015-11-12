#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* список слов и их значений */
char  *dic[][40] = {
  "a", "b",
  "c", "D",
  "E", "F",
  "G", "H",
  "", ""  /* нули, завершающие список */
};

int main(void)
{
  char word[80], ch;
  char **p;

  do {
    puts("vved: ");
    scanf("%s", word);

    p = (char **)dic;

    /* поиск слова в словаре и вывод его значения */
    do {
      if(!strcmp(*p, word)) {
        puts("val:");
        puts(*(p+1));
        break;
      }
      if(!strcmp(*p, word)) break;
      p = p + 2;  /* продвижение по списку */
    } while(*p);
    if(!*p) puts("sl v clvnk no");
    printf("will you? (y/n): ");
    scanf(" %c%*c", &ch);
  } while(toupper(ch) != 'N');

  return 0;
}
