#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define MAXLEN 10
using namespace std;

typedef struct listnode
{  
   int data;                                   
   struct listnode *next;                                 
}listnode;

typedef struct list
{
   listnode *head;   
   listnode *tail;    
}list;

int num = 0;

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

list *AddElement(list *l,int x)
{
   if(l == NULL)
      l = new list();
   listnode *node = new listnode();
   
   node->data = x;
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

void DeleteSpecElement(list *l)
{
   if(l == NULL)
   {
      return ;
      printf("\n\t\t The list is empty!!!");
   }
   
   listnode *p = l -> head;
      int i  = p->data;
      l->head = p->next;
      free(p);
      p = NULL;
      cout << "Deleted Element is: " << i <<endl;   
}

void SearchSpecElement(list *l)
{
   if(l == NULL)
   {
      return ;
      printf("\n\t\t The list is empty!!!");
   }
   listnode *p = l->head;
   int x ; 
   int squ = 0; 
   printf("\n\t\t Enter an integer element you want to search£º");
   scanf("%d",&x);
   
   while(1)
   {
      squ++; 
      if(p->data == x)
      {
         cout << ("\t\t  The element's sequence you want to search is£º") << squ << endl;
         break;
      }
      p = p->next;
   }
}

listnode *Partition(listnode *low,listnode *high)
{
   int key = low->data;
   while(low != high)
   {
      while(low != high && high->data >= key)
      {
         high = GetPreviousNode(low,high);
      }
      if(low != high)
      {
         low->data = high->data;
         low = low->next;
      }
   
      while(low != high && low->data < key)
      {
         low = low->next;                
      }
      if(low != high)
      {
         high->data = low->data;
         high = GetPreviousNode(low,high);
      }  
   }
   low->data = key;
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
         cout << "\t\t " << p->data << endl;
         p = p->next;       
      }
      // fflush(stdin);
      cout << "low is: " << low->data << endl; 
	  cout << "high is: " << high->data << endl; 
	  cout << "pos is: " << pos->data << endl; 
      getchar();
      if(pos != low) 
         QuickSort(l,low,GetPreviousNode(l->head,pos));
      if(pos != high)
         QuickSort(l,pos->next,high);      
   }
}

void ShowList(list *l)
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
      cout << "\n\t\t " << p->data << endl;
      p = p->next;        
   }
}

int length(list *l)
{  
   if(l == NULL)
   {
      return 0;
      cout << ("\t\t The list is empty!!!") << endl;
   }
   
   int len = 0;
   listnode *p = l->head;
   while(p)
   {
      len++;
      p = p->next;
   }
   return len;
}

void Option()
{
    // system("cls");
     printf("\n\t\t                    linked list\n");
     printf("\n\t\t***********************************************");
     printf("\n\t\t*          1--------Add element               *");
     printf("\n\t\t*          2--------Delete element            *");
     printf("\n\t\t*          3--------Search element            *");
     printf("\n\t\t*          4--------Quick sort                *");
     printf("\n\t\t*          5--------Show length               *");
     printf("\n\t\t*          6--------Show list                 *");
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
   int array[] = {5,42,12,53,32,0,65,-61,24,72,10,12},k;
   for(k = 0;k < 12;k++)
   {
      l = AddElement(l,array[k]);
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
		   	       l = AddElement(l,x);
                //  system("pause");
				   break;
                   
		   case 2: ShowList(l); 
               //    system("pause");
				   break;
                   
		   case 3: SearchSpecElement(l);
                //   system("pause");
				   break;
           
           case 4: if(l != NULL)
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
                   
           case 5: cout << "\t\t the list length is: " << length(l) << endl;
                  // system("pause");
				   break;
                   
           case 6: ShowList(l);
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
