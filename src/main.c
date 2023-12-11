#include <stdio.h>
#include "helpers.h"
#include "doctor.h"

void login();

int main(void) {

    login();

    return 0;
}

void login(){
    char svar;
    do {
        //textColor('b');
        printf("\nIf doctor press d \n");
        //textColor('y');
        printf("If patient, nurse, citizen etc. press p\n");
        //textColor('w');
        scanf(" %c", &svar);

        if (svar == 'd') {
            doctor();
        } else if (svar == 'p') {
            nurse();
        }
    } while (svar != 'd' && svar != 'p');
}