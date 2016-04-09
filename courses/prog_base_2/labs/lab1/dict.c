#include "dict.h"
#include <string.h>

struct couple{
    int num_of_words;
    char * word;
    struct couple * next;
};
struct dictionary_s {
    struct couple * couples;
    int num_of_couples;
};


d_status status = D_OK;

d_status get_status(int func){
    switch (func){
case 1:
    return D_OK;
case 0:
    return D_NULL;
case -2:
    return D_EMPTY_WORD;
case -3:
    return D_EMPTY_DICT;
}
}

dictionary_t * dictionary_new()
{
    dictionary_t * self = NULL;
    self = malloc(sizeof(struct dictionary_s));
    if (NULL == self){
        status = D_NULL;
        return NULL;
    }
    self->couples = malloc(sizeof(struct couple));
    self->couples->next = NULL;
    self->num_of_couples = 0;
    status = D_OK;
    return self;
}

char * dictionary_text_revork( char * new_word, dictionary_t * self){
    if(!strcmp(new_word, "")){
        status = D_EMPTY_WORD;
        return (char*)status;
    }
    int i, j, count = 0;
    int flag = 0;
    j = 0;
    for(i = 0; i < strlen(new_word);i++){
        if((new_word[i] >= 'a' && new_word[i] <= 'z') || (new_word[i] >= 'A' && new_word[i] <= 'Z'))
            count++;
    }
    char reworked_word[30];
    for(i = 0; i < strlen(new_word);i++)
    {
        while((new_word[i] >= 'a' && new_word[i] <= 'z') || (new_word[i] >= 'A' && new_word[i] <= 'Z')){
            reworked_word[j] = new_word[i];
            j++;
            i++;
            flag = 0;
        }
        if(flag == 0)
            if(!(new_word[i] >= 'a' && new_word[i] <= 'z') || (new_word[i] >= 'A' && new_word[i] <= 'Z')){
                reworked_word[j] = ' ';
                j++;
                flag = 1;
            }
    }
    reworked_word[j] = '\0';
    for(i = 0; reworked_word[i] != '\0'; i++){
        new_word[i] = reworked_word[i];
    }
    new_word[i-1] = '\0';
    status = D_OK;
    return new_word;
}

int dictionary_word_count( char * buffer, dictionary_t * self){
   char *words_arr[35], *pov[35];
   char *text;
   int amount_of_words = 0, j, k, words_in_coup, pov_count[35], unic_words_count = 0, d, f; // j, k, f just for cycle

   text = strtok(buffer," ");

   while ( text != NULL) {
      words_arr[amount_of_words] = text;
      text = strtok (NULL, " ");
      amount_of_words++;
   }

   for(j = 0; j < amount_of_words; j++) {
      words_in_coup = 0;
      f = 0;
      for(k = 0; k < amount_of_words; k++) {
         if (strcmp(words_arr[j], words_arr[k]) == 0) {
            words_in_coup++;
         }
      }
      for(d = 0; d < unic_words_count; d++) {
         if (strcmp(words_arr[j], pov[d]) == 0) {
            f++;
         }
      }
      if(words_in_coup > 0 && f == 0) {
         pov[unic_words_count] = words_arr[j];
         pov_count[unic_words_count] = words_in_coup;
         unic_words_count++;
      }
   }
   struct couple * tmp;
   for(j = 0; j < unic_words_count; j++) {
      tmp = malloc(sizeof(struct couple));
      tmp->word = malloc(sizeof(char *)* strlen(pov[j]));
      tmp->next = self->couples;
      self->couples = tmp;
      strcpy(tmp->word, pov[j]);
      tmp->num_of_words = pov_count[j];
      self->num_of_couples++;
   }
   if(self->num_of_couples == 0){
        status = D_EMPTY_DICT;
        return status;
   }
   status = D_OK;
   return self->num_of_couples;
}

void dictionary_print(dictionary_t * self){
    struct couple * tmp = self->couples;
    printf("\n%i\n", self->num_of_couples);
    for(int i = 0; i < self->num_of_couples; i++){
        printf("Word: %s\n", tmp->word);
        printf("Amount of words: %i\n", tmp->num_of_words);
        if(tmp != NULL)
            tmp = tmp->next;
    }
}

void dictionary_free(dictionary_t * self)
{
    free(self);
    free(self->couples);
    struct couple * tmp = self->couples;
    while( tmp->next != NULL){
        free(tmp->word);
        tmp = tmp->next;
    }
}
