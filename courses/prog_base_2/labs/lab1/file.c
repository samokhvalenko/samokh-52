#include "dict.h"
#include "file.h"

struct file_s {
    char * word;
};

file_t * file_new( char * word)
{
    file_t * self = NULL;
    self = malloc(sizeof(struct file_s));
    if(self == NULL)
        return NULL;
    self->word = malloc(sizeof(char) * strlen(word));
    return self;
}

int add_file(char * word, dictionary_t * dict){
    file_t * file = file_new(word);
    char * text = malloc(sizeof(text_revork(word, dict)));
    strcpy(text, text_revork(word, dict));
    int cop_num = word_count(text, dict);
    file_free(file);
    return cop_num;
}

int file_free(file_t * self)
{
    free(self->word);
    free(self);
    return 0;
}
