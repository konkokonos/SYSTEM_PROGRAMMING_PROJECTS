#include "opendirectory.h"

void child(int creadfd0,int creadfd, int cwritefd)
{	
	int nu;
	int bufferSize;
	int sizeOfBloom;
	char *sizes[2];
	int i=0;
	char sb[20];
	if ((nu = read(creadfd0,sb,40)) <= 0)
		perror("child: Sizes read error ");
	sb[nu] = '\0';
	//printf("%s\n",sb);
	char * token = strtok(sb,"#");
	while(token!=NULL)
	{
		sizes[i]=token;
		i++;
		token = strtok(NULL,"#");
	}
	//for(i=0;i<2;i++)
	//{
	//	printf("%s\n",sizes[i]);
	//}
	bufferSize = atoi(sizes[0]);
	printf("bufferSize=%d\n",bufferSize);
	sizeOfBloom = atoi(sizes[1]);
	printf("sizeOfBloom=%d\n",sizeOfBloom);

	char buff[bufferSize];
	char errmesg[bufferSize];
	int n, fd;
	re returns;
	char **filenames;
	int num_of_files;

	while ((n= read(creadfd,buff,bufferSize)) > 0)
	{
		buff[n]='\0';
		printf("Received data: %s\n",buff);
		returns = opendirectory(buff);
		num_of_files=returns.numdirectories;
		filenames = returns.subnames; //pinakas me ta file_names
		int siz = strlen(buff);
		char full_path[siz];
		strcpy(full_path,buff);
		for(int j=0;j<num_of_files;j++)
		{
			strcat(full_path,"/");
			strcat(full_path,filenames[j]);
			printf("%s\n",full_path);
			strcpy(full_path,buff);
		}

	}
	if (n < 0) 
	{
    perror("filename read");
	}
	/*if ( (fd = open(buff, 0)) <0) 
	{
		sprintf(errmesg, ":can't open, %s\n", buff);
		strcat(buff, errmesg);
		n = strlen(buff);
		if (write(cwritefd, buff, n) != n)  
			perror("child: errmesg write error");
	}
	else 
	{
		while ( (n = read(fd, buff, bufferSize)) > 0)
			if (write(cwritefd, buff, n) != n)
				perror("child: data write error");
		if (n < 0)
			perror("child: read error");
	}*/
}

char* parent(int pwritefd0,int pwritefd,int preadfd,char* input_dir,char* bufferSize,char* sizeOfBloom)
{
	char sb[40];
	strcpy(sb,bufferSize);
	int m;
	char special_character[2] ="#";
	strcat(sb,special_character);
	strcat(sizeOfBloom,special_character);
	strcat(sb,sizeOfBloom);
	m = strlen(sb);

	int n;
	int buffsize;
	buffsize = atoi(bufferSize);
	char buff[buffsize];
	strcpy(buff,input_dir);
	n = strlen(buff);

	char *message; //auto poy epistrefei se emas

	if(write(pwritefd0, sb, m) != m)
		perror("parent: buffsize write error");

	if(write(pwritefd, buff, n) != n)
		perror("parent: data write error");

	while ( (n = read(preadfd, buff, buffsize)) > 0)
	{
		//if (write(message, buff, n) != n)
		//	perror("parent: data read error \n");
		message = (char*)malloc(strlen(buff)*sizeof(char));
		strcpy(message,buff);
		if (n <0)
			perror("parent: data read error \n");
	}	

	return message;
}