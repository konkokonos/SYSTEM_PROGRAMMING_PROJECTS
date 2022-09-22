#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include "parent_child.h"

int main(int argc, char **argv)
{	
	char* f0= argv[0];
	char* f1 = argv[1];
	char* f2 = argv[2];
	printf("MY FIFOS ARE %s, %s and %s\n",f0,f1,f2);
	int creadfd0,creadfd, cwritefd;

	if((creadfd0 = open(f0, O_RDONLY))<0)
		perror("can't open read fifo0");
	else
		printf("FIFO0 CHILD OPENED FOR READING\n");

	if((creadfd = open(f1, O_RDONLY))<0)  
		perror("can't open read fifo");
	else
		printf("FIFO1 CHILD OPENED FOR READING\n");

	if((cwritefd = open(f2, O_WRONLY))<0) 
		perror("can't open write fifo");
	else
		printf("FIFO2 CHILD OPENED FOR WRITING\n");

	child(creadfd0,creadfd, cwritefd);

	return 0;
}