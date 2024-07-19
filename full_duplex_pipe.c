#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define BUFF_SIZE 100
#define READ_END 0
#define WRITE_END 1

int main(){
	char str[BUFF_SIZE]="This is second programe for pipe ",
	     rr[BUFF_SIZE],
	     ss[BUFF_SIZE];
	int pi[2],
	    pp[2];
	pid_t n;
	
	if(pipe(pi)==-1){
		perror("\n pipe1 failed! \n");
	}
	if(pipe(pp)==-1){
		perror("\n pipe2 failed! \n");
	}
	
	n=fork();

	if(n<0){
		perror("\n fork failed \n");
	}
	else if(n>0){
		close(pi[READ_END]);
		close(pp[WRITE_END]);
		
		write(pi[WRITE_END],str,strlen(str)+1);
		wait(NULL);
		read(pp[READ_END],ss,BUFF_SIZE);
		printf("\n parent: child modified string %s",ss);
		
		close(pi[WRITE_END]);
		close(pp[READ_END]);
	}
	else{
		close(pi[WRITE_END]);
		close(pp[READ_END]);
		
		read(pi[READ_END],rr,BUFF_SIZE);
		strcat(rr,"and it is full duplex");
		write(pp[WRITE_END],rr,strlen(rr)+1);
		
		close(pi[READ_END]);
		close(pp[WRITE_END]);
	}
}
