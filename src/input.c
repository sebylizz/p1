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
    if (cpr == -1){
        return -1;
    }

    char valg;

    printf("Skriv r for at se aktuelle recepter\n");
    printf("Skriv q for at afslutte program\n");

    scanf(" %c", &valg);
    if(valg == 'r'){
        int i = 0;
        for(int i = 0; i < antalrecepts; i++){
            printf("%ld, %i, %i, %i\n", recepts[i].cpr, recepts[i].id, recepts[i].dosage, recepts[i].frequency);
        }
    }
    
    return 0;
}

int load_patient() {

    char* cpr;
    char svar;
    char sql[100];

    do{
        cur.cpr = 0;
        cur.name = "NULL";
        cur.weight = 0;

        printf("Indtast CPR-nummer på patienten> \n");
        scanf(" %s", cpr); 
        sprintf(sql, "SELECT * FROM patients WHERE cpr = %s", cpr);
        
        executeSQL(sql, 0);

        if(cur.cpr == 0){
            printf("Fejlagtigt CPR-Nummer\n");
        }

        else{
            printf("Er patientens navn %s og CPR-nummer %ld korrekt? [y/n]\n", cur.name, cur.cpr);
            scanf(" %c", &svar); 
        }

    } while (svar != 'y' || cur.cpr == 0);
    
    sprintf(sql, "SELECT * FROM patmed WHERE cpr = %s", cpr);
    executeSQL(sql, 1);
   
    if (svar == 'y'){
        printf("Valgte patient er %s\n", cur.name);
        return cpr;
    }
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
        recepts = realloc(recepts, (antalrecepts + 1) * sizeof(recept));
    }

    recepts[antalrecepts].cpr = atol(argv[0]);
    recepts[antalrecepts].id = atoi(argv[1]);
    recepts[antalrecepts].dosage = atoi(argv[2]);
    recepts[antalrecepts].frequency = atoi(argv[3]);
    antalrecepts++;

    return 0;
}