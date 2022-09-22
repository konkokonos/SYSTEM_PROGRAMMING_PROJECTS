#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include <sys/stat.h>
#include<string.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <parent_child.h>
#include <Commands.h>

int main(int argc, char **argv)
{
	int numMonitors;
	char* bufferSize;
	char* sizeOfBloom;
	char* input_dir;

	pid_t childpid;
	char myfifo[7] = "fifo";
	int execl_return;
	int pwritefd0,pwritefd,preadfd;

	if (argc == 9)
	{
		for(int i=0; i<9; i++)
		{
			if(strcmp(argv[i],"-m") ==0)
				numMonitors=atoi(argv[i+1]);
			if(strcmp(argv[i],"-b") ==0)
				bufferSize=argv[i+1];
			if(strcmp(argv[i],"-s") ==0)
				sizeOfBloom=argv[i+1];
			if(strcmp(argv[i],"-i") ==0)
				input_dir=argv[i+1];
		}
	}
	printf("numMonitors has value: %d\n",numMonitors);
	printf("bufferSize has value: %s\n",bufferSize);
	printf("sizeOfBloom has value: %s\n",sizeOfBloom);
	printf("input_dir has value: %s\n",input_dir);
	printf("///////////////////////////////////////////////////////////////////\n");

	re returns;
	char **subdirnames,**filenames;
	int num_of_subdir,num_of_files;

	returns = opendirectory(input_dir);
	num_of_subdir = returns.numdirectories;
	subdirnames = returns.subnames;

	char dire[strlen(input_dir)];

	char **full_path_names;
	full_path_names =(char**)malloc(num_of_subdir*sizeof(char*));

	for(int i=0;i<num_of_subdir;i++)
	{
		strcpy(dire,input_dir);
		strcat(dire,"/");
		strcat(dire,subdirnames[i]);
		full_path_names[i]= malloc((strlen(dire)+1)*sizeof(char));
		strcpy(full_path_names[i],dire);
		//printf("%s\n",full_path_names[i]);
	}

	//for(int i=1;i<=numMonitors;i++)
	//{
	//	for(int j=i-1;j<num_of_subdir;j=j+numMonitors)
	//	{
	//		printf("%s,",full_path_names[j]);
	//	}
	//	printf("\n");
	//}
	
	printf("///////////////////////////////////////////////////////////////////\n");
	
	char *fifos[2*numMonitors+1];

	for(int i=0;i<2*numMonitors+1;i++)
	{
		sprintf(myfifo, "fifo%d", i);
		if((mkfifo(myfifo,0666)<0))
			perror("can't create fifo");

		fifos[i]=malloc(10*sizeof(char));
		strcpy(fifos[i],myfifo);
	}

	char** messages=NULL;
	messages =(char**)malloc(numMonitors*sizeof(char*));

	for(int i=0;i<numMonitors;i++)
	{
		char* f0 = fifos[0];
		char* f1 = fifos[2*i+1];
		char* f2 = fifos[2*i+2];
		childpid=fork();
		if(childpid<0)
			printf("FAILED TO FORK\n");
		else if(childpid == 0)
		{
			printf("Im the child process with ID:%lu and my fathers ID:%lu\n",(long)getpid(),(long)getppid());
			execl_return=execl("./Monitor",f0,f1,f2,NULL);
			if(execl_return==-1)
				printf("Yparxei problhma sthn execl tou ./Monitor");
		}
		else
		{
			int preadfd,pwritefd,pwritefd0;

			if((pwritefd0 = open(f0, O_WRONLY))<0)
				perror("can't open write fifo");
			else
				printf("FIFO0 PARENT OPENED FOR WRITING\n");

			if((pwritefd = open(f1, O_WRONLY))<0)
				perror("can't open write fifo");
			else
				printf("FIFO1 PARENT OPENED FOR WRITING\n");

			if((preadfd = open(f2, O_RDONLY))<0) 
				perror("can't open read fifo");
			else
				printf("FIFO2 PARENT OPENED FOR READING\n");
			for(int j=i;j<num_of_subdir;j=j+numMonitors)
			{
				//printf("%d\n",j);
				close(preadfd);
				char* message1=NULL;
				message1 = parent(pwritefd0,pwritefd,preadfd,full_path_names[j],bufferSize,sizeOfBloom);
				//printf("%s",message1);
				sleep(1);
			}

			close(pwritefd);
			close(pwritefd0);

			wait(NULL);

        	//messages[i] = malloc((siz+1)*sizeof(char));
        	//strcpy(messages[i],message);
        	
			if(i == (numMonitors-1))
			{
				if ( unlink(f0) < 0) 
				perror("parent: can't unlink \n");
			}
			
			if ( unlink(f1) < 0) 
				perror("parent: can't unlink \n");
			if ( unlink(f2) < 0) 
				perror("parent: can't unlink \n");
		}
	}
	
	//for(int i=0;i<numMonitors;i++)
	//	{
	//		printf("%s",messages[i]);
	//	}

	commands();
	
	return 0;
}

