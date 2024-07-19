#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void*myfun(void* arg){
	char *s=(char *)arg;
	//sleep(1);
	printf("%s",s);
	return 0;
} 

int main(){
	pthread_t th1,
		  th2;
	char *s1 = "Hello first";
	char *s2 = "Hello secoand";
	pthread_create(&th1,NULL,myfun,(void *)s1);
	pthread_create(&th2,NULL,myfun,(void *)s2);	
	pthread_join(th1,NULL);
	return 0;
}
