#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "CProdCons.hpp"

CProdCons CProdCons;


void* Producer_thread(void *data)
{
   while(1)
   {
	  sleep(PRODUCER_SLEEP);
	  
	  in = in % BUFFER_SIZE;
	  CProdCons.pc_buffer->writepos = in;
	  Write(CProdCons.pc_buffer, 1);
	  ++in;
   }

   return NULL;
}

void* Consumer_thread(void *data)
{
   while(1)
   {
	  sleep(CONSUMER_SLEEP);

	  out = out % BUFFER_SIZE;
	  CProdCons.pc_buffer->readpos = out;
	  Read(CProdCons.pc_buffer);
	  printf("consumer in %d. like: \n", out);
	  ShowBuffer();
	  ++out;
   }
 
   return NULL;
}


int main(void)
{
    
	
    pthread_t pProducer;
	pthread_t pConsumer;
	int ret;

	cProdCons.Init();

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

