#include <stdio.h>
#include <string.h>

void bi_medicin();

int main(void) {

    bi_medicin();

    return 0;

}

void bi_medicin() {

    char svar, bi_check_1, bi_check_2;
    int bi_dosis_1, bi_frek_1;
    char med_input[20];

    if (strcmp(med_input, "prednisolon")==2) {

        printf("Bivirkninger på prednisolon kan dæmpes med: Pantoprazol, skal det med? [y/n] \n");
        scanf(" %c", &svar);

        if (svar == 'y') {

            printf("What dosage of Pantoprazol would you like to prescribe? (in mg) \n");
            scanf(" %d", &bi_dosis_1);

            printf("Is %d mg the correct dosage of Pantoprazol you wish to prescribe? [y/n] \n", bi_dosis_1);
            scanf(" %c", &bi_check_1);

        }

        if (svar == 'y') {

            printf("How many times a day do you wish the patient to take Pantoprazol with the dosage of %d mg \n", bi_dosis_1);
            scanf(" %d", &bi_frek_1);

            printf("Is it correct that you wish the patient takes Pantoprazol %d times/time a day with the dosage of %d mg? [y/n] \n", bi_frek_1, bi_dosis_1);
            scanf(" %c", &bi_check_2);

        }

    }

}