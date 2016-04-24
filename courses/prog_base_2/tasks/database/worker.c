#include <stdlib.h>
#include <stdio.h>

#include "worker.h"

void worker_print(worker_t * st) {
    printf("Name: %s\nSurname: %s\nBirthbate: %s\nCash: %i\nWork time: %i\n",
        st->name, st->surname, st->birthdate, st->cash, st->work_time);
}

void worker_printList(worker_t * arr, int len) {
    for (int i = 0; i < len; i++) {
        worker_print(&arr[i]);
        puts("");
    }
}
