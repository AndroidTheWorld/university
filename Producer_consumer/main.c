#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<stdbool.h>
#define MAX_LINE 256

int bufferSize;
int x,y;
int numP,numC;

/* ����ѭ������ */ 
typedef struct{
	int *numArray;	//����
	int font;		//�����ײ� 
	int rear;		//����β�� 
	int capacity;	//�����ܳ��� 
	int size;		//������Ԫ�ظ��� 
}queueArray;

/* ���建���� */ 
typedef struct{
	queueArray* bufferArray;		//ѭ�����ж��� 
	pthread_mutex_t producerLock;	//�����̻߳����� 
	pthread_mutex_t consumerLock;	//�����̻߳����� 
	int producerSleep;				//�����߳�˯��ʱ�� 
	int consumerSleep;				//�����߳�˯��ʱ�� 
}buffer;


/* ����ѭ�����У�������ʼ�� */ 
queueArray* createQueueArray(int len){
	queueArray* queue=(queueArray*)malloc(sizeof(queueArray));	//ѭ�����з���ռ� 
	queue->font		=0;		//��ʼ������0 
	queue->rear		=0;		//��ʼ����β0 
	queue->capacity	=len;	//��ʼ�����д�СbufferSize 
	queue->size		=0;		//��ʼ������Ԫ�ظ�ʽ0 
	queue->numArray=(int*)malloc(len*sizeof(int));	//Ϊ����Ԫ�ط���ռ� 
	return queue; 	//���ض���ָ�� 
}

/* ��ն��У�δʹ�ã� */  
void clearQueueArray(queueArray* queue){
	queue->font=0;
	queue->rear=0;
	queue->size=0;
}

/* �ж϶����Ƿ�Ϊ�� */ 
bool isEmpty(queueArray* queue){
//	printf("Queue Size:[%d]\n",queue->size);
//	printf("Queue capacity:[%d]\n",queue->capacity);
	if (queue->size==0) return true;
	return false;
}

/* �ж϶����Ƿ����� */ 
bool isFull(queueArray* queue){
//	printf("Queue Size:[%d]\n",queue->size);
//	printf("Queue capacity:[%d]\n",queue->capacity);
	if (queue->size==queue->capacity) return true;
	return false;
}

/* ��ѭ��������д������ */ 
int writeQueueArray(queueArray* queue,int num){
	if (isFull(queue)) return 0;
	if (queue->rear+1<queue->capacity) {
		queue->numArray[queue->rear++]=num;
	}else {
		queue->numArray[0]=num;
		queue->rear=0;
	}
	queue->size++;
	return 1;
}

/* ��ѭ�������ж�ȡ���� */ 
int readQueueArray(queueArray* queue){
	int ret=0;
	if (isEmpty(queue)) return ret;
	if (queue->font+1<queue->capacity){
		ret=queue->numArray[queue->font];
		queue->font+1;
	}else{
		ret=queue->numArray[queue->font];
		queue->font=0;	
	}
	queue->size--;
	return ret;
}


/* ��ӡѭ���Ķ���������Ԫ�أ�debug�ã�*/ 
void fetchall(queueArray* queue){
	int i=0;
	int p;
	for (i=0,p=queue->font;i<queue->size;i++){
		if (p<queue->capacity) printf("%d\n",queue->numArray[p]);
		else {
			p=0;
			printf("%d\n",queue->numArray[p]);
		}
	}
}

/* ����ѭ�����У��ͷſռ䣨δʹ�ã�*/ 
void destroyQueueArray(queueArray* queue){
	free(queue->numArray);
	return;
}

/* ���������� */ 
buffer* createBuffer(){
	buffer* buf=NULL;
	queueArray* queue=createQueueArray(bufferSize);		//���ô���ѭ�����к��� 
	buf=(buffer*)malloc(sizeof(buffer));				//Ϊ����������ռ� 
	buf->bufferArray	=queue;							//��ʼ���������е�ѭ������ָ�� 
	buf->producerSleep	=x;								//��ʼ�������߳�˯��ʱ�� 
	buf->consumerSleep	=y;								//��ʼ�������߳�˯��ʱ�� 
	if (pthread_mutex_init(&buf->producerLock,NULL)){	//��ʼ�������߳��� 
		printf("Producer Mutex initialization failed");
	}
	if (pthread_mutex_init(&buf->consumerLock,NULL)){	//��ʼ�������߳��� 
		printf("Consumer Mutex initialization failed");
	}
	return buf;
}

/* ���ļ��л�ȡ�������б������� */ 
int getArguement(const char* filename){
	char buf[MAX_LINE];		//�����ļ���ȡ������ 
	FILE *fp=NULL;			//�����ļ�ָ�� 
	if ((fp=fopen(filename,"r"))==NULL){	//���ļ� 
		printf("Cant not read file:[%s]\n",filename);
		return 0;
	}
	if (!feof(fp)){	//���ж�ȡ�ļ��еĲ��� 
		fgets(buf,MAX_LINE,fp);
		bufferSize=atoi(buf);
		printf("The buffer size:[%d]\n",bufferSize);
		
		fgets(buf,MAX_LINE,fp);
		x=atoi(buf);
		printf("The x:[%d]\n",x);
		
		fgets(buf,MAX_LINE,fp);
		y=atoi(buf);
		printf("The y:[%d]\n",y);
		
		fgets(buf,MAX_LINE,fp);
		numP=atoi(buf);
		printf("The number of producer:[%d]\n",numP);
		
		fgets(buf,MAX_LINE,fp);
		numC=atoi(buf);
		printf("The number of consumer:[%d]\n",numC);
	}
	return 1;
	
}

/* �������̺߳��� */ 
void* producer(void* args){
	int num;
	buffer* buf=(buffer*)args;	//������ʽת�� 
	while(1){
		pthread_mutex_lock(&buf->producerLock);	//�̼߳��� 
		srand((unsigned)time(NULL));			//��ʼ����������� 
		num=rand()%100000000;					//��������� 
		if (writeQueueArray(buf->bufferArray,num)){			//�����򻺳���д�������� 
			printf("Generate number [%d] and writed\n",num);
		}else{
			printf("Buffer is full wait for consumer\n");
		}
		pthread_mutex_unlock(&buf->producerLock);	//�߳̽��� 
		sleep(buf->producerSleep);	//�߳�˯�� 
	}
}

/* �������̺߳��� */ 
void* consumer(void* args){
	int num;
	buffer* buf=(buffer*)args;	//������ʽת�� 
	while (1){
		pthread_mutex_lock(&buf->consumerLock);		//�߳����� 
		num=readQueueArray(buf->bufferArray);		//���Դӻ�������ȡ���� 
		if (num==0){			
			printf("buffer is empty wait for producer\n");
		}else{
			printf("Read from buffer number:[%d]\n",num);
		}
		pthread_mutex_unlock(&buf->consumerLock);	//�߳̽��� 
		sleep(buf->consumerSleep);	//�߳�˯�� 
	}
}

/* ���������������߳� */ 
pthread_t* createThreads(buffer* buf){
	int i;
	//Ϊ���������̳߳ط���ռ� 
	pthread_t* threads=(pthread_t*)malloc(numP*sizeof(pthread_t)+numC*sizeof(pthread_t));
	
	for (i=0;i<numP;i++){	//���������߳� 
		if (pthread_create(&threads[i],NULL,producer,buf)){
			printf("Producer thread [%d] field\n",i+1);
		}else printf("Producer thread [%d] created\n",i+1);
	}
	
	for (;i<numC+numP;i++){	//���������߳� 
		if (pthread_create(threads+i,NULL,consumer,buf)){
			printf("Consumer thread [%d] field\n",i+1);
		}else printf("Consumer thread [%d] created\n",i+1);
	}
	return threads;	//�����̳߳ص�ַ 
}

/* �̵߳ȴ� */ 
void threadWait(pthread_t* threads){
	int i;
	for (i=0;i<numP+numC;i++)
		pthread_join(threads[i],NULL);
}


/* ������ */ 
int main(int argc,char* argv[]){
	buffer* buf=NULL;		//����������ָ�� 
	pthread_t* threads=NULL;//�����̳߳�ָ�� 
	if (argc<=1){			//�ж��Ƿ������д������ 
		printf("Please input a argument file path!");
		return 0;
	}
	getArguement(argv[1]);	//�������в����ļ���ַ�л�ȡ�������u 
	buf=createBuffer();		//���������� 
	threads=createThreads(buf);	//�����̳߳� 
	threadWait(threads);		//�̵߳ȴ� 
	
	return 0;
}
