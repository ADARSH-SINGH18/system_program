#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void myfun(int signo){
	if(signo==SIGUSR2){
		printf("\n child: caught sigusr2 \n");
	}
}

int main(int arg,char *argv[]){
	int i=0;
	printf("New process called br excel with pid : %d\n",getpid());
	if(signal(SIGUSR2,myfun)==SIG_ERR){
		perror("Failed sigusr2\n");
	}
	for(int i=0;i<arg;i++){
		printf("\n Child argv[%d] = %s\n",i,argv[i]);
	}
	sleep(5);
	printf("\n Child Sending sigusr1 to parents\n");
	kill(getppid(),SIGUSR1);
	sleep(10);
	printf("\n child exiting \n");
	return 0;
}
