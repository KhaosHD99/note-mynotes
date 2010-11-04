//#include <stdio.h>
#include <stdlib.h>
//#include <locale.h>
#include <string.h>
#include "config.h"
#include "iostream"

int main()
{	
	CConfig xmlConfig("XmlConfig.xml");
	
	//获取Author的值
	string author = xmlConfig.GetValue("Author");
	//printf("Author: %s", author);
	cout << "author: " << author <<endl;
	
	//获取Site的值
	string site = xmlConfig.GetValue("Site");
	//printf("Site: %s", site);
	cout << "site: " << site <<endl;
	
	//获取Desc的值
	string desc = xmlConfig.GetValue("Desc");
	//printf("Desc: %s", desc);
	cout << "desc: " << desc <<endl;

	
	return 0;
}

//printf ("size: %d\n", sizeof(int));
#if 0
int i;
int count = 5;
int testInt[5]= {3010102254,3010102285,3010102297,3010102248,3010102279};

//setlocale (LC_ALL, "");
qsort (testInt, count, sizeof(int), test_comp);

for (i=0; i<count; i++)
	printf ("%d\n", testInt[i]);
#endif

 
