#include <stdio.h>

int bekraeft_cpr();

int main(void) {

    int cpr = bekraeft_cpr();

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