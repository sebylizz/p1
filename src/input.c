#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "input.h"
#include "../sql/sqlite3.h"

person cur;
recept *recepts = NULL;
int antalrecepts;

int main(void) {

    char* cpr = load_patient();

    char valg;

    printf("Skriv i for at oprette recept\n");
    printf("Skriv s for at slette recept\n");
    printf("Skriv r for at se aktuelle recepter\n");
    printf("Skriv q for at afslutte program\n");

    scanf(" %c", &valg);
    if(valg == 'r'){
        //print_recepts
        for(int i = 0; i < antalrecepts; i++){printf("%s, %d, %d, %s\n", recepts[i].medname, recepts[i].dosage, recepts[i].frequency, recepts[i].notes);}
    }

    free(recepts);
    return 0;
}

char* load_patient() {

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("sql/p1data.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    char cpr[11];
    char svar;
    char sql[250];

    do{
        strcpy(cur.cpr, "NULL");
        strcpy(cur.name, "NULL");
        cur.weight = 0;

        printf("Indtast CPR-nummer på patienten> \n");
        scanf(" %s", cpr); 
        sprintf(sql, "SELECT * FROM patients WHERE cpr = '%s'", cpr);
        
        sqlite3_exec(db, sql, person_callback, 0, &err_msg);

        if(strcmp(cur.cpr, "NULL") == 0){
            printf("Fejlagtigt CPR-Nummer\n");
        }

        else{
            printf("Er patientens navn %s og CPR-nummer %s korrekt? [y/n]\n", cur.name, cur.cpr);
            scanf(" %c", &svar); 
        }

    } while (svar != 'y' || strcmp(cur.cpr, "NULL") == 0);
    
    sprintf(sql, "SELECT medicine.medicine, patmed.dosage, patmed.frequency, patmed.notes FROM patmed JOIN medicine ON medicine.id = patmed.id WHERE patmed.cpr = '%s'", cpr);
    sqlite3_exec(db, sql, recept_callback, 0, &err_msg);

    sqlite3_close(db);
   
    printf("Valgte patient er %s\n", cur.name);
    return cur.cpr;
}

int person_callback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;

    strcpy(cur.cpr, strdup(argv[0]));
    strcpy(cur.name, strdup(argv[1]));
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

    strcpy(recepts[antalrecepts].medname, strdup(argv[0]));
    recepts[antalrecepts].dosage = atoi(argv[1]);
    recepts[antalrecepts].frequency = atoi(argv[2]);
    if(argv[3] != NULL){strcpy(recepts[antalrecepts].notes, (strdup(argv[3])));}

    antalrecepts++;

    return 0;
}