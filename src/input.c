#include "../sql/sqlite3.h"
#include "input.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

person cur;
recept *recepts = NULL;
int antalrecepts;

int main(void) {

    int cpr = load_patient();

    printf("Skriv r for at se aktuelle recepter\n");

    char r;
    scanf(" %c", &r);
    if(r == 'r'){
        int i = 0;
        for(int i = 0; i < antalrecepts; i++){
            printf("%ld, %i, %i, %i\n", recepts[i].cpr, recepts[i].id, recepts[i].dosage, recepts[i].frequency);
        }
    }

    return 0;
}

int load_patient() {

    long cpr;
    char svar;

    printf("Indtast CPR-nummer på patienten> \n");
    scanf(" %ld", &cpr);

    char sql[100];
    sprintf(sql, "SELECT * FROM patients WHERE cpr = %ld", cpr);

    executeSQL(sql, 0);

    printf("Er patientens navn %s og CPR-nummer %ld korrekt? [y/n]\n", cur.name, cur.cpr);
    scanf(" %c", &svar);

    sprintf(sql, "SELECT * FROM patmed WHERE cpr = %ld", cpr);
    executeSQL(sql, 1);

    printf("Valgte patient er %s\n", cur.name);

    return cpr;
}

int executeSQL(const char *sql, int type) {
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("sql/p1data.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    if(type == 1){
        rc = sqlite3_exec(db, sql, recept_callback, 0, &err_msg);
    }
    else{
        rc = sqlite3_exec(db, sql, person_callback, 0, &err_msg);
    }

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute SQL query\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int person_callback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;

    cur.cpr = atol(argv[0]);
    cur.name = strdup(argv[1]);
    cur.weight = atoi(argv[2]);

    printf("\n");

    return 0;
}

int recept_callback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;

    if (recepts == NULL) {
        recepts = malloc(sizeof(recept));
    } else {
        // Extend the array size
        recepts = realloc(recepts, (antalrecepts + 1) * sizeof(recept));
    }

    recepts[antalrecepts].cpr = atol(argv[0]);
    recepts[antalrecepts].id = atoi(argv[1]);
    recepts[antalrecepts].dosage = atoi(argv[2]);
    recepts[antalrecepts].frequency = atoi(argv[3]);
    antalrecepts++;

    return 0;
}