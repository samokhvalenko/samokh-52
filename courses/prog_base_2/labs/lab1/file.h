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
int add_file(char * word, dictionary_t * dict);


#endif
