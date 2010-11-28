#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <string.h>

static char* substr(const char*str, unsigned start, unsigned end) 
{ 
	unsigned n = end - start; 
	static char stbuf[256]; 
	strncpy(stbuf, str + start, n);
	stbuf[n] = 0; 
	return stbuf; 
}

int main(int argc, char** argv) 
{ 
	const char *pattern; 
	int x, z, lno = 0, cflags = 0; 
	char ebuf[128];
	char lbuf[256];
	char lbuf2[256];
		//lbuf[256] = "a test"; 

		regex_t reg;
	regmatch_t pm[10]; 
	const size_t nmatch = 10;
	
	/* Compile*/ 
	//pattern = argv[1]; 
	pattern = "[a-b][a-b]";
	
	z = regcomp(&reg, pattern, cflags); 
	
	if (z != 0)
	{ 
		regerror(z, &reg, ebuf, sizeof(ebuf)); 
		fprintf(stderr, "%s: pattern '%s' \n", ebuf, pattern); 
		return 1; 
	}
	
	strcpy(lbuf , "nmcab123");
	//strcpy(lbuf2, "acb123");
	z = regexec(&reg, lbuf, 10, pm, 0);
	lbuf[z - 1] = 0;
	z = regexec(&reg, lbuf, nmatch, pm, 0);
	//z = regexec(&reg, lbuf2, nmatch, pm, 0);
	if (z == REG_NOMATCH) 
	{
		printf("No Match\n");
		return;
	}
	
    int i;
	for(i = 0; i< 10; i++)
		printf("z: %d, show: %d %d\n", z, pm[i].rm_so, pm[i].rm_eo);
	//	printf("match: %s\n", substr(lbuf, pm[i].rm_so, pm[i].rm_eo));

	//printf("show: %d\n", ' ');
	#if 0
	/*  input loop*/ 
	while(fgets(lbuf, sizeof(lbuf), stdin))
	{
		++lno;
		if ((z = strlen(lbuf)) > 0 && lbuf[z-1] == '\n')
		  lbuf[z - 1] = 0;
		
		/* line */
		z = regexec(&reg, lbuf, nmatch, pm, 0);
		if (z == REG_NOMATCH) 
			continue; 
		else if (z != 0) 
		{ 
			regerror(z, &reg, ebuf, sizeof(ebuf));
			fprintf(stderr, "%s: regcom('%s')\n", ebuf, lbuf);
			return 2;
		}
		
		/* Show */ 
		for (x = 0; x < nmatch && pm[x].rm_so != -1; ++ x) 
		{ 
			if (!x) 
				printf("%04d: %s\n", lno, lbuf);
			printf("  $%d='%s'\n", x, substr(lbuf, pm[x].rm_so, pm[x].rm_eo)); 
		} 
	} 
	#endif
	
	/* release  */
	regfree(&reg); 
	
    #if 0
	char * pattern; 
	int x, z, lno = 0, cflags = 0; 
	char ebuf[128], lbuf[256]; 
	regex_t reg; 
	regmatch_t pm[10]; 
	const size_t nmatch = 10;
	
	/* 编译正则表达式*/ 
	pattern = argv[1]; 
	z = regcomp(&reg, pattern, cflags); 
	if (z != 0)
	{ 
		regerror(z, &reg, ebuf, sizeof(ebuf)); 
		fprintf(stderr, "%s: pattern '%s' \n", ebuf, pattern); 
		return 1; 
	} 
	
	/*  逐行处理输入的数据 */ 
	while(fgets(lbuf, sizeof(lbuf), stdin)) 
	{ 
		++lno;
		if ((z = strlen(lbuf)) > 0 && lbuf[z-1] == '\n') 
		  lbuf[z - 1] = 0;
		
		/* 对每一行应用正则表达式进行匹配 */ 
		z = regexec(&reg, lbuf, nmatch, pm, 0); 
		if (z == REG_NOMATCH) 
			continue; 
		else if (z != 0) 
		{ 
			regerror(z, &reg, ebuf, sizeof(ebuf));
			fprintf(stderr, "%s: regcom('%s')\n", ebuf, lbuf);
			return 2;
		}
		
		/* 输出处理结果 */ 
		for (x = 0; x < nmatch && pm[x].rm_so != -1; ++ x) 
		{ 
			if (!x) 
				printf("%04d: %s\n", lno, lbuf); 
			printf("  $%d='%s'\n", x, substr(lbuf, pm[x].rm_so, pm[x].rm_eo)); 
		} 
	} 
	
	/* 释放正则表达式  */ 
	regfree(&reg); 
	#endif
	
	return 0; 
} 
