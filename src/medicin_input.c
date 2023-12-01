#include <stdio.h>
#include <string.h>
#include "input.h"
#include <sys/ioctl.h>
#include <unistd.h>

void medicin(char* name) {

    char check1, check2, check3, check5, check6, check7;
    int check4;
    int dosis, frek, medid;
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
            printf("\nWhat medicine would you like to prescribe to \n");
            scanf(" %s", med_input);
            medid = check_med(med_input);
        }

        // Check funktion
        printf("\nIs %s the correct medicine you wish to prescribe? [y/n]\n", med_input);
        scanf(" %c", &check1);

    } while (check1 != 'y');

    do { // spørge om styrke, evt. tilføje checks i forhold til grænser udfra database med bestemt medicin
        printf("\nWhat dosage of %s would you like to prescribe? (in mg)\n", med_input);
        scanf(" %d", &dosis);

        // Check funktion
        printf("\nIs %d mg the correct dosage of %s you wish to prescribe? [y/n]\n", dosis, med_input);
        scanf(" %c", &check2);


    } while (check2 != 'y');

    //char times[frek][6];
    do { // Spørge om frekvensen
        printf("\nHow many times a day do you wish for the patient to take %d mg %s?\n", dosis, med_input);
        scanf(" %d", &frek);
        // Check funktion
        printf("\nIs it correct that you want the patient to take %d mg of %s %d time(s) a day? [y/n]\n", dosis, med_input, frek);
        scanf(" %c", &check3);

    } while (check3 != 'y');

    //bi_medicin();
    /*do { // Spørge om det skal være bestemte tidspunkter eller en beskrivelse af hvornår det skal tages ca.
        printf("1. Do you wish for the patient to take the medicine at a specific time/times?\n");
        printf("2. Do you wish to give the patient a description of when to take the medicine? [1/2]\n");
        scanf(" %d", &check4);
    } while (check4 != 1 && check4 != 2);*/

    /*if (check4 == 1) {
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
    }*/
    do {
        // spørger om beskrivelsen
        printf("\nState your description of when and how the patient should take %s:\n", med_input);
        getchar();
        fgets(desk, 250, stdin);
        // Check funktion
        printf("\nIs the following description correct: %s [y/n]\n", desk);
        scanf(" %c", &check7);
    } while (check7 != 'y');

    insert_recept(medid, dosis, frek, desk);
}

// printning af recept
void print_recept(int tempid, char* mednavn, char* besk, int styrke, int frek) {

    printf("Prescription #%d", tempid);

    printf(" | Medicine: %s", mednavn);
           for (int i = strlen(mednavn); i < 12; i++){
               printf(" ");
           }
           printf("| Strength: %d mg/dose", styrke);
           char temp[5];
           sprintf(temp, "%d", styrke);
           for (int i = strlen(temp); i < 4; i++){
               printf(" ");
           }
           printf(" | Frequency: %d time(s) a day \nDescription: %s \n",frek, besk);

    // Printer linjer mellem recepter
    int width = getTerminalWidth();
    char symbol = '-';
    for (int i = 0; i < width; i++) {
        printf("%c", symbol);
    }
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

int getTerminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}
