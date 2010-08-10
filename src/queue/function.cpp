#include<stdio.h>
#include<stdlib.h>
#include<iostream>

typedef struct queuenode
{  
   int data;                                   
   struct queuenode *next;                                 
};

typedef struct
{
   queuenode *front;
   queuenode *rear;        
}queue;

class TestClass
{
   public:
   queue *InQueue(queue *q)                                             
   {  
      if(q == NULL)
         q = new queue();
      queuenode *p = new queuenode();
      int x ; 
      printf("\n\t\t Please Enter an integer£º");
      scanf("%d",&x);
   
      p->data = x;
      p->next = NULL;
   
      if(q->front == NULL)
      {
         q->front = p;
         q->rear = p;
      }
      else
      {
         q->rear->next = p;
         q->rear = p;
      }
      return q;
   };
   
   void OutQueue(queue *q)                                          
   {  
      if(q == NULL)
         return ;
      queuenode *p = q -> front;
      int i  = p->data;
      q->front = p->next;
      free(p);
      p = NULL;
      cout << "OutQueue is:" << i <<endl;    
   }

   void ShowQueue(queue *q)                                           
   {  
      if(q == NULL)
      {
         cout << "q is null" <<endl;
         return;
    }
    queuenode *p = q->front;
     
    while(p)
    {
       cout << "\n\t\t " << p->data <<endl;
       p = p->next;  
    }
}    

};
