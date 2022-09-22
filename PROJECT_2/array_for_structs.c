#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <array_for_structs.h>

int elexos(record* eggrafi,record* *array_for_structs,int i)
{
    for(int j=0; j<i; j++)
    {
        if(strcmp(eggrafi->citizenID,array_for_structs[j]->citizenID) == 0)
        {
            record* tmp=array_for_structs[j];
            while(tmp!= NULL)
            {
                if(strcmp(eggrafi->firstName,tmp->firstName) == 0 &&
                    strcmp(eggrafi->lastName,tmp->lastName) == 0 &&
                    strcmp(eggrafi->country,tmp->country) == 0 &&
                    strcmp(eggrafi->age,tmp->age) == 0 &&
                    strcmp(eggrafi->virusName,tmp->virusName) != 0)
                    tmp=tmp->next;
                else
                    return -2; 
            }return j;
        }
    }
    return -1;
}

record** insert_to_array_of_structs(record* eggrafi,record** array_for_structs,int i,int found,int thesi)
{
    if(found == 1)
    {
        eggrafi->next = array_for_structs[thesi];
        array_for_structs[thesi] =eggrafi;
        //printf("THESI %d\n",thesi);
    }
    else
    {
        array_for_structs = (record**)realloc(array_for_structs,(i+1)*sizeof(record*));
        eggrafi->next = array_for_structs[i];
        array_for_structs[i] = eggrafi;
        array_for_structs[i]->next = NULL;
        //printf("THESI %d\n",i);
    }
    
    return array_for_structs;
}

void print_array_for_structs(record** array_for_structs)
{
    record* tmp = NULL;
    for(int j =0; array_for_structs[j] != NULL; j++)
    {
        tmp=array_for_structs[j];

        while(tmp != NULL)
        {
            printf("%s,%s",tmp->citizenID,tmp->virusName);
            tmp=tmp->next;
            printf(" ------ ");
        }
        printf("\n");
    }
}

record** create_array_of_structs(FILE* fi)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned char citizenID[5];
    char firstName[14],lastName[14],country[15],age[5],virusName[20],YN[4],dateVaccinated[11];
    citizenID[5]=firstName[14]=lastName[14]=country[15]=age[5]=virusName[20]=YN[4]=dateVaccinated[11]='\0';
    record* eggrafi;
    int i =0;
    record** array_for_structs;
    array_for_structs = NULL;
    int thesi =0;
    int found=0;

    while ((read = getline(&line, &len, fi)) != -1)
    {
        if (line[0] == '\0') 
        {
            printf ("Parakalw dwste allo arxeio me eggrafes\n");
        }
        if(7 <= sscanf(line, "%s %s %s %s %s %s %s %s",citizenID,firstName,lastName,country,age,virusName,YN,dateVaccinated)
        && sscanf(line, "%s %s %s %s %s %s %s %s",citizenID,firstName,lastName,country,age,virusName,YN,dateVaccinated) <=8)
        {
            if(strcmp(YN,"NO") == 0 && strcmp(dateVaccinated,"\0")!=0)
            {
                printf("ERROR IN RECORD %s",line);
                firstName[14]=lastName[14]=country[15]=age[5]=virusName[20]=YN[4]=dateVaccinated[11]='\0';
                continue;
            }
            eggrafi = create_record(citizenID,firstName,lastName,country,age,virusName,YN,dateVaccinated);
            thesi = elexos(eggrafi,array_for_structs,i);
            if(thesi > 0)
            {
                i--;
                found = 1;
            }
            else if(thesi == -1)
                found = 0;
            else
            {
                printf("ERROR IN RECORD %s",line);
                firstName[14]=lastName[14]=country[15]=age[5]=virusName[20]=YN[4]=dateVaccinated[11]='\0';
                continue;
            }
            //printf ("%s %s %s %s %s %s %s %s ",eggrafi->citizenID, eggrafi->firstName, eggrafi->lastName, eggrafi->country,eggrafi->age, eggrafi->virusName, eggrafi->YN, eggrafi->dateVaccinated);
            array_for_structs = insert_to_array_of_structs(eggrafi,array_for_structs,i,found,thesi);
            i++;
            firstName[14]=lastName[14]=country[15]=age[5]=virusName[20]=YN[4]=dateVaccinated[11]='\0';
        }
        else
            printf("ERROR IN RECORD %s\n",line);
    }

    return array_for_structs;
}