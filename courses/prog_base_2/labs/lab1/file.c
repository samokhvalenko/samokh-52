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

int file_add(char * word, file_t * file){
    dictionary_t * dict = dictionary_new();
    char * text = malloc(sizeof(dictionary_text_revork(word, dict)));
    strcpy(text, dictionary_text_revork(word, dict));
    int cop_num = dictionary_word_count(text, dict);
    dictionary_free(dict);
    return cop_num;
}

char * file_get_word(file_t * file){
    return file->word;
}

int file_free(file_t * self)
{
    free(self->word);
    free(self);
    return 0;
}
