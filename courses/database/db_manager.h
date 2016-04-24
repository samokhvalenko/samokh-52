#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "worker.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

int db_insertWorker(db_t * self, worker_t * student);
worker_t * db_getWorkerById(db_t * self, int id);
void db_updateWorker(db_t * self, worker_t * student);
void db_deleteWorker(db_t * self, int id);

int db_countWorkers(db_t * self);

int db_getWorkerTask(db_t * self, int K, int P, worker_t * arr, int arrMax);

#endif // DB_MANAGER_H_INCLUDED
