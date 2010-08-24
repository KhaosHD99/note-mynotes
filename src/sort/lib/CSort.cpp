#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include "CSort.hpp"


list* AddElement(list *l,int x)
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
   listnode *p = l->head;
   int x ; 
   int squ = 0; 
   printf("\n\t\t Enter an integer element you want to search : ");
   scanf("%d",&x);

   listnode *prior = NULL;                               //to storage the prior pointer
   while(1)
   {
      squ++; 
      if(p->data == x)
      {
         if(prior == NULL)                               //means p is head pointer     
         {
            l->head = p->next;
	        free(p);
	        p = NULL;
	        printf("\n\t\tDelete element successfully!");
	        return;
		 }
		 if(p->next != NULL)
		 {
            prior->next = p->next;
		    free(p);
		    p = NULL;
		 }
		 else
		 {
		    prior->next == NULL;
			free(p);
		    p = NULL;
		 }
		 printf("\n\t\t Delete element successfully!");
         return;
      }
	  if(p->next == NULL)
	  {
	     printf("\n\t\tNo such a element!");
	  	 break;
	  }
	  prior = p;
      p = p->next;
   }
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
   printf("\n\t\t Enter an integer element you want to search : ");
   scanf("%d",&x);
   
   while(1)
   {
      squ++; 
      if(p->data == x)
      {
         printf("\t\t  The element is in sequence : %d",squ);
         break;
      }
	  if(p->next == NULL)
	  {
	  	 printf("\n\t\tNo such a element!");
	  	 break;
	  }
      p = p->next;
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
   printf("\n\t\t linked list is:");
   while(p)
   {
      printf("\n\t\t %d",p->data);
      p = p->next;        
   }
}

int length(list *l)
{  
   if(l == NULL)
   {
      return 0;
      printf("\t\t The list is empty!!!");
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

listnode* GetPreviousNode(listnode *ref,listnode *target)       //get the previous pointer 
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


listnode* Partition(listnode *low,listnode *high)
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
      //num++;
     // printf("\nAfter %d Sort\n",num);
      printf("\nAfter Sort\n");
      listnode *p = l->head;
      while(p)
      {
         printf("\t\t %d\n",p->data);
         p = p->next;       
      }
      // fflush(stdin);
     // cout << "low is: " << low->data << endl; 
	  //cout << "high is: " << high->data << endl; 
	 // cout << "pos is: " << pos->data << endl; 
      getchar();
      if(pos != low) 
         QuickSort(l,low,GetPreviousNode(l->head,pos));
      if(pos != high)
         QuickSort(l,pos->next,high);      
   }
}

