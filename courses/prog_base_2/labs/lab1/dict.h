#ifndef AUD_H_INCLUDED
#define AUD_H_INCLUDED


typedef enum d_status {D_OK = 1, D_NULL = 0, D_ERROR_OPERATION = -1, D_EMPTY_WORD = -2,D_EMPTY_DICT = -3} d_status;
typedef struct dictionary_s dictionary_t;

dictionary_t * dictionary_new();

void dictionary_print(dictionary_t * self);
int dictionary_word_count( char * text, dictionary_t * self);
char * dictionary_text_revork( char * new_word, dictionary_t * self);
void dictionary_free(dictionary_t * self);
d_status get_status(int func);


#endif // AUD_H_INCLUDED
