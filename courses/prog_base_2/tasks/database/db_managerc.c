#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sqlite3.h>
#include "db_manager.h"
#include "worker.h"

struct db_s {
    sqlite3 * db;
};
static void _fillWorker(sqlite3_stmt * stmt, worker_t * st) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    const unsigned char * birthdate = sqlite3_column_text(stmt, 3);
    int cash = sqlite3_column_int(stmt, 4);
    int wt = sqlite3_column_int(stmt, 5);
    st->id = id;
    //if(name == NULL)
    puts("done");
    strcpy(st->name, (const char *)name);
    puts("done");
    strcpy(st->surname, (const char *)surname);
    puts("done");
    strcpy(st->birthdate, (const char *)birthdate);
    puts("done");
    st->cash = cash;
    st->work_time = wt;
}


db_t * db_new(const char * dbFile) {
    db_t * self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, & (self->db));
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void db_free(db_t * self) {
    sqlite3_close(self->db);
    free(self);
}

int db_insertWorker(db_t * self, worker_t * worker) {
    int newStudentId = -1;
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "INSERT INTO Worker_tab VALUES (null, ?, ?, ?, ?, ?);";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_text(stmt, 1, worker->name, strlen(worker->name), NULL);
    sqlite3_bind_text(stmt, 2, worker->surname, strlen(worker->surname), NULL);
    sqlite3_bind_text(stmt, 3, worker->birthdate, strlen(worker->birthdate), NULL);
    sqlite3_bind_int(stmt, 4, worker->cash);
    sqlite3_bind_int(stmt, 5, worker->work_time);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select workers\n");
        exit(1);
    }
    return newStudentId;
}

worker_t * db_getWorkerById(db_t * self, int id) {
    worker_t * worker = malloc(sizeof(struct worker_s));
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Worker_tab WHERE Id == ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select workers\n");
        exit(1);
    } else
        _fillWorker(stmt, worker);
    return worker;
}

void db_updateWorker(db_t * self, worker_t * workers) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "UPDATE Worker_tab SET Name = ?, Surname = ?, Birthdate = ?, Cash = ?, Work_time = ? WHERE Id == ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_text(stmt, 1, workers->name, strlen(workers->name), NULL);
    sqlite3_bind_text(stmt, 2, workers->surname, strlen(workers->surname), NULL);
    sqlite3_bind_text(stmt, 3, workers->birthdate, strlen(workers->birthdate), NULL);
    sqlite3_bind_int(stmt, 4, workers->cash);
    sqlite3_bind_int(stmt, 5, workers->work_time);
    sqlite3_bind_int(stmt, 6, workers->id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select workers\n");
        exit(1);
    }
}

void db_deleteWorker(db_t * self, int id) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "DELETE FROM Worker_tab WHERE Id == ?";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select workers\n");
        exit(1);
    }
}

int db_countWorkers(db_t * self) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM Worker_tab;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}


int db_getStudentsTask(db_t * self, int K, int P, worker_t * arr, int arrMax) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Worker_tab WHERE Cash > ? AND Work_time > ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, K);
    sqlite3_bind_int(stmt, 2, P);
    int count = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select workers\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            _fillWorker(stmt, &arr[count]);
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;
}
