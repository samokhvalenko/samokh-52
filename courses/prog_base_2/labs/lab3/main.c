#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <setjmp.h>

#include <cmocka.h>
#include "automata.h"
#include "user.h"

int main()
{
    srand(time(NULL));
    game_auto_t au = game_auto_new();
    player_t pl = user_new_player("Stas");
    press_t pr = user_new_press("Press");
    administration_t ad = user_new_admin("Adminka");
    game_auto_sub_win(au, pl, user_get_cb_alm_win(pl));
    automata_sub_win(au, pl, user_get_cb_win(pl));
    automata_sub_jackpot(au, pl, user_get_cb_jackpot_player(pl));
    automata_sub_jackpot(au, pr, user_get_cb_jackpot_press(pr));
    automata_sub_jackpot(au, ad, user_get_cb_jackpot_admin(ad));
    while(1)
    {
        automata_run(au);
        Sleep(1000);
    }
    automata_free(au);
    user_free_admin(ad);
    user_free_player(pl);
    user_free_press(pr);
    return 0;
}


/*static void new_cb_user_jackpot(void **state){
    game_auto_t sender = game_auto_new();
    player_t sb = user_new_player("Stas");
    assert_int_equal(user_jack_player_react(sender, sb), jackpot);
    user_free_player(sb);
    automata_free(sender);
}
static void new_cb_user_win(void **state){
    game_auto_t sender = game_auto_new();
    player_t sb = user_new_player("Stas");
    assert_int_equal(user_win_player_react(sender, sb), win);
    user_free_player(sb);
    automata_free(sender);
}
static void new_cb_user_near_to_win(void **state){
    game_auto_t sender = game_auto_new();
    player_t sb = user_new_player("Stas");
    assert_int_equal(user_near_win_player_react(sender, sb), near_to_win);
    user_free_player(sb);
    automata_free(sender);
}
int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_cb_user_jackpot),
        cmocka_unit_test(new_cb_user_win),
        cmocka_unit_test(new_cb_user_near_to_win),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}*/
