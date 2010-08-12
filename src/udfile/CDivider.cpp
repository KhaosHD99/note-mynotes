#include "CDivider.hpp"
#include <stdio.h>

   
   //CTest(int j)
  // {
   //   i = j;
   //}
   CDivider :: CDivider(char *fname)
   {
       //i = j;
       filename = fname;
   };

   void CDivider :: ShowTest()
   {
      printf("this is a DividerClass \n");
      //printf("i value is: %d\n",i);
      printf(filename);
	  printf("\n");
   };

   void CDivider :: Divide()
   {
      int ch;
      FILE* fp;
      //char fname[50];
      //printf("Enter the filename£º");
      //scanf("%s",fname);
      fp=fopen(filename,"r");
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
   
   
   


