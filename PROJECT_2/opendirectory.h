#include <dirent.h>
#include <string.h>
#include <stdlib.h>

typedef struct RETURN
{
    int numdirectories;
    char** subnames;
}re;

re opendirectory(char* name)
{
	int subdirectories=0;
	char **names;
    struct dirent *di;  
    re r;
  
    DIR *direct = opendir(name);
  
    if (direct == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory: " );
    }
    while ((di = readdir(direct)) != NULL)
    {
        if ((strcmp(di->d_name,".")==0) || (strcmp(di->d_name,"..")==0))
        {
            continue;
        }
        subdirectories++;
    }
    closedir(direct);

    DIR *direc = opendir(name);
    //printf("%d\n",subdirectories);
    names =(char**)malloc(subdirectories*sizeof(char*));
    int i=0;
    while ((di = readdir(direc)) != NULL)
    {
    	//printf("%d\n",i);
    	int siz;
    	if ((strcmp(di->d_name,".")==0) || (strcmp(di->d_name,"..")==0))
    	{
            continue;
    	}
        siz=strlen(di->d_name);
        names[i] = malloc((siz+1)*sizeof(char));
        strcpy(names[i],di->d_name);
        //printf("%s\n",names[i]);
        i++;
    }
    //printf("%d\n",i);
    closedir(direc);

    r.numdirectories = subdirectories;
    r.subnames = names;
    return r;
}