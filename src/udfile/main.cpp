#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "CDivider.cpp"
using namespace std; 
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
   //while((ch = getc(fp)) != EOF)
   //putchar(ch);
   // fclose(fp);
   return fp;
}

void Divide()
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
   // while((ch = getc(fp)) != EOF)
   //  putchar(ch);
   unsigned long file_size = 5;
   unsigned long FILE_SIZE = file_size;
   char* data_block = new char[file_size];
   FILE* dst_file = NULL;
   int read_element_num = 0;
   
   if((read_element_num = fread(data_block,5,1,fp)) != 0)
   {
   	  printf("\n get right size");
	  printf("\n read_element_num is: %d \n",read_element_num);
   }
   else
   {
      printf("\n can't get right size");
	  printf("\n read_element_num is: %d \n",read_element_num);
	  exit(1);
   }
  // snprintf(split_file,MAX_PATH,"%s%04d",dest_file,count++);
   dst_file = fopen("divide01","wb");
	  if(dst_file == NULL)
	  {
	     printf("open %s error!\n");
		 exit(1);
	     //return -1;
	  }
	  fwrite(data_block,file_size,1,dst_file);
	  fclose(dst_file);
}


const char *GetFliename()
{
   const char *pname = "filename";
   return pname;
}

int main()
{  
   // const char *filename = GetFliename();
    char filename[] = "testfile";
    CDivider cdivider(filename);
	cdivider.Divide();
	
   // OpenFile();
     //Divide();
     
	/*   int i=1;
	   int choice;
	   
	   list *l = NULL; 

	   while (i)
	   {	
			Option();
			scanf("%d",&choice);
			switch(choice)
			{
			   case 1: 
			   	
					   break;
					   
			   case 2: ShowListWithTag(l); 
				  
					   break;
					   
			   case 3: 
					
					   break;
					   
			   case 0: i=0;
					   break;
	
			}
	   }*/
}


/*void unfile()
{
   
   int opt = 0;
	   char* optstr = NULL;
   
	   char* program_name = argv[0];
	   char* p = strchr(program_name,'.');
	   if(p == NULL)
	   {
	   }
	   else
	   {
		   *p = 0;
	   }
	   
	   char source_file[MAX_PATH] = {0};
	   char dest_file[MAX_PATH] = {0};
   
	   unsigned long file_size = 1024*1024;//1M
	   unsigned long FILE_SIZE = file_size;
   
	   //the default source file name is the same as program name but ext
	   //the destination file name is the same as program name but ext.
	   snprintf(source_file,MAX_PATH,"%s.src",program_name);
	   snprintf(dest_file,MAX_PATH,"%s.dst",program_name);
   
	   while((opt = getopt(argc,argv,"s:d:n:")) != -1)
	   {
		   switch(opt)
		   {
			   case 's':
				   snprintf(source_file,MAX_PATH,"%s",optarg);
				   break;
			   case 'd':
				   snprintf(dest_file,MAX_PATH,"%s.part",optarg);
				   break;
			   case 'n':
				   file_size = atol(optarg);
				   FILE_SIZE = file_size;
				   break;
			   default:
				   printf("invalid options!\n");
		   }
   
	   }
	   
	   FILE* src_file = fopen(source_file,"rb");
	   if(src_file == NULL)
	   {
		   printf("open %s file error!\n",source_file);
		   return -1;
	   }
	   
	   char* data_block = new char[file_size];
	   FILE* dst_file = NULL;
	   char split_file[MAX_PATH];
	   unsigned int count = 0;
   
	   //write the same size file
	   while((file_size = fread(data_block,1,FILE_SIZE,src_file)) == FILE_SIZE)
	   {
		   snprintf(split_file,MAX_PATH,"%s%04d",dest_file,count++);
		   dst_file = fopen(split_file,"wb");
		   if(dst_file == NULL)
		   {
			   printf("open %s error!\n");
			   return -1;
		   }
		   fwrite(data_block,1,file_size,dst_file);
		   fclose(dst_file);
	   }
   
	   //write the last block data 
	   snprintf(split_file,MAX_PATH,"%s%04d",dest_file,count);
	   dst_file = fopen(split_file,"wb");
	   if(dst_file == NULL)
	   {
		   printf("open %s error!\n");
		   return -1;
	   }
	   fwrite(data_block,1,file_size,dst_file);
	   fclose(dst_file);
   
	   delete[] data_block;
	   //close the source file
	   fclose(src_file);
   
       return 0;
}*/


