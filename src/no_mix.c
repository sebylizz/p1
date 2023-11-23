#include <stdio.h>
#include <string.h>

void no_mix();

int main(void) {

    no_mix();

    return 0;

}

void no_mix() {

    char svar;

    if (strcmp(med_input, med_input_2)==1) {

        printf("%s and %s can be deadly if mixed together, are you sure you want to proceed? [y/n] \n", med_input, med_input_2);
        scanf(" %c", &svar);

        if (svar == 'y') {

            // RUN LUKASS FINE FUNKTION JA TAK yup

        }

    }

}