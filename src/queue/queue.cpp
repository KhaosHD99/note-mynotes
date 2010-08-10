#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define MAXLEN 10
using namespace std;

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

void IniQueue()                                            
{  
   queue *q = NULL;    
}



int length(queue *q)
{  
   if(q == NULL)
      return -1;
   int i = 0;
   
   queuenode *p = q->front;
   while(p)
   {
      i++;
      p = p->next;       
   }
  // k=q->rear-q->front;
   return i;
}

void Option()
{
     system("cls");
     printf("\n\t\t                      queue\n");
     printf("\n\t\t***********************************************");
     printf("\n\t\t*          1------------InQueue               *");
     printf("\n\t\t*          2------------OutQueue              *");
     printf("\n\t\t*          3------------ShowQueue             *");
     printf("\n\t\t*          4------------ShowLength            *");
     printf("\n\t\t*          0------------Exit                  *");
     printf("\n\t\t***********************************************");
     printf("\n\n\t\t Please select :  ");
}

int main()                                               
{  
   int i=1;
   int choice;
   //IniQueue();
   //TestClass testClass;
   queue *q = NULL;
   
   while (i)
   { 	
		Option();
		scanf("%d",&choice);
		switch(choice)
		{
		   case 1: q = InQueue(q);
                   system("pause");break;
                   
		   case 2: OutQueue(q); 
                   system("pause");break;
                   
		   case 3: ShowQueue(q); 
                   system("pause");break;
                   
		   case 4: printf("\n\t\t Queue lenght is: %d \n",length(q));
                   system("pause");break;
                   
		   case 0: i=0; break;
		}
   }
}


