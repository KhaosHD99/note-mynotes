#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "CProdCons.hpp"


CProdCons :: CProdCons()
{
   in = 0;
   out = 0;
   pc_buffer = new ProdCons();
}
void CProdCons :: Init()
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

void CProdCons :: Write(ProdCons *pc_buffer, int data)
{
   sem_wait(&pc_buffer->empty_sem);
   pthread_mutex_lock(&pc_buffer->lock);
   
   pc_buffer->buffer[pc_buffer->writepos] = data;
   
   pthread_mutex_unlock(&pc_buffer->lock);
   sem_post(&pc_buffer->full_sem);	
}

//when readed ,the pos is 0
void CProdCons :: Read(ProdCons *pc_buffer)
{
	sem_wait(&pc_buffer->full_sem);
    pthread_mutex_lock(&pc_buffer->lock);

  	pc_buffer->buffer[pc_buffer->readpos] = 0;
	
	pthread_mutex_unlock(&pc_buffer->lock);
	  sem_post(&pc_buffer->empty_sem);
}

void CProdCons :: ShowBuffer()
{
   int i;
   for(i = 0; i < BUFFER_SIZE; i++)
	  printf("%d \n", pc_buffer->buffer[i]);
}

