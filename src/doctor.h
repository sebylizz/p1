#include "../sql/sqlite3.h"

typedef struct{
    char cpr[11];
    char name[30];
} person;

typedef struct{
    int rid;
    char medname[20];
    int dosage;
    int frequency;
    char notes[200];
} recept;

void medicin();
void load_patient();
void doctor();
void nurse();
void dbinit();

int person_callback(void *, int, char **, char **);
int recept_callback(void *, int, char **, char **);
int delrecepts_callback(void *, int, char **, char **);
int medicine_callback(void *inp, int, char **, char **);

int check_med(char med_input[20]);
int check_med_max(char med_input[20]);
void insert_recept(int medid, int dosis, int frek, char desk[250]);
void delete_recept(int valg);