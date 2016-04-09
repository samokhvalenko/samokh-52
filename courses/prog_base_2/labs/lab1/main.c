#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "dict.h"
#include "file.h"

static void new_file_add(void **state){
    dictionary_t * dict = dictionary_new();
    char word[30] = {"^7*gh&^vb^$#nm&*vb&8"};
    assert_int_equal(add_file(word, dict), 3);
    dictionary_free(dict);
}

static void new_more_krakozyabra_file_add(void **state){
    dictionary_t * dict = dictionary_new();
    char word[70] = {"^%^7    *first&^fifth$%^&*second^$##$%^&*third&*fourth  ^  &*&8  "};
    assert_int_equal(add_file(word, dict), 5);
    dictionary_free(dict);
}

static void new_three_words_dict( void **state){
    dictionary_t * dict = dictionary_new();
    char word[10] = {" gh bn jk"};
    assert_int_equal(word_count(word, dict), 3);
    dictionary_free(dict);
}

static void new_three_double_words_dict( void **state){
    dictionary_t * dict = dictionary_new();
    char word[25] = {" gh bn bn jk gh bn jk "};
    assert_int_equal(word_count(word, dict), 3);
    dictionary_free(dict);
}

static void new_word_reworking( void **state){
    dictionary_t * self = dictionary_new();
    char word[20] = {"*&gh63gv25cv56"};
    assert_string_equal(text_revork(word, self), " gh gv cv");
    dictionary_free(self);
}

static void new_word_more_spaces_reworking( void **state){
    dictionary_t * self = dictionary_new();
    char word[25] = {"*&gh63gv25cv56          "};
    assert_string_equal(text_revork(word, self), " gh gv cv");
    dictionary_free(self);
}

static void new_one_word_reworking( void **state){
    dictionary_t * self = dictionary_new();
    char word[20] = {"ghgvcv"};
    assert_string_equal(text_revork(word, self), "ghgvcv");
    dictionary_free(self);
}

static void new_without_word_text_reworking( void **state){
    dictionary_t * self = dictionary_new();
    char word[20] = {"$%632565"};
    assert_string_equal(text_revork(word, self), "");
    dictionary_free(self);
}

int main(void){

    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_three_words_dict),
        cmocka_unit_test(new_word_reworking),
        cmocka_unit_test(new_file_add),
        cmocka_unit_test(new_without_word_text_reworking),
        cmocka_unit_test(new_three_double_words_dict),
        cmocka_unit_test(new_one_word_reworking),
        cmocka_unit_test(new_word_more_spaces_reworking),
        cmocka_unit_test(new_more_krakozyabra_file_add),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
