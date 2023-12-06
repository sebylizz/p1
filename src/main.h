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

typedef struct{
    int rid;
    char medname[20];
    int dosage;
    int frequency;
    char notes[200];
} delrecept;

void medicin(char* name);
void load_patient();
void login();
void doctor();
void nurse();

int person_callback(void *, int, char **, char **);
int recept_callback(void *, int, char **, char **);
int delrecepts_callback(void *, int, char **, char **);
int medicine_callback(void *, int, char **, char **);

int check_med(char med_input[20]);
int check_med_max(char med_input[20]);
void insert_recept(int medid, int dosis, int frek, char desk[250]);
void delete_recept(int valg);