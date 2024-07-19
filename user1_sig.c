#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

void myfun(int signo){
	if(signo==SIGUSR1){
		printf("\n parent caught user1 \n");
	}
}

int main(){
	int status=0;
	pid_t n;
	n=fork();
	if(n==-1){
		perror("Fork Fail\n");
		exit(EXIT_FAILURE);
	}	
	else if(n==0){
		printf("\n This is child before user2 call with id %d\n",getpid());
		execl("./user2_sig","arg1","arg2",NULL);
		exit(0);
	}
	else{
		if(signal(SIGUSR1,myfun)==SIG_ERR){
			perror("Failed\n");
			exit(EXIT_FAILURE);
		}
		printf("\n Parent befor wait, child created by parent is : %d\n",n);
		sleep(2);
		kill(n,SIGUSR2);
		n=wait(&status);
		printf("\n Parent wait() is done parent id%d\n",getpid());
		printf("\n parent child id : %d\n",n);
		printf("\n parent status is : %d\n",status);
	}
	return 0;
}
