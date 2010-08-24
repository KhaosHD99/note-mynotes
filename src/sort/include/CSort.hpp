#ifndef CSORT_H
#define CSORT_H
#define MAXLEN 10

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

//int num;
listnode *GetPreviousNode(listnode *ref,listnode *target);
list *AddElement(list *l,int x);
void DeleteSpecElement(list *l);
void SearchSpecElement(list *l);
void ShowList(list *l);
int length(list *l);
listnode* GetPreviousNode(listnode *ref,listnode *target);
listnode *Partition(listnode *low,listnode *high);
void QuickSort(list *l,listnode *low,listnode *high);

#endif
