#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<mqueue.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc,char **argv){
	mqd_t mq;
	struct mq_attr attr;
	size_t msg_len;
	int msg_prio=0;

	attr.mq_flags=0;
	attr.mq_maxmsg=10;
	attr.mq_msgsize=1024;
	attr.mq_curmsgs=0;

	mq=mq_open(argv[1], O_CREAT | O_WRONLY, 0644, &attr );
	if(mq==(mqd_t)-1){
		perror("mq_open failed!");
		return 1;
	}
	printf("\n message queue mq_maxmsg = (%d)\n mq_msgsize = (%d)\n",(int)attr.mq_maxmsg,(int)attr.mq_msgsize);

	msg_len=strlen(argv[2]);
	if(msg_len>attr.mq_msgsize){
		printf("\n message is greater than message queue can handle \n");
		exit(1);
	}
	if(mq_send(mq,argv[2],msg_len,0)==-1){
		perror("\n mq_send failed! \n");
		mq_close(mq);
		exit(1);
	}
	return 0;


}
