#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

#define BUFF_SIZE 100
#define READ_END 0
#define WRITE_END 1

int main(){
	char str[BUFF_SIZE]="Hello this is forst pipe half duplex program";
	char rr[BUFF_SIZE];
	int pi[2];
	pid_t pro;
	if(pipe(pi)==-1){
		perror("pipe failed \n");
	}
	pro=fork();
	if(pro<-1){
		perror("error fork failed \n");
	}
	else if(pro==0){
		close(pi[WRITE_END]);
		read(pi[READ_END],rr,BUFF_SIZE);
		printf("child: %s",rr);
		close(pi[READ_END]);
	}
	else{
		close(pi[READ_END]);
		write(pi[WRITE_END],str,strlen(str)+1);
		close(pi[WRITE_END]);
	}
	printf("\ndone\n");
	return 0;

}
