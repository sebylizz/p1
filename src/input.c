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

    do { // forskellige muligheder i programmet
        printf("\nType c to create a prescription\n");
        printf("Type d to delete a prescription\n");
        printf("Type v to view existing prescription(s)\n");
        printf("Type h to view patient medical history\n");
        printf("Type q to quit program\n");

        scanf(" %c", &valg);
        if (valg == 'v') { // se eksisterende recepter
            printf("\nName: %s | CPR: %s\n", cur.name, cur.cpr);
            int width = getTerminalWidth();
            char symbol = '_';
            for (int i = 0; i < width; i++) {
                printf("%c", symbol);
            }
            for (int i = 0; i < antalrecepts; i++) {
                print_recept(i+1, recepts[i].medname, recepts[i].notes, recepts[i].dosage, recepts[i].frequency);
            }
            printf("\n");
        }
        else if (valg == 'h') { //print tidligere recepter (Slettede)


        }
        else if (valg == 'c') { //lave en ny recept
            medicin(cur.name);
            int width = getTerminalWidth();
            char symbol = '-';
            for (int i = 0; i < width; i++) {
                printf("%c", symbol);
            }
            print_recept(antalrecepts-1, recepts[antalrecepts-1].medname, recepts[antalrecepts-1].notes, recepts[antalrecepts-1].dosage, recepts[antalrecepts-1].frequency);
            printf("\n");
        }
        else if (valg == 'd') { //slet en eksisterende recept
            char sletvalg;
            if (antalrecepts == 0) {
                printf("There is no existing prescriptions prescribed to the chosen patient\n");
            }
            else {
                printf("\nName: %s | CPR: %s\n", cur.name, cur.cpr);
                int width = getTerminalWidth();
                char symbol = '_';
                for (int i = 0; i < width; i++) {
                    printf("%c", symbol);
                }
                for (int i = 0; i < antalrecepts; i++) {
                    print_recept(i+1, recepts[i].medname, recepts[i].notes, recepts[i].dosage, recepts[i].frequency);
                    printf("\n");
                }
                char check_sletvalg;
                do {
                    printf("\nWhich prescription do you wish to delete? Type the registration number:\n");
                    printf("Type 'q' if you do not wish to delete a prescription\n");
                    scanf(" %c", &sletvalg);
                    if (sletvalg == 'q' ){
                        break;
                    }
                    else {
                        printf("\nIs it correct that you want to delete prescription %c? [y/n]\n", sletvalg);
                        scanf(" %c", &check_sletvalg);
                    }
                } while (check_sletvalg != 'y');
                if (sletvalg != 'q') {
                    int sletvalg_d = (sletvalg - '0') - 1;
                        delete_recept( (sletvalg_d));
                }

            }
        }

    } while (valg != 'q'); // lukke programmet

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

        printf("\nType the patients CPR-Number: \n");
        scanf(" %s", cpr);
        sprintf(sql, "SELECT * FROM patients WHERE cpr = '%s'", cpr);

        sqlite3_exec(db, sql, person_callback, 0, &err_msg);

        if(strcmp(cur.cpr, "NULL") == 0){
            printf("\nInvalid CPR-Number\n");
        }

        else{ // check
            printf("Is the patients name: %s and CPR-Number: %s correct? [y/n]\n", cur.name, cur.cpr);
            scanf(" %c", &svar);
        }

    } while (svar != 'y' || strcmp(cur.cpr, "NULL") == 0);

    sprintf(sql, "SELECT medicine.medicine, patmed.dosage, patmed.frequency, patmed.notes, rid FROM patmed JOIN medicine ON medicine.id = patmed.id WHERE patmed.cpr = '%s'", cpr);
    sqlite3_exec(db, sql, recept_callback, 0, &err_msg);

    sqlite3_close(db);

    printf("\nChosen patient is: %s\n", cur.name);
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

    sprintf(sql, "INSERT INTO delrecepts SELECT * FROM patmed WHERE rid = %d", recepts[valg].rid);
    sqlite3_exec(db, sql, NULL, 0, &err_msg);

    sprintf(sql, "DELETE FROM patmed WHERE rid = %d", recepts[valg].rid);
    sqlite3_exec(db, sql, NULL, 0, &err_msg);

    antalrecepts = 0;
    free(recepts);
    recepts = NULL;
    sprintf(sql, "SELECT medicine.medicine, patmed.dosage, patmed.frequency, patmed.notes, rid FROM patmed JOIN medicine ON medicine.id = patmed.id WHERE patmed.cpr = '%s'", cur.cpr);
    sqlite3_exec(db, sql, recept_callback, 0, &err_msg);

    sqlite3_close(db);
}

