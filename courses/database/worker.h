#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

typedef struct worker_s {
    int id;
    char name[256];
    char surname[256];
    char birthdate[256];
    int cash;
    int work_time;
} worker_t;

void worker_print(worker_t * st);
void worker_printList(worker_t * arr, int len);

#endif // STUDENT_H_INCLUDED
