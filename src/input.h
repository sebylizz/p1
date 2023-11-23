typedef struct{
    char cpr[11];
    char name[30];
    int weight;
} person;

typedef struct{
    char cpr[11];
    int id;
    int dosage;
    int frequency;
} recept;

int person_callback(void *, int, char **, char **);
int recept_callback(void *, int, char **, char **);
int executeSQL(const char *sql, int type);
char* load_patient();