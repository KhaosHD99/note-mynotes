#include "CUniter.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX 30

CUniter :: CUniter(char* savepath, char*filename)
{
   p_filename = filename;
   p_savepath = savepath;
}

char* CUniter :: GetFileName(char *filepath)
{
   while(*filepath)
   {
      filepath++;
   }

   while(*filepath != '/')
   {
      filepath--;
   }

   filepath++;
   char * file_name = filepath;
   //cout << file_name << endl;
   return file_name;
}

void CUniter :: Unite()
{
   int ch;
   int num = 1;
   char* buf = new char[1];
   char split_name[MAX];
   char unite_name[MAX];
   //snprintf(unite_name,MAX,"%s/%s","unite",p_filename);
   FILE *fp_unite = fopen(p_filename,"wt");
   FILE *fp_split = NULL;

   if(fp_unite == NULL)
   {
      printf("create unitefile fail \n");
	  exit(1);
   }
   else
   {
      printf("create unitefile successfully \n");
   }
   
   while(1)
   {
      snprintf(split_name,MAX,"%s/%s%d",p_savepath,GetFileName(p_filename),num);
      fp_split = fopen(split_name,"r");
	  if(fp_split == NULL)
	  {
	     if(num == 1)
		 	printf("there is not any divided file in this directory \n");
	     break;
	  }
      while(fread(buf,1,1,fp_split))
      {
         fwrite(buf,1,1,fp_unite);
	  }
	  printf("readed the %d splitfile \n",num);
	  fclose(fp_split);
	  num++;
   }
   fclose(fp_unite); 
}
