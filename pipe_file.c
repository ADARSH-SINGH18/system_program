#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#define BUFF_SIZE 1001
#define READ_END 0
#define WRITE_END 1

int main(){
	FILE *fptr;
	int pi[2];
	pid_t pro;

	if(pipe(pi)==-1){
		perror("\n pipe failed!\n");
		exit(EXIT_FAILURE);

	}
	pro=fork();
	if(pro==-1){
		perror("\n fork failed!\n");
		exit(EXIT_FAILURE);	
	}
	else if(pro>0){
		fptr=fopen("file1","r");
		if(fptr==NULL){
			perror("\n file open failed!\n");
			exit(EXIT_FAILURE);
		}
		
		char bff[BUFF_SIZE];
		fgets(bff,BUFF_SIZE,fptr);
		printf("\n file 1 output : %s\n",bff);
		
		close(pi[READ_END]);
		
		write(pi[WRITE_END],bff,strlen(bff)+1);
		
		close(pi[WRITE_END]);
		fclose(fptr);
		sleep(2);
		wait(NULL);
	}
	else{
		char ss[BUFF_SIZE],
		     ans[BUFF_SIZE];
		close(pi[WRITE_END]);
		fptr=fopen("file2","w+");

		read(pi[READ_END],ss,BUFF_SIZE);
		fprintf(fptr,"%s",ss);
		printf("\n ss : %s\n",ss);
		close(pi[READ_END]);
		sleep(2);
		printf("\n output of file 2 : ");
		fclose(fptr);
		
		FILE *fptr1=fopen("file2","r");
		fgets(ans,BUFF_SIZE,fptr1);
		printf("%s\n",ans);

		fclose(fptr1);
	}
	return 0;

}
