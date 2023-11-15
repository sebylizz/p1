#include "../sql/sqlite3.h"
#include "output.h"
#include <stdio.h>

int main(void) {

    //SQL BOILERPLATER HERUNDER
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("sql/test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "SELECT * FROM patients ORDER BY name"; //SQL example query

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}

//SQL print funktion
int callback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;

    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i]);
    }

    printf("\n");

    return 0;
}