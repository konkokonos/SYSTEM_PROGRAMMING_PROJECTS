#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Commands.h>
#include <stdint.h>

int main (int argc, char **argv) 
{
    FILE* fi;
    char *pfile = NULL; //citizenRecordsFile
    int bloomsize = 0; //bloomSize

    if (argc == 5)
    {
        for(int i=0; i<5; i++)
        {
            if(strcmp(argv[i],"-c") == 0)
                pfile=argv[i+1];
            if(strcmp(argv[i],"-b") ==0)
                bloomsize=atoi(argv[i+1]);
        }
    }
    printf("patientRecordsFile has value: %s\n",pfile);
    printf("bloomSize has value: %d\n",bloomsize);
    printf("///////////////////////////////////////////////////////////////////\n");

    fi = fopen (pfile, "r");
    if (fi == NULL) 
    {
        printf ("Adynamia anoigmatos toy dosmenou arxeiou\n");
        return 1;
    }
    record** array_for_structs = NULL;
    array_for_structs = create_array_of_structs(fi);    //print_array_for_structs(array_for_structs);
    
    re returns;
    returns = create_array_of_virus_structs(array_for_structs,bloomsize);
    virus *array_of_virus_structs = returns.array_of_virus_structs;     //print_array_of_virus_structs(array_of_virus_structs,elements,bloomsize);
    int elements = returns.elements -1;

    commands(array_of_virus_structs,elements,bloomsize);
}