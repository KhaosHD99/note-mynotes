#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "CDivider.cpp"
#include "CUniter.cpp"
using namespace std; 
//#define MAX 30

//#define MAX_PATH 260

void Option()
{
     printf("\n\t\t                    udfile\n");
     printf("\n\t\t***********************************************");
     printf("\n\t\t*           1--------Divide                   *");
     printf("\n\t\t*           2--------Unite                    *");
     printf("\n\t\t*           0--------Exit                     *");
     printf("\n\t\t***********************************************");
     printf("\n\n\t\t Please select :  ");
}

FILE *OpenFile()
{
   int ch;
   FILE* fp;
   char fname[50];
   printf("Enter the filename£º");
   scanf("%s",fname);
   fp=fopen(fname,"r");
   if(fp==NULL)
   {
      printf("Openfile error!\n");
	  exit(1);
   }
  
   return fp;
}



int main()
{  
    char *filename = (char *)malloc(10);
    char *savepath = (char *)malloc(10);
	int i=1;
    int choice;
	   
    while (i)
	{	
	   Option();
	   scanf("%d",&choice);
	      switch(choice)
		  {
		     case 1: 
		     	     {
			 	        printf("Enter the filename you want to split: ");
					    scanf("%s",filename);
					 
					    printf("Enter the savepath: ");
					    scanf("%s",savepath);
					    
			   	        CDivider cdivider(filename,savepath,3);
					    cdivider.Divide();
		     	     }
			         break;
					   
			 case 2: 
                     {
					 	printf("Enter the divided file directory: ");
					    scanf("%s",savepath);
					 
					    printf("Enter the filepath you want to save: ");
					    scanf("%s",filename);
						CUniter cuniter(savepath,filename);
					    cuniter.Unite();
					 }
					 break;
					 
			 
			 case 0: i=0;
				     break;
	
		  }
	}
}


