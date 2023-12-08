#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "helpers.h"
#include "../sql/sqlite3.h"

person cur;
recept *recepts = NULL;
delrecept *delrecepts = NULL;
int antalrecepts, antaldelrecepts, medid;
sqlite3 *db;
char *err_msg = 0;

char* sti = "sql/p1data.db";

int main(void) {
    int rc = sqlite3_open(sti, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    login();

    sqlite3_close(db);
    free(recepts);
    return 0;
}

void login(){
    char svar;
    do {
        textColor('b');
        printf("\nIf doctor press d \n");
        textColor('y');
        printf("If patient, nurse, citizen etc. press p\n");
        textColor('w');
        scanf(" %c", &svar);

        if (svar == 'd') {
            doctor();
        } else if (svar == 'p') {
            nurse();
        }
    } while (svar != 'd' && svar != 'p');
}

void doctor(){
    load_patient();

    char valg;
    do { // forskellige muligheder i programmet
        printf("\nType c to create a prescription\n");
        printf("Type d to delete a prescription\n");
        printf("Type v to view existing prescription(s)\n");
        printf("Type h to view previous prescription(s)\n");
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
        else if (valg == 'h') { //se tidligere recepter (Slettede)
            printf("\nName: %s | CPR: %s\n", cur.name, cur.cpr);
            int width = getTerminalWidth();
            char symbol = '_';
            for (int i = 0; i < width; i++) {
                printf("%c", symbol);
            }
            for (int i = 0; i < antaldelrecepts; i++) {
                print_recept(i+1, delrecepts[i].medname, delrecepts[i].notes, delrecepts[i].dosage, delrecepts[i].frequency);
            }
            printf("\n");

        }
        else if (valg == 'c') { //lave en ny recept
            medicin(cur.name);
            int width = getTerminalWidth();
            char symbol = '-';
            for (int i = 0; i < width; i++) {
                printf("%c", symbol);
            }
            print_recept(antalrecepts, recepts[antalrecepts-1].medname, recepts[antalrecepts-1].notes, recepts[antalrecepts-1].dosage, recepts[antalrecepts-1].frequency);
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

    exit(EXIT_SUCCESS);
}

void nurse(){
    load_patient();

    char valg;
    do { // forskellige muligheder i programmet

        printf("\nType v to view existing prescription(s)\n");
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
        else if (valg == 'h') { //se tidligere recepter (Slettede)
            printf("\nName: %s | CPR: %s\n", cur.name, cur.cpr);
            int width = getTerminalWidth();
            char symbol = '_';
            for (int i = 0; i < width; i++) {
                printf("%c", symbol);
            }
            for (int i = 0; i < antaldelrecepts; i++) {
                print_recept(i+1, delrecepts[i].medname, delrecepts[i].notes, delrecepts[i].dosage, delrecepts[i].frequency);
            }
            printf("\n");

        }
    } while (valg != 'q'); // lukke programmet

    exit(EXIT_SUCCESS);
}

void medicin(char* name) {

    char check1, check2, check3, check5, check6, check7, check8;
    int check4;
    int frek, medid;
    float dosis;
    char med_input[20];
    char desk[250];
    char s_time;

    do {
        // Spørge om medicin
        // Skal kobles sammen med første input funktion så der spørges om navnet herunder //
        printf("\nWhat medicine would you like to prescribe to %s?\n", name);
        scanf(" %s", med_input);
        medid = check_med(med_input);

        while(medid == 0){
            printf("\nMedicine not found, please try again\n");
            printf("\nWhat medicine would you like to prescribe to %s?\n", name);
            scanf(" %s", med_input);
            medid = check_med(med_input);
        }

        // Check funktion
        printf("\nIs %s the correct medicine you wish to prescribe? [y/n]\n", med_input);
        scanf(" %c", &check1);

    } while (check1 != 'y');

    here: do { // spørge om styrke, evt. tilføje checks i forhold til grænser udfra database med bestemt medicin
        printf("\nWhat dosage of %s would you like to prescribe? (in mg)\n", med_input);
        scanf(" %f", &dosis);

        // Check funktion
        printf("\nIs %.2f mg the correct dosage of %s you wish to prescribe? [y/n]\n", dosis, med_input);
        scanf(" %c", &check2);

    } while (check2 != 'y');

    int max = check_med_max(med_input);
    if (dosis > max){
        textColor('r');
        printf("\n%s with the dosage of %.2f mg is dangerous, want to proceed? [y/n]\n", med_input, dosis);
        textColor('w');
        scanf(" %c", &check8);

        if (check8 == 'n') {
            goto here;
        }
    }

    //char times[frek][6];
    do { // Spørge om frekvensen
        printf("\nHow many times a day do you wish for the patient to take %.2f mg %s?\n", dosis, med_input);
        scanf(" %d", &frek);
        // Check funktion
        printf("\nIs it correct that you want the patient to take %.2f mg of %s %d time(s) a day? [y/n]\n", dosis, med_input, frek);
        scanf(" %c", &check3);

    } while (check3 != 'y');

    do {
        // spørger om beskrivelsen
        printf("\nState your description of when and how the patient should take %s:\n", med_input);
        getchar();
        fgets(desk, 250, stdin);
        desk[strcspn(desk, "\n")] = 0;
        // Check funktion
        printf("\nIs the following description correct: %s [y/n]\n", desk);
        scanf(" %c", &check7);
    } while (check7 != 'y');

    insert_recept(medid, dosis, frek, desk);
}

void load_patient() {

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

    sprintf(sql, "SELECT medicine.medicine, delrecepts.dosage, delrecepts.frequency, delrecepts.notes, rid FROM delrecepts JOIN medicine ON medicine.id = delrecepts.id WHERE delrecepts.cpr = '%s'", cpr);
    sqlite3_exec(db, sql, delrecepts_callback, 0, &err_msg);


    printf("\nChosen patient is: %s\n", cur.name);   
}

int check_med(char med_input[20]){
    medid = 0;
    char sql[250];
    sprintf(sql, "SELECT id FROM medicine WHERE LOWER(medicine) = LOWER('%s')", med_input);
    sqlite3_exec(db, sql, medicine_callback, 0, &err_msg);

    return medid;
}

void insert_recept(int medid, double dosis, int frek, char desk[250]){
    char sql[250];
    sprintf(sql, "INSERT INTO patmed(cpr, id, dosage, frequency, notes) VALUES('%s', %d, %f, %d, '%s')", cur.cpr, medid, dosis, frek, desk);
    sqlite3_exec(db, sql, NULL, 0, &err_msg);

    antalrecepts = 0;
    free(recepts);
    recepts = NULL;
    sprintf(sql, "SELECT medicine.medicine, patmed.dosage, patmed.frequency, patmed.notes, rid FROM patmed JOIN medicine ON medicine.id = patmed.id WHERE patmed.cpr = '%s'", cur.cpr);
    sqlite3_exec(db, sql, recept_callback, 0, &err_msg);
}

void delete_recept(int valg){
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
}

int check_med_max(char med_input[20]){ //shit code here
    char sql[250];

    medid = 0;
    sprintf(sql, "SELECT max FROM medicine WHERE LOWER(medicine) = LOWER('%s')", med_input);
    sqlite3_exec(db, sql, medicine_callback, 0, &err_msg);

    return medid;
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

int delrecepts_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;

    if (delrecepts == NULL) {
        delrecepts = malloc(sizeof(delrecept));
    } else {
        delrecepts = realloc(delrecepts, (antaldelrecepts + 1) * sizeof(delrecept));
    }
    strcpy(delrecepts[antaldelrecepts].medname, strdup(argv[0]));
    delrecepts[antaldelrecepts].dosage = atoi(argv[1]);
    delrecepts[antaldelrecepts].frequency = atoi(argv[2]);
    if(argv[3] != NULL){strcpy(delrecepts[antaldelrecepts].notes, (strdup(argv[3])));}
    delrecepts[antaldelrecepts].rid = atoi(argv[4]);

    antaldelrecepts++;

    return 0;
}

int medicine_callback(void *NotUsed, int argc, char **argv, char **azColName){
    medid = atoi(argv[0]);
    return 0;
}