#ifndef AUD_H_INCLUDED
#define AUD_H_INCLUDED


typedef struct dictionary_s dictionary_t;

dictionary_t * dictionary_new();

void dictionary_print(dictionary_t * self);
int dictionary_word_count( char * text, dictionary_t * self);
char * dictionary_text_revork( char * new_word, dictionary_t * self);
void dictionary_free(dictionary_t * self);


#endif // AUD_H_INCLUDED
