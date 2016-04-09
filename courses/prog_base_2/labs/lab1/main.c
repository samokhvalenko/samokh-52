#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "dict.h"
#include "file.h"

static void file_add_3_words(void **state){
    char word[30] = {"^7*gh&^vb^$#nm&*vb&8"};
    file_t * file = file_new(word);
    assert_int_equal(file_add(word, file), 3);
    file_free(file);
}

static void file_add_5_couples_of_words(void **state){
    char word[70] = {"^%^7    *first&^fifth$%^&*second^$##$%^&*third&*fourth  ^  &*&8  "};
    file_t * file = file_new(word);
    assert_int_equal(file_add(word, file), 5);
    file_free(file);
}

static void dictionary_word_count_3_words( void **state){
    char word[10] = {" gh bn jk"};
    dictionary_t * dict = dictionary_new();
    assert_int_equal(dictionary_word_count(word, dict), 3);
    dictionary_free(dict);
}

static void dictionary_word_count_3_couples( void **state){
    char word[25] = {" gh bn bn jk gh bn jk "};
    dictionary_t * dict = dictionary_new();
    assert_int_equal(dictionary_word_count(word, dict), 3);
    dictionary_free(dict);
}

static void dict_text_rework_3word_string( void **state){
    char word[20] = {"*&gh63gv25cv56"};
    dictionary_t * dict = dictionary_new();
    assert_string_equal(dictionary_text_revork(word, dict), " gh gv cv");
    dictionary_free(dict);
}

static void dict_text_rework_morespaces_3words( void **state){
    char word[25] = {"*&gh63gv25cv56          "};
    dictionary_t * dict = dictionary_new();
    assert_string_equal(dictionary_text_revork(word, dict), " gh gv cv");
    dictionary_free(dict);
}

static void dict_text_rework_one_word_string( void **state){
    char word[20] = {"ghgvcv"};
    dictionary_t * dict = dictionary_new();
    assert_string_equal(dictionary_text_revork(word, dict), "ghgvcv");
    dictionary_free(dict);
}

static void dict_text_rework_no_words( void **state){
    char word[20] = {"$%632565"};
    dictionary_t * dict = dictionary_new();
    assert_string_equal(dictionary_text_revork(word, dict), "");
    dictionary_free(dict);
}

static void dict_text_rework_empty_string(void **state){
    char word[2] = {""};
    dictionary_t * dict = dictionary_new();
    assert_int_equal(get_status(dictionary_text_revork(word, dict)), D_EMPTY_WORD);
    dictionary_free(dict);
}

static void dict_word_count_empty_string(void **state){
    char word[2] = {""};
    dictionary_t * dict = dictionary_new();
    assert_int_equal(dictionary_word_count(word, dict), D_EMPTY_DICT);
    dictionary_free(dict);
}

int main(void){

    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(dictionary_word_count_3_words),
        cmocka_unit_test(dict_text_rework_3word_string),
        cmocka_unit_test(file_add_3_words),
        cmocka_unit_test(dict_text_rework_no_words),
        cmocka_unit_test(dictionary_word_count_3_couples),
        cmocka_unit_test(dict_text_rework_one_word_string),
        cmocka_unit_test(dict_text_rework_morespaces_3words),
        cmocka_unit_test(file_add_5_couples_of_words),
        cmocka_unit_test(dict_text_rework_empty_string),
        cmocka_unit_test(dict_word_count_empty_string),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
