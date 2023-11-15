#include "../sql/sqlite3.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

int main(void) {

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("sql/test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char navn[40];
    printf("Indtast navn: ");
    fgets(navn, 40, stdin);
    navn[strcspn(navn, "\n")] = 0;

    char sql[200];
    sprintf(sql, "INSERT INTO patients VALUES (1234176831, '%s', 'Cocaine', 69, 'Dagligt')", navn);

    rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);

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