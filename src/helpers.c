#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "main.h"
#include <sys/ioctl.h>
#include <unistd.h>

// printning af recept
void print_recept(int tempid, char* mednavn, char* besk, float styrke, int frek) {

    printf("Prescription #%d", tempid);

    printf(" | Medicine: %s", mednavn);
           for (int i = strlen(mednavn); i < 12; i++){
               printf(" ");
           }
           printf("| Strength: %.1f mg/dose", styrke);
           char temp[11];
           sprintf(temp, "%.1f", styrke);
           for (int i = strlen(temp); i < 10; i++){
               printf(" ");
           }
           printf(" | Frequency: %d time(s) a day \nDescription: %s \n",frek, besk);

    // Printer linjer mellem recepter
    int width = getTerminalWidth();
    char symbol = '-';
    for (int i = 0; i < width; i++) {
        printf("%c", symbol);
    }
}

int getTerminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void textColor(char col){     
    switch(col){
        case 'r':
            printf("\033[1;31m");
            break;
        case 'g':
            printf("\033[1;32m");
            break;
        case 'y':
            printf("\033[1;33m");
            break;
        case 'b':
            printf("\033[1;34m");
            break;
        default:
            printf("\033[0m");
            break;
    }
}

void printline(){
    int width = getTerminalWidth();
    char symbol = '-';
    for (int i = 0; i < width; i++) {
        printf("%c", symbol);
    }
}
