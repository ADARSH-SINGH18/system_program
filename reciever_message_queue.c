#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<mqueue.h>

int main(int argc,char **argv){
	mqd_t mq;
	struct mq_attr attr;
	ssize_t rec;
	char *msg_ptr;

	if(argc<2){
		printf("\n it only have file name : %s\n",argv[0]);
		exit(1);
	}
	mq=mq_open(argv[1],O_RDONLY | O_CREAT, 0600 ,0);
	if(mq==(mqd_t)-1){
		perror("mq_open failed!\n");
		exit(1);
	}
	if(mq_getattr(mq,&attr)==-1){
		perror("mq_getattr failed!");
		exit(1);
	}
	msg_ptr=calloc(1,attr.mq_msgsize);
	if(msg_ptr==NULL){
		perror("calloc failed\n");
		mq_close(mq);
		exit(1);
	}
	rec=mq_receive(mq,msg_ptr,attr.mq_msgsize,0);
	if(rec==-1){
		perror("mq_recive\n");
	}
	printf("\n Recived message in msg queue = (%s)\n",msg_ptr);
	return 0;
}
