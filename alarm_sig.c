#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void  myfun(int signo){
	if(signo==SIGALRM){
		printf("\n Caught Alaram \n");
		exit(EXIT_SUCCESS);
	}
}
int main(){
	printf("\n Process id: %d\n",getpid());
	signal(SIGALRM,myfun);
	alarm(2);
	while(1);
}
