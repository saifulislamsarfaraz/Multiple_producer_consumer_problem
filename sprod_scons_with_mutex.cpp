#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<queue>
#include<stdlib.h>
#include<unistd.h>
using namespace std;


//semaphore to control sleep and wake up
sem_t empty;
sem_t full;
queue<int> q;
pthread_mutex_t lock;
int cnt = 0;

void init_semaphore()
{
	sem_init(&empty,0,5);
	sem_init(&full,0,0);
	pthread_mutex_init(&lock,0);
}

void * ProducerFunc(void * arg)
{
	printf("%s\n",(char*)arg);
	int i;

    for(int i = 0; i <5; i++){
		sem_wait(&empty);//down operation

		pthread_mutex_lock(&lock);//lock kore dibo
		sleep(1);
		q.push(cnt);
		cnt++;
		printf("producer produced item %d\n", cnt);
		pthread_mutex_unlock(&lock);
		sem_post(&full);

	}
}

void * ConsumerFunc(void * arg)
{
	printf("%s\n",(char*)arg);
	int i;
	while(true)
	{

		sem_wait(&full);

		pthread_mutex_lock(&lock);
		sleep(1);
		int item = q.front();
		q.pop();
		printf("consumer consumed item %d\n",item);
		pthread_mutex_unlock(&lock);

		sem_post(&empty);

	}
}





int main(void)
{
	pthread_t thread1;
	pthread_t thread2;

	init_semaphore();

	char * message1 = "i am producer";
	char * message2 = "i am consumer";

	pthread_create(&thread1,NULL,ProducerFunc,(void*)message1 );
	pthread_create(&thread2,NULL,ConsumerFunc,(void*)message2 );


	while(1);
	return 0;
}
