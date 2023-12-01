#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "input.h"
#include "../sql/sqlite3.h"

person cur;
recept *recepts = NULL;
int antalrecepts, medid;
sqlite3 *db;
char *err_msg = 0;

char* sti = "sql/p1data.db";


int main(void) {

    char* cpr = load_patient();
    char valg;

    do {
        printf("\nSkriv i for at oprette recept\n");
        printf("Skriv s for at slette recept\n");
        printf("Skriv r for at se aktuelle recepter\n");
        printf("Skriv q for at afslutte program\n");

        scanf(" %c", &valg);
        if (valg == 'r') {
            //print_recepts funktion kaldes - Loopet skal være i selve funktionen senere hen
            printf("\nNavn: %s | CPR: %s\n", cur.name, cur.cpr);
            int width = getTerminalWidth();
            char symbol = '_';
            for (int i = 0; i < width; i++) {
                printf("%c", symbol);
            }
            for (int i = 0; i < antalrecepts; i++) {
                print_recept(i+1, recepts[i].medname, recepts[i].notes, recepts[i].dosage, recepts[i].frequency);
            }
        }
        else if (valg == 'i') {
            medicin();
            print_recept(antalrecepts-1, recepts[antalrecepts-1].medname, recepts[antalrecepts-1].notes, recepts[antalrecepts-1].dosage, recepts[antalrecepts-1].frequency);
        }
        else if (valg == 's') {
            int sletvalg;
            if (antalrecepts == 0) {
                printf("Der findes ikke nogle recepter under den valgte patients navn.\n");
            }
            else {
                printf("\nNavn: %s | CPR: %s\n", cur.name, cur.cpr);
                int width = getTerminalWidth();
                char symbol = '_';
                for (int i = 0; i < width; i++) {
                    printf("%c", symbol);
                }
                for (int i = 0; i < antalrecepts; i++) {
                    print_recept(i+1, recepts[i].medname, recepts[i].notes, recepts[i].dosage, recepts[i].frequency);
                }
                printf("\nHvilken recept ønsker du at slette? Indtast nummeret:\n");
            }
            scanf(" %d", &sletvalg);
            delete_recept(sletvalg-1);
            // indsæt sletfunktion sammenkoblet med "sletvalg"
        }

    } while (valg != 'q');

    free(recepts);
    return 0;
}

char* load_patient() {
    int rc = sqlite3_open(sti, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    char cpr[11];
    char svar;
    char sql[250];

    //Indlæs patient i program
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

    sprintf(sql, "SELECT medicine.medicine, patmed.dosage, patmed.frequency, patmed.notes, rid FROM patmed JOIN medicine ON medicine.id = patmed.id WHERE patmed.cpr = '%s'", cpr);
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
    recepts[antalrecepts].rid = atoi(argv[4]);

    antalrecepts++;

    return 0;
}

int medicine_callback(void *NotUsed, int argc, char **argv, char **azColName){
    medid = atoi(argv[0]);
    return 0;
}

int check_med(char med_input[20]){
    int rc = sqlite3_open("sql/p1data.db", &db);

    medid = 0;
    char sql[250];
    sprintf(sql, "SELECT id FROM medicine WHERE LOWER(medicine) = LOWER('%s')", med_input);
    sqlite3_exec(db, sql, medicine_callback, 0, &err_msg);

    return medid;

    sqlite3_close(db);
}

void insert_recept(int medid, int dosis, int frek, char desk[250]){
    int rc = sqlite3_open("sql/p1data.db", &db);

    char sql[250];
    sprintf(sql, "INSERT INTO patmed(cpr, id, dosage, frequency, notes) VALUES('%s', %d, %d, %d, '%s')", cur.cpr, medid, dosis, frek, desk);
    sqlite3_exec(db, sql, NULL, 0, &err_msg);
    antalrecepts = 0;
    free(recepts);
    recepts = NULL;
    sprintf(sql, "SELECT medicine.medicine, patmed.dosage, patmed.frequency, patmed.notes, rid FROM patmed JOIN medicine ON medicine.id = patmed.id WHERE patmed.cpr = '%s'", cur.cpr);
    sqlite3_exec(db, sql, recept_callback, 0, &err_msg);

    sqlite3_close(db);
}

void delete_recept(int valg){
    int rc = sqlite3_open("sql/p1data.db", &db);

    char sql[250];
    sprintf(sql, "DELETE FROM patmed WHERE rid = %d", recepts[valg].rid);
    sqlite3_exec(db, sql, NULL, 0, &err_msg);
    antalrecepts = 0;
    free(recepts);
    recepts = NULL;
    sprintf(sql, "SELECT medicine.medicine, patmed.dosage, patmed.frequency, patmed.notes, rid FROM patmed JOIN medicine ON medicine.id = patmed.id WHERE patmed.cpr = '%s'", cur.cpr);
    sqlite3_exec(db, sql, recept_callback, 0, &err_msg);

    sqlite3_close(db);
}