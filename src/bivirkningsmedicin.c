#include "../sql/sqlite3.h"
#include <stdio.h>
#include <string.h>

void bi_medicin();
int har_modvirkende_medicin(char* med);

int main(void) {

    bi_medicin();

    return 0;

}


char *med_input = "Panodil";
int har_modvirkende_medicin(char* med){
    return 1;
}

void bi_medicin() {

    if (har_modvirkende_medicin(med_input)) {

        printf("There seems to be a possible counteracting medication, would you like to prescribe? [y/n] \n");
        scanf(" %c", &svar_bi);

        if (svar_bi == 'y') {

            // Kør Lukas' funktion

        }

    }

}