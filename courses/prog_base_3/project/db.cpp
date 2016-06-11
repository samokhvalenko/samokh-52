#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "db.h"
#include "sqlite3.h"

struct db_s {
    sqlite3 * db;
};

db_t * db_new(const char * dbFile) {
    db_t * self = (db_t*)malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, & (self->db));
    std::cout << "\nReturn code db new: " << rc;
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void db_free(db_t * self) {
    int rc = sqlite3_close(self->db);
    printf("\nRC SQLITE3 CLOSE: %i\n", rc);
    free(self);
}

int db_insert_player(db_t * self, char * name, int score) {
    int newStudentId = -1;
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "INSERT INTO Players VALUES ( ?, ?);";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_text(stmt, 0, name, strlen(name), NULL);
    sqlite3_bind_int(stmt, 1, score);
    int rc = sqlite3_step(stmt);
    printf("\n THAT IS RC: %i\n", rc);
    if (SQLITE_OK == rc) {
        printf("ALL IS OK");
        exit(1);
    }
    if (SQLITE_ERROR == rc) {
        printf("can't select workers\n");
        exit(1);
    }
    sqlite3_finalize(stmt);
    return newStudentId;
}

std::string convert(char * data){
    return std::string(data);
}

void _fill_player(sqlite3_stmt * stmt, Player * player) {
    const unsigned char * name = sqlite3_column_text(stmt, 0);
    int score = sqlite3_column_int(stmt, 1);
    player->name = convert((char *)name);
    player->score = score;
    std::cout << "\nPlayer name: " << player->name;
    std::cout << "\nPlayer score: " << player->score;
}

int db_count_players(db_t * self) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM Players;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

void db_get_players(db_t * self, std::vector <Player *> *players) {

	int rc;
	const char * sqlQuery = "SELECT * FROM Players;";
    sqlite3_stmt * stmt = NULL;
    rc = sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery) + 1, &stmt, 0);
    std::cout << "\nReturn code sqlite3_prepare_v2: " << rc;
	for (int i = 0; i < db_count_players(self); i++)
	{
		Player * player = new Player("");
		rc = sqlite3_step(stmt);
		if (SQLITE_ERROR == rc) {
			printf("can't select workers\n");
			exit(1);
		} else if(rc == SQLITE_OK){
		    printf("\n RC: %i", rc);
            continue;
		}else{
			_fill_player(stmt, player);
            players->push_back(player);
		}

	}
	sqlite3_finalize(stmt);

}
