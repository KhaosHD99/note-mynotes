#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "CSort.hpp"
//using namespace std;


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
  // num = 0; 
   list *l = NULL; 

   //Add the test data
   int array[] = {5,42,12,53,32,0,65,-61,24,72,10,12},k;
   for(k = 0;k < 12;k++)
   {
      l = AddElement(l,array[k]);
   }
   printf("\n\nFor convenience,array{5,42,12,53,32,0,65,-61,24,72,10,12} has been added to the list");
 
   while (i)
   { 	
		Option();
		scanf("%d",&choice);
		switch(choice)
		{
		   case 1: int x ; 
                   printf("\n\t\t Enter an integer :  ");
                   scanf("%d",&x);
		   	       l = AddElement(l,x);
                   break;
                   
		   case 2: DeleteSpecElement(l); 
                   break;
                   
		   case 3: SearchSpecElement(l);
                   break;
           
           case 4: if(l != NULL)
                   {
                     // num = 0; 
                      listnode *low = l->head;
                      listnode *high = l->tail;
                      QuickSort(l,low,high);
                   }
                   else
                   {
                      printf("the list is empty");    
                   }
                   break;
                   
           case 5: printf("\t\t the list length is: %d \n",length(l));
                   break;
                   
           case 6: ShowList(l);
                   break;
                   
           case 0: i=0;
		           break;

		  // default: cout << "invalid number!!!" << endl;
		  //         fflush(stdin);
		  //         break;
		   	       
		}
   }
}
