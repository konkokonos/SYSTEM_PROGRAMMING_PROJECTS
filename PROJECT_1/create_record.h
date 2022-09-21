typedef struct record
{
    unsigned char* citizenID;
    char* firstName;
    char* lastName;
    char* country;
    char* age;
    char* virusName;
    char* YN;
    char* dateVaccinated;
    struct record *next;
}record;

record* create_record(unsigned char*,char*,char*,char*,char*,char*,char*,char*);