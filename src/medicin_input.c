#include <stdio.h>
#include <string.h>

void medicin() {

    char check1, check2, check3, check5, check6, check7;
    int check4;
    int dosis, frek;
    char med_input[20];
    char s_time;

    do {
        // Spørge om medicin
        // Skal kobles  sammen med første input funktion så der spørges om navnet herunder //
        printf("What medicine would you like to prescribe to \n");
        scanf(" %s", med_input);
        // Check funktion
        printf("Is %s the correct medicine you wish to prescribe? [y/n]\n", med_input);
        scanf(" %c", &check1);

    } while (check1 != 'y');

    do { // spørge om styrke, evt. tilføje checks i forhold til grænser udfra database med bestemt medicin
        printf("What dosage of %s would you like to prescribe? (in mg)\n", med_input);
        scanf(" %d", &dosis);

        // Check funktion
        printf("Is %d mg the correct dosage of %s you wish to prescribe? [y/n]\n", dosis, med_input);
        scanf(" %c", &check2);


    } while (check2 != 'y');

    char times[frek][6];
    do { // Spørge om frekvensen
        printf("How many times a day do you wish the patient to take %s with the dosage of %d mg\n", med_input, dosis);
        scanf(" %d", &frek);
        // Check funktion
        printf("Is it correct that you wish the patient takes %s %d time(s) a day with the dosage of %d mg? [y/n]\n",
               med_input, frek, dosis);
        scanf(" %c", &check3);

    } while (check3 != 'y');

    //bi_medicin();
    do { // Spørge om det skal være bestemte tidspunkter eller en beskrivelse af hvornår det skal tages ca.
        printf("1. Do you wish for the patient to take the medicine at a specific time/times?\n");
        printf("2. Do you wish to give the patient a description of when to take the medicine? [1/2]\n");
        scanf(" %d", &check4);

    } while (check4 != 1 && check4 != 2);

    if (check4 == 1) {
        if (frek == 1) {
            do { // spørge om bestemt tidspunkt hvis frekvensen kun er 1
                printf("At what time of day do you wish the patient takes %s (24 hour format, i.e 16:00)\n", med_input);
                scanf(" %s", &s_time);
                // Check funktion
                printf("Is it correct that you wish for the patient to take %s at %s [y/n]\n", med_input, s_time);
                scanf(" %c", &check5);
            } while (check5 != 'y');
        } else {
            do { // spørge om flere tidspunkter da frekvensen er over 1
                printf("State the specific times a day the patient should take %s,\nfrom first to last, one at the time (24 hour format, i.e 16:00)\n",
                       med_input);
                for (int i = 0; i < frek; i++) {
                    scanf(" %s", times[i]);
                    //times[i]
                    printf("State the next time they should take %s\n", med_input);
                }// Check funktion
                printf("Is it correct that you wish for the patient to take %s at the following times: [y/n]\n",
                       med_input);
                for (int i = 0; i < frek; i++) {
                    printf("%s\n", times[i]);
                }
                scanf(" %c", &check6);

            } while (check6 != 'y');

        }
    }
    if (check4 == 2) {
        do {
            char d_time[250]; // spørger om beskrivelsen
            printf("State your description of when the patient should take %s:\n", med_input);
            getchar();
            fgets(d_time, 250, stdin);
            // Check funktion
            printf("Is the following description correct: %s [y/n]\n", d_time);
            scanf(" %c", &check7);
        } while (check7 != 'y');
    }
}

// printning af recept (ikke helt færdig)
void print_recept(char* cpr, char* navn, char* mednavn, char* besk, int styrke) {

    printf("CPR: %s\n Patient navn: %s\n\n Medicin: \n - Navn: %s\n Beskrivelse: %s\n - Styrke: %d (mg)", cpr, navn, mednavn, besk, styrke);
    /* printf("\n\nDosering forslag: \n - Dosis: %d (mg) %d gang(e) om dagen\n")
     if (check4 == 1) {
         printf("Doserings tidspunkter: ");
         for (int i = 0; i < frek; i++){
             printf("%s  ", times[i]);
         }
     }
     else {
         printf("%s\n\n\n", d_time);
     } */

}