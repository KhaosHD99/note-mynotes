#include "CDivider.hpp"
#include <stdio.h>
#include <string.h>
#define MAX 30

   CDivider :: CDivider(char *filename,char *savepath,int count)
   {
       //i = j;
       p_filename = filename;
	   p_savepath = savepath;
	   m_count = count;
   };

   void CDivider :: ShowTest()
   {
      
   };

   int CDivider :: GetFileSize(char *filename)
   {
      FILE* fp;
      fp=fopen(filename,"r");
      char* data_block = new char[1];
	  int size = 0,temp = 0;
      while(temp = fread(data_block,1,100,fp))
	  {
	     size += temp;
	  };
	  printf("File size is: %d\n",size);
	  fclose(fp);
	  //rewind(fp);
	  return size;
   }
   
   void CDivider :: Divide()
   {
      //unsigned long file_size = GetFileSize(p_filename);
      unsigned long file_size = 16;
      int ch;
      FILE* fp;
      fp=fopen(p_filename,"r");
      if(fp==NULL)
      {
         printf("Openfile error!\n");
	     exit(1);
      }
	  else
	     printf("Openfile successfully!\n");
      
      unsigned long split_size = 0;
	  
	  if(file_size % m_count == 0)
	  {
		 split_size = file_size / m_count; 	   
	  }
	  else
	  {
         split_size = file_size / (m_count + 1);
	  }
      char* data_block = new char[split_size];
      FILE* fp_dst_file = NULL;
	  char split_file_name[MAX];
	  
      int num = 1;
      while(fread(data_block,split_size,1,fp))
      {
         snprintf(split_file_name,MAX,"%s/%s%d",p_savepath,p_filename,num);
		 printf("split filename is %s\n",split_file_name);
         fp_dst_file = fopen(split_file_name,"wb");
	     if(fp_dst_file == NULL)
	     {
	        printf("create split file error!\n");
		    exit(1);
	        //return -1;
	     }
	     fwrite(data_block,split_size,1,fp_dst_file);
		 printf("file %d is saved \n",num);
		 num++;
	  }
   
      fclose(fp);
	  fclose(fp_dst_file);
}
   
   
   


