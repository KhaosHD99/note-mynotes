#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define PRODUCER_SLEEP 1
#define CONSUMER_SLEEP 2

typedef struct ProdCons 
{
  int buffer[BUFFER_SIZE];
  pthread_mutex_t lock; 
  int readpos, writepos;
  sem_t empty_sem;
  sem_t full_sem;
  //pthread_cond_t notempty;
  //pthread_cond_t notfull;
}ProdCons;

int in = 0;
int out = 0;	
ProdCons *pc_buffer = new ProdCons();

void Init()
{
   //Init the  semaphore
    int ini1 = sem_init(&pc_buffer->empty_sem, 0, BUFFER_SIZE); 
	int ini2 = sem_init(&pc_buffer->full_sem, 0, 0);  
	if(ini1 || ini2 != 0)
	{
	   printf("cond init failed \n");
	   exit(1);
	}
	else
       printf("cond init successfully! \n");
	
    //Init the mutex lock
	int ini3 = pthread_mutex_init(&pc_buffer->lock, NULL);
	if(ini3 != 0)
	{
	   printf("mutex init failed \n");
	   exit(1);
	}
	else
		printf("mutex init successfully \n");
}

void Write(ProdCons *pc_buffer, int data)
{
   pc_buffer->buffer[pc_buffer->writepos] = data;
}

//when readed ,the pos is 0
void Read(ProdCons *pc_buffer)
{
  	pc_buffer->buffer[pc_buffer->readpos] = 0;
}

void ShowBuffer()
{
   int i;
   for(i = 0; i < BUFFER_SIZE; i++)
	  printf("%d \n", pc_buffer->buffer[i]);
}

void *Producer_thread(void *data)
{
   while(1)
   {
	  sleep(PRODUCER_SLEEP);
	  
	  sem_wait(&pc_buffer->empty_sem);
	  pthread_mutex_lock(&pc_buffer->lock);
	 
	  in = in % BUFFER_SIZE;
	  pc_buffer->writepos = in;
	  Write(pc_buffer, 1);
	  ++in;
	  
	  pthread_mutex_unlock(&pc_buffer->lock);
	  sem_post(&pc_buffer->full_sem);	
   }

   return NULL;
}

void *Consumer_thread(void *data)
{
   while(1)
   {
	  sleep(CONSUMER_SLEEP);
   
	  sem_wait(&pc_buffer->full_sem);
	  pthread_mutex_lock(&pc_buffer->lock);
	 
	  out = out % BUFFER_SIZE;
	  pc_buffer->readpos = out;
	  Read(pc_buffer);
	  printf("consumer in %d. like: \n", out);
	  ShowBuffer();
	  ++out;
	  
	  pthread_mutex_unlock(&pc_buffer->lock);
	  sem_post(&pc_buffer->empty_sem);
   }
 
   return NULL;
}

int main(void)
{
    pthread_t pProducer;
	pthread_t pConsumer;
	int ret;

	Init();

	//Create the producer thread
	ret = pthread_create(&pProducer, NULL, Producer_thread, NULL);
	if(ret != 0)
	{
       printf("product creation failed \n");
	   exit(1);
	}
	else
       printf("producer thread create successfully \n");
	
    //Create the consumer thread
	ret = pthread_create(&pConsumer, NULL, Consumer_thread, NULL);
	if(ret != 0)
	{
       printf("prochase creation failed \n");
	   exit(1);
	}
	else
       printf("consumer thread create successfully \n");
	
    //join the thread
    pthread_join(pProducer,NULL);
	pthread_join(pConsumer,NULL);
	
  	return 0;
}

