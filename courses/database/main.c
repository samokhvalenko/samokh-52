#include <stdio.h>
#include <stdlib.h>

#include "db_manager.h"
#include "worker.h"

int main(void) {
    const char * dbFile = "worker.db";
    worker_t studentList[100];
    db_t * db = db_new(dbFile);

    int countWorkers = db_countWorkers(db);
    printf("Workers total: %i\n\n", countWorkers);
    int filterCash = 10;
    int filterWork_time = 1;
    int count = db_getStudentsTask(db, filterCash, filterWork_time, studentList, 100);
    printf("Workers with cash > %i and worked time > %i: %i\n\n", filterCash, filterWork_time, count);
    worker_printList(studentList, count);

    worker_t * worker = db_getWorkerById(db, 3);
    if (worker->id != 3)
        puts("fail");
    worker->cash = 1000;
    strcpy(worker->name, "Kek");
    db_updateWorker(db, worker);
    db_deleteWorker(db, 6);
    db_updateWorker(db, worker);
    //db_insertWorker(db, worker);
    db_free(db);
    return 0;
}
