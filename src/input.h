typedef struct{
    char cpr[11];
    char name[30];
    int weight;
} person;

typedef struct{
    char medname[20];
    int dosage;
    int frequency;
    char notes[200];
} recept;

int person_callback(void *, int, char **, char **);
int recept_callback(void *, int, char **, char **);
int executeSQL(const char *sql, int type);
char* load_patient();
void print_recept(char* cpr, char* navn, char* mednavn, char* besk, int styrke);
void medicin();