#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void sig_handler(int signo){
	if(signo==SIGTERM){
		printf("\n Caught SIGTERM! \n");
	}
	else if(signo==SIGINT){
		printf("\n Caught SIGINT! \n");
	}
	exit(EXIT_SUCCESS);
}

int main(){
	printf("\n Process id : %d\n",getpid());
	if(signal(SIGINT,sig_handler)==SIG_ERR){
		perror("Cannot handle SIGINT  \n");
		exit(-1);
	}
	if(signal(SIGTERM,sig_handler)==SIG_ERR){
		perror("Cannot handle SIGTERM \n");
		exit(-1);
	}
	while(1);
}
