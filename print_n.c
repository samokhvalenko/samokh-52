#include "Printer.h"

#include "thread.h"
#include "mutex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

static mutex_t* printer_num;
static thread_t* last_active_thread;
static thread_t* curr_thread_free;

struct  NumPrinter {
  int msg;
  thread_t* thread;
};

void CONSTR(mutex_t * print_mut){
    printer_num = print_mut;
    last_active_thread = thread_getCurrentThread();
    curr_thread_free = last_active_thread;
}

void DESTR(){
    mutex_free(printer_num);
    thread_free(curr_thread_free);
}

NumPrinter* num_pr_new(int msg){
    NumPrinter* self = malloc(sizeof(NumPrinter));
    self->msg = msg;
    self->thread = NULL;
    return self;
}

void printer_free(NumPrinter* p){
      mutex_lock(printer_num);
      if(p->thread != NULL){
        thread_terminate(p->thread);
        thread_free(p->thread);
      }
      mutex_unlock(printer_num);

      free(p);
}

static void* printer_loop(void* printer){
      NumPrinter* p = printer;

    while(1) {
        mutex_lock(printer_num);

        if(thread_equals(last_active_thread, p->thread)){
            mutex_unlock(printer_num);
            continue;
        }

        for(size_t i =  0; i < 3; i++){
            printf("%i\n", p->msg);
        }
        last_active_thread = p->thread;

        mutex_unlock(printer_num);
    }
    assert(0);
    return NULL;
}

void printStart(NumPrinter* p){
    thread_t* new_thread;
    mutex_lock(printer_num);
    new_thread = thread_create_args(printer_loop, p);
    p->thread = new_thread;
    mutex_unlock(printer_num);
}
