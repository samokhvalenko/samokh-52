#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arraydz.h"
#include "time.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void new_void_size_eq_five( void **state){

    list_t * list = list_new(5);
    assert_int_equal(list_length(list), 5);
    list_remove(&list);
}

static void new_int_add_elem_five_on_first_pos( void **state){

    list_t * list = list_new(2);
    assert_int_equal(list_add(list, 1, 5), 5);// returns elem if adding was successful
    list_remove(&list);
}

static void new_int_del_elem_on_first_pos( void **state){
    list_t * list = list_new(2);
    list_add(list, 1, 5);
    assert_int_equal(list_del(list, 1), 0);// returns 0 if deleting was successful
    list_remove(&list);
}

static void new_int_list_with_all_posit_elements( void **state){
    list_t * list = list_new(5);
    list_random(list, 10, 1);
    //list_print(list);
    assert_int_equal(list_count_pos(list), 5);
    list_remove(&list);
}

static void new_int_list_with_no_posit_elements( void **state){
    list_t * list = list_new(5);
    list_random(list, 10, -20);
    //list_print(list);
    assert_int_equal(list_count_pos(list), 0);
    list_remove(&list);
}

static void new_int_list_with_all_negative_elements( void **state){
    list_t * list = list_new(5);
    list_random(list, 100, -200);
    //list_print(list);
    assert_int_equal(list_count_neg(list), 5);
    list_remove(&list);
}

static void new_int_list_with_no_negative_elements( void **state){
    list_t * list = list_new(5);
    list_random(list, 10, 2);
    //list_print(list);
    assert_int_equal(list_count_neg(list), 0);
    list_remove(&list);
}

static void new_int_list_with_all_zero_elements( void **state){
    list_t * list = list_new(5);
    list_random(list, 1, 0);
    //list_print(list);
    assert_int_equal(list_count_null(list), 5);
    list_remove(&list);
}

static void new_int_list_with_no_zero_elements( void **state){
    list_t * list = list_new(5);
    list_random(list, 10, 1);
    //list_print(list);
    assert_int_equal(list_count_null(list), 0);
    list_remove(&list);
}

int main(void){

    srand(time(NULL));
    const UnitTest tests[] = {
        unit_test(new_void_size_eq_five),
        unit_test(new_int_add_elem_five_on_first_pos),
        unit_test(new_int_del_elem_on_first_pos),
        unit_test(new_int_list_with_all_posit_elements),
        unit_test(new_int_list_with_no_posit_elements),
        unit_test(new_int_list_with_all_negative_elements),
        unit_test(new_int_list_with_no_negative_elements),
        unit_test(new_int_list_with_all_zero_elements),
        unit_test(new_int_list_with_no_zero_elements),
    };
    return run_tests(tests);

}
