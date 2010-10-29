#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h> 
#include <gtk/gtk.h>

int comp(const void *p, const void *q)
{
	return (*(int *)p - *(int *)q);
}

int main(void)
{
    #if 0
	int i;
	int count = 5;
	char *test;
	                  
	//char str[10][20] ={"–Ï", "Œ‚", "∫Œ", "¡÷", "≤Ã","≥¬","À’", "’Ú", "Ω‹", "∞°"};
    char contact_name[5][30] = {"¡÷", "∫Œ", "–Ï", "≤Ã", "Œ‚"};
    //  setlocale(LC_ALL, "zh_CN.UTF-8");
    // setlocale(LC_ALL, "");
	//setlocale(LC_ALL, "zh_CN.GB2312");

	qsort(contact_name, 5, 30, 
	     (__compar_fn_t)strcoll);
	
	for (i = 0; i < count; ++i)
	{
	    printf("before len: %d\n", strlen(contact_name[i]));
		test = g_convert (contact_name[i], -1, "UTF-8", 
	                      "GB2312",
	                      // "ISO-8859-1", 
	                      NULL, NULL, NULL);
		  
	    printf("%s, len: %d\n", test, strlen(test));

		g_free(test);
	}
	#endif
#if 0
	char contact_name[8][20] = {"¡÷", "∫Œ", "–Ï", "≤Ã", "Œ‚", "p", "o", "µÀ"};
    //setlocale(LC_ALL, "C");
	  qsort(contact_name, 8, 20, (__compar_fn_t)strcoll);
      int i;
	  
	  for(i = 0; i < 8; i++)
      {
      		if(!strcmp(contact_name[i],"¡÷"))
        	 printf("lin\n");           
		   else if(!strcmp(contact_name[i], "∫Œ"))
	       		printf("he\n");
		  else if(!strcmp(contact_name[i], "–Ï"))
			  printf("xu\n");
	      else if(!strcmp(contact_name[i], "≤Ã"))
			printf("cai\n");
		  else if(!strcmp(contact_name[i], "Œ‚"))
			printf("wu\n");
		  else if(!strcmp(contact_name[i], "µÀ"))
			printf("deng\n");
		  else 
		  	printf("%s\n",contact_name[i]);
	  }
#endif

#if 1
	const int MAX_NAME_LEN=12;
	int buf_count = 4;
	char **contact_name = new char*[buf_count];
	
	for(int i = 0; i < buf_count; i++)
	{
		contact_name[i] = new char[MAX_NAME_LEN];
	}
	sprintf(contact_name[0], "%s", "a");
	sprintf(contact_name[1], "%s", "b");
	sprintf(contact_name[2], "%s", "c");
	sprintf(contact_name[3], "%s", "d");
	
	qsort(contact_name, buf_count, MAX_NAME_LEN, (__compar_fn_t)comp);
	for(int i = 0; i < buf_count; i++)
	{
		printf("%s\r\n", contact_name[i]);
	}
	
#endif

    return 0;
}
