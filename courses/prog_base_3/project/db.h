#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "roads.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);
int db_insert_player(db_t * self, char * name, int score);
void db_get_players(db_t * self, std::vector <Player *> *players);

#endif // DB_H_INCLUDED
