typedef struct{
    char cpr[11];
    char name[30];
    int weight;
} person;

typedef struct{
    int rid;
    char medname[20];
    int dosage;
    int frequency;
    char notes[200];
} recept;

int person_callback(void *, int, char **, char **);
int recept_callback(void *, int, char **, char **);
int medicine_callback(void *, int, char **, char **);
char* load_patient();
void print_recept(int tempid, char* mednavn, char* besk, int styrke, int frek);
void medicin();
void insert_recept(int medid, int dosis, int frek, char desk[250]);
void delete_recept(int valg);
int check_med(char med_input[20]);
int getTerminalWidth();