#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "text.h"
int main()
{
    char *stop_words[32] = {"i", "a", "about", "an", "are", "as", "at", "be", "by", "com", "for", "from", "how", "in",
     "is", "it", "of", "or", "on", "that", "the", "this", "to", "was", "what", "when", "where", "who",
      "will", "with", "the", "www"};
    char str[20] = "text.txt";
    text_t * text = text_new(str);
    sentense_t * tmp = NULL;
    for (int i = 0; i < text_sentence_count(text); i++)
    {
        tmp = text_get_sentence(text, i);
        for (int j = 0; j < sentence_word_count(tmp); j++)
        {
            for( int k = 0; k < 32; k++){
                if(strcmp(get_word(sentence_get_word(tmp, j)), stop_words[k]) == 0 || strlen(get_word(sentence_get_word(tmp, j))) < 4){
                    sentence_del_word(tmp, j);
                    j--;
                    break;
                }
            }
        }
    }

    FILE * file_out = NULL;
    file_out = fopen("out.txt", "w");
    if (file_out == NULL)
        return 1;

    for (int i = 0; i < text_sentence_count(text); i++)
    {
        tmp = text_get_sentence(text, i);
        for (int j = 0; j < sentence_word_count(tmp); j++)
        {
            if (j < sentence_word_count(tmp) - 1)
                fprintf(file_out, "%s\n", get_word(sentence_get_word(tmp, j)));
        }
    }
    text_print(text);
    text_free(text);
    fclose(file_out);

    return 0;
}
