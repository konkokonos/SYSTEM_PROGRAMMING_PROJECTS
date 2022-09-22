#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Commands.h>

void commands()
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

        if(strcmp(token,"/travelRequest") == 0) // /travelRequest citizenID date countryFrom countryTo virusName
        {   printf("%s\n",token);
        }
        else if(strcmp(token,"/travelStats") == 0) // /travelStats virusName date1 date2 [country]
        {   printf("%s\n",token);

        }
        else if(strcmp(token,"/addVaccinationRecords") == 0) // /addVaccinationRecords country
        {   printf("%s\n",token);
            
        }
        else if(strcmp(token,"/searchVaccinationStatus") == 0) // /searchVaccinationStatus citizenID
        {   printf("%s\n",token);
            
        }
        else
            printf("MH APODEKTO COMMAND,PROSPATHISTE PALI\n");
    }
}