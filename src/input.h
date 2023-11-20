typedef struct{
    long cpr;
    char* name;
    int weight;
} person;

typedef struct{
    long cpr;
    int id;
    int dosage;
    int frequency;
} recept;

int person_callback(void *, int, char **, char **);
int recept_callback(void *, int, char **, char **);
int executeSQL(const char *sql, int type);
int load_patient();