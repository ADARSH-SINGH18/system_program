#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

#define WRITE_END 1
#define READ_END 0

void myfun(int signo){
	if(signo==SIGUSR1){
		printf("\n parent caught SIGUSR1 \n");
	}	
}

int main(int argc,char* argv[]){
	pid_t n;
	int pi[2];
	
	if(pipe(pi)==-1){
		perror("pipe failed \n");
	}
	n=fork();

	if(signal(SIGUSR1,myfun)==SIG_ERR){
		perror("\n signal catch failed\n");
		exit(EXIT_FAILURE);
	}

	if(n<0){
		perror("fork failed!\n");
	}
	else if(n>0){
		close(pi[READ_END]);
		printf("\nargc :%d\n",argc);
		for(int i=1;i<argc;i++){
			write(pi[WRITE_END],argv[i],strlen(argv[i])+1);
			printf("%d\n",i);
			pause();
		}
		close(pi[WRITE_END]);
	}
	else{
		char bff[1001];
		close(pi[WRITE_END]);
		while(1){
		ssize_t bytes_read = read(pi[READ_END],bff,1001);
		if(bytes_read <= 0){
			printf("\n fail to read \n");
			break;
		}
		bff[bytes_read]='\0';
		printf("\n Child recived : %s\n",bff);
		kill(getppid(),SIGUSR1);
		}
		close(pi[READ_END]);
		exit(EXIT_SUCCESS);
	}
}
