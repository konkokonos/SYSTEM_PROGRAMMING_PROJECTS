#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Commands.h>

void commands(virus* array_of_virus_structs, int elements, int bloomsize)
{
    char *command;
    char* token;
    size_t len = 0;
    unsigned char citizenID[5];
    char virusName[20];

    while(1)
    {
        puts("Parakalw dwste ena command");
        getline(&command,&len,stdin);
        if (strcmp(command,"/exit\n") == 0)
            {
                printf("To programma tha termatisei\n");
                break;
            }
        else 
            printf("Exete dwsei to command: %s",command);

        char copy[strlen(command)+1];
        strcpy(copy,command);
        token = strtok(copy," ");
        char comm[strlen(token)];

        if(strcmp(token,"/vaccineStatusBloom") == 0) // /vaccineStatusBloom citizenID virusName
        {   
            int a;
            a = sscanf(command,"%s %s %s",comm,citizenID,virusName);
            if(a!=3)
                printf ("H eggrafi pou thelete na kataxwrisete exei problhma\n");
            else
            {
                for (int i=0; i<=elements; i++)
                {
                    int b=0;
                    if(strcmp(virusName,array_of_virus_structs[i].name) == 0)
                    {
                        int* bloom_filt = array_of_virus_structs[i].bloom_filter;
                        unsigned long* pinakas_thesewn;
                        pinakas_thesewn = NULL;
                        pinakas_thesewn = pinakas_me_k_hash(citizenID, bloomsize);
                        for(int i =0; i<16; i++)
                        {
                            unsigned long byteposition = pinakas_thesewn[i]/8;  //printf("%d\n",bloom_filt[byteposition]);
                            unsigned int bitposition = pinakas_thesewn[i]%8;    //printf("%d\n",bitposition);
                            int pin[8];
                            for (int j = 8; j >= 0; j--)
                            {
                                int k = bloom_filt[byteposition] >> j;
                                if (k & 1)
                                    pin[7-j]=1;
                                else
                                    pin[7-j]=0;
                            }
                            if(pin[7-bitposition] == 1)
                                continue;
                            else
                            {
                                printf("NOT VACCINATED\n");
                                b =1;
                                break;
                            }
                        }
                        if(b == 1)
                            break;
                        else
                            printf("MAYBE\n");
                    }
                    else
                        printf("THERE IS NO VIRUS WITH SUCH NAME,PLEASE TRY AGAIN\n");
                }
            }
        }
        
        else
            printf("MH APODEKTO COMMAND,PROSPATHISTE PALI\n");
    }
}
