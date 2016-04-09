#ifndef KORPUS_H_INCLUDED
#define KORPUS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "dict.h"

typedef struct file_s file_t;
file_t * file_new(char * word);
int file_free(file_t * self);
int file_add(char * word, file_t * file);
char * file_get_word(file_t * file);


#endif
