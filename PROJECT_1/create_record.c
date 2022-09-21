#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <create_record.h>

record* create_record(unsigned char* citizenID,char* firstName,char* lastName,char* country,char* age,char* virusName,char* YN,char* dateVaccinated)
{
    record* eggrafi;

    eggrafi =(record*)malloc(sizeof (record));
    if (eggrafi == NULL) 
    {
        printf ("Ran out of memory\n");
    }
    unsigned char* id =(unsigned char*)malloc(strlen(citizenID)+1);
    strcpy(id,citizenID);
    eggrafi->citizenID = id;
    char* fname =(char*)malloc(strlen(firstName)+1);
    strcpy(fname,firstName);
    eggrafi->firstName = fname;
    char* lname =(char*)malloc(strlen(lastName)+1);
    strcpy(lname,lastName);
    eggrafi->lastName = lname;
    char* coun =(char*)malloc(strlen(country)+1);
    strcpy(coun,country);
    eggrafi->country = coun;
    char* ag =(char*)malloc(strlen(age)+1);
    strcpy(ag,age);
    eggrafi->age = ag;
    char* vname =(char*)malloc(strlen(virusName)+1);
    strcpy(vname,virusName);
    eggrafi->virusName = vname;
    char* yn =(char*)malloc(strlen(YN)+1);
    strcpy(yn,YN);
    eggrafi->YN = yn;
    if(strcmp(eggrafi->YN,"NO") == 0)
    {
        eggrafi->dateVaccinated = '\0';
    }
    else
    {
        char* dvac =(char*)malloc(strlen(dateVaccinated)+1);
        strcpy(dvac,dateVaccinated);
        eggrafi->dateVaccinated = dvac;
    }

    return eggrafi;
}