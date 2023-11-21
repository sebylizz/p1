
#include <stdio.h>


int medicin();

int main(void) {

    medicin();

    return 0;

}

int medicin(){
    char check1, check2, check3, check5, check6;
    int check4;
    int dosis, frek;
    char med_input[20];
    char s_time;
    do
    {
        // Skal kobles  sammen med første input funktion så der spørges om navnet herunder //
        printf("What medicine would you like to prescribe to \n");
        scanf(" %s", med_input);

        printf("Is %s the correct medicine you wish to prescribe? [y/n]\n", med_input);
        scanf(" %c", &check1);

    }
    while (check1 != 'y');

    do
    {
       printf("What dosage of %s would you like to prescribe? (in mg)\n", med_input);
       scanf(" %d", &dosis);

       printf("Is %d mg the correct dosage of %s you wish to prescribe? [y/n]\n",dosis, med_input);
       scanf(" %c", &check2);


    }
    while (check2 != 'y');

    do
    {
        printf("How many times a day do you wish the patient to take %s with the dosage of %d mg\n", med_input, dosis);
        scanf(" %d", &frek);

        printf("Is it correct that you wish the patient takes %s %d times/time a day with the dosage of %d mg? [y/n]\n",med_input, frek, dosis);
        scanf(" %c", &check3);

    }
    while (check3 != 'y');

    //bi_medicin();
    do
    {
        printf("1. Do you wish for the patient to take the medicine at a specific time/times?\n");
        printf("2. Do you wish to give the patient a description of when to take the medicine? [1/2]\n");
        scanf(" %d", &check4);
    }
    while (check4 != '1'||'2');


    if (check4 == '1')
    {
        if (frek == 1)
        {
            do {
                printf("At what time of day do you wish the patient takes %s (24 hour format)", med_input);
                scanf(" %s", &s_time);

                printf("Is it correct that you wish for the patient to take %s at %s [y/n]\n",med_input, s_time);
                scanf(" %c", &check5);
            }
            while (check5 != 'y');
        }
        else
        {


        }
    }
    if (check4 == '2')
        printf("Do you wish to ")


    printf("")

}