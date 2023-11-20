#include "../sql/sqlite3.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

int main(void) {

    //SQL BOILERPLATER HERUNDER
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("../sql/p1data.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }
    // SQL BOILERPLATE HEROVER

    int cpr = bekraeft_cpr();

    char sql[200];
    sprintf(sql, "SELECT name FROM patients WHERE cpr = %d", cpr);



    //IK PIL
    //rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);

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

int bekraeft_cpr() {

    char svar;
    int cpr;
    char * sqlnavn = "Emil Bøsrup";

    do {

        printf("Indtast CPR-nummer på patienten> \n");
        scanf(" %d", &cpr);

        printf("Er patientens navn %s og CPR-nummer %d korrekt? [y/n]\n", sqlnavn, cpr);
        scanf(" %c", &svar);

    } while (svar != 'y');

    printf("Patientens navn er %s og CPR-nummer %d", sqlnavn, cpr);

    return cpr;

}