#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;

int num = 0;

typedef struct myint
{  
   int value;                                   
   int tag;                              
}myint;

typedef struct listnode
{  
   myint data;                                   
   listnode *next;                                 
}listnode;

typedef struct list
{
   listnode *head;   
   listnode *tail;    
}list;


listnode *GetPreviousNode(listnode *ref,listnode *target)          //get the previous pointer 
{
   if(ref == target)
      return NULL; 
   while(1)
   {
      if(ref->next == target)
      {
         target = ref;
         ref = NULL;
         break;         
      }
      ref = ref->next;
   }
   return target;
}

list *AddElement(list *l,myint mi)
{
   if(l == NULL)
      l = new list();
   listnode *node = new listnode();
   
   node->data = mi;
   node->next = NULL;
   
   if(l->head == NULL)
      {
         l->head = node;
         l->tail = node;
      }
      else
      {
         node->next = l->head;
         l->head = node;
      }
      return l;
}

listnode *Partition(listnode *low,listnode *high)
{
   int key = low->data.value;
   int tagKey = low->data.tag;
   while(low != high)
   {
      while(low != high && high->data.value >= key)
      {
         high = GetPreviousNode(low,high);
      }
      if(low != high)
      {
         low->data = high->data;
         low = low->next;
      }
   
      while(low != high && low->data.value < key)
      {
         low = low->next;                
      }
      if(low != high)
      {
         high->data = low->data;
         high = GetPreviousNode(low,high);
      }  
   }
   low->data.value = key;
   low->data.tag = tagKey;
   return low;   
}

void QuickSort(list *l,listnode *low,listnode *high)
{
   if(l == NULL || low == NULL || high == NULL)
      return ;
      
   listnode *pos = NULL;
   int k;
   if(low != high)
   {
      pos = Partition(low,high);
      num++;
      cout << "\nAfter " << num << " Sort\n" << endl;
      listnode *p = l->head;
      while(p)
      {
         cout << "\t\t " << p->data.value << "  " << p->data.tag << endl;
         p = p->next;       
      }
      // fflush(stdin);
      //cout << "low is: " << low->data << endl;
	  //cout << "high is: " << high->data << endl;
	  //cout << "pos is: " << pos->data << endl;
      getchar();
      if(pos != low) 
         QuickSort(l,low,GetPreviousNode(l->head,pos));
      if(pos != high)
         QuickSort(l,pos->next,high);      
   }
}


void ShowListWithTag(list *l)
{
   if(l == NULL)
   {
      return ;
      printf("\n\t\t The list is empty!!!");
   }
   listnode *p = l->head;
   cout << "\n\t\t linked list is:" << endl;
   while(p)
   {
      cout << "\n\t\t " << p->data.value << "  " << p->data.tag << endl;
      p = p->next;
   }
}

void Option()
{
    // system("cls");
     printf("\n\t\t                    stable list\n");
     printf("\n\t\t***********************************************");
     printf("\n\t\t*          1--------Add element               *");
     printf("\n\t\t*          2--------Delete element            *");
     printf("\n\t\t*          3--------Quick sort                *");
     printf("\n\t\t*          4--------Show list with tag        *");
	 printf("\n\t\t*          0------------Exit                  *");
     printf("\n\t\t***********************************************");
     printf("\n\n\t\t Please select :  ");
}

int main()                                               
{  
   int i=1;
   int choice;
   
   list *l = NULL; 

   //Add the test data
   int array[] = {5,42,12,53,32,0,65,-61,24,72,10,12},k,tag = 1;     
   //int array[] = {5,42,12,53,12,0,65,-61,24,72,10,32},k,tag = 1;
   myint mi;
   for(k = 0;k < 12;k++)
   {
      mi.value = array[k];
	  if(array[k] == 12)
	  {
	  	mi.tag = tag;
		tag++;
	  }
	  else
	  	mi.tag = 0;
      l = AddElement(l,mi);
   }

   
   cout << "\n\nFor convenience,array{5,42,12,53,32,0,65,-61,24,72,10,12} has been added to the list" << endl;
 
   while (i)
   { 	
		Option();
		scanf("%d",&choice);
		switch(choice)
		{
		   case 1: int x ; 
                   printf("\n\t\t Please Enter an integer£º");
                   scanf("%d",&x);
				   myint mi;
				   mi.value = x;
				   mi.tag = 0;
		   	       l = AddElement(l,mi);
                //  system("pause");
				   break;
                   
		   case 2: ShowListWithTag(l); 
               //    system("pause");
				   break;
                   
		   case 3: if(l != NULL)
                   {
                      num = 0; 
                      listnode *low = l->head;
                      listnode *high = l->tail;
                      QuickSort(l,low,high);
                   }
                   else
                   {
                      cout << "the list is empty" << endl;    
                   }
                 //  system("pause");
				   break;
                   
           case 4: ShowListWithTag(l);
                  // system("pause");
				   break;
				  
           case 0: i=0;
		           break;

		  // default: cout << "invalid number!!!" << endl;
		  //         fflush(stdin);
		  //         break;
		   	       
		}
   }
}

