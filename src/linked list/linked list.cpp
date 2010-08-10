#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define MAXLEN 10
using namespace std;

typedef struct listnode
{  
   int data;                                   
   struct listnode *next;                                 
};

typedef struct
{
   listnode *head;       
}list;

void IniList()                                            
{  
   list *l = NULL;           
}

list *AddElement(list *l)
{
   if(l == NULL)
      l = new list();
   listnode *node = new listnode();
   int x ; 
   printf("\n\t\t Please Enter an integer£º");
   scanf("%d",&x);
   
   node->data = x;
   node->next = NULL;
   
   if(l->head == NULL)
      {
         l->head = node;
      }
      else
      {
         node->next = l->head;
         l->head = node;
      }
      return l;
}

list *AddElementToSpecPos(list *l)
{
        
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
   printf("\n\t\t Enter an integer element you want to delete£º");
   scanf("%d",&x);
   
   while(1)
   {
      if(p->data == x)
      {
           
      }
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

void ShowList(list *l)
{
   if(l == NULL)
      return;
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
  // if(q == NULL)
  //    return -1;
 //  int i = 0;
   
  // queuenode *p = q->front;
  // while(p)
  // {
    //  i++;
  //    p = p->next;       
  // }
  // k=q->rear-q->front;
  // return i;
}

void QuickSort(int *pData,int left,int right)
{
    int i,j,middle,iTemp;
    middle=pData[(left+right)/2];
    middle=pData[(rand()%(right-left+1))+left]; 
    do
    {
       while((pData[i]<middle)&&(i<right))
          i++;
       while((pData[j]>middle) && (j>left))
          j--; 
       if(i<=j)
       { 
          iTemp=pData[j];
          pData[j]=pData[i];
          pData[i]=iTemp;
          i++;           
          j--;       
       }
    }while(i<=j);
         
    if(left<j)
    {
       QuickSort(pData,left,j);
    }
    if(right>i)
    {
       QuickSort(pData,i,right);
    }                           
}

void Option()
{
     system("cls");
     printf("\n\t\t                    linked list\n");
     printf("\n\t\t***********************************************");
     printf("\n\t\t*          1--------Add element               *");
     printf("\n\t\t*          2--------Add element to spec pos   *");
     printf("\n\t\t*          3--------Delete spec element       *");
     printf("\n\t\t*          4--------Search element            *");
     printf("\n\t\t*          5--------Quick sort                *");
     printf("\n\t\t*          5--------Show all elements         *");
     printf("\n\t\t*          0------------Exit                  *");
     printf("\n\t\t***********************************************");
     printf("\n\n\t\t Please select :  ");
}

int main()                                               
{  
   int i=1;
   int choice;
   
   //IniList();
   list *l = NULL; 
  // TestClass testClass;
   
   while (i)
   { 	
		Option();
		scanf("%d",&choice);
		switch(choice)
		{
		   case 1: l = AddElement(l);
                   system("pause");break;
                   
		   case 2: AddElement(l); 
                   system("pause");break;
                   
		   case 3: ShowList(l); 
                   system("pause");break;
                   
		   case 4: SearchSpecElement(l);
                   system("pause");break;
           
           case 5: QuickSort();
                   system("pause");break;
		   case 0: i=0; break;
		}
   }
}
