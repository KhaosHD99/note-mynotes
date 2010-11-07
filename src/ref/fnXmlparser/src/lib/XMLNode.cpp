// XMLNode.cpp: implementation of the CXMLNode class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/fcntl.h>
#include <sys/stat.h>  
#include <dirent.h> 
#include <errno.h> 
#include <unistd.h>
#include <termios.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <math.h>
#include <time.h>


#include "XMLNode.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
char g_szAttributeValue[PROPERTY_LEN + 4] = {0};
/************************************************************************
字母转换小写函数 StrToLower

参数:
cStr	字符串
nLen	字串长

返回:
	无
备注:
1、本函数用于将字符串中大写字母转换为小写字母.
************************************************************************/
void CXMLNode::StrToLower(char *cStr, int nLen)
{
	int i = 0;
	for(; i < nLen && cStr[i]; i++)
	{
		if(cStr[i] >= 'A'  && cStr[i] <= 'Z')
		{
			cStr[i] += 32;
		}
	}
}
char *CXMLNode::TrimSpace(char *cText)
{

	while(*cText == ' ' || *cText == '\t' || *cText == '\r' || *cText == '\n')
	{
		cText++;
	}
	return cText;
}
int fn_isalpha(int nChar)
{

	if(nChar >= 'A' && nChar <= 'Z' || nChar >= 'a' && nChar <= 'a')
	{
		return 1;
	}
	return 0;
}
//不区分大小写,比较字符串
int fn_strncmp(char *szInfo1, char *szInfo2, int nLen)
{
	if(nLen <= 0)
	{
		return 0;
	}
	unsigned char *szInnerInfo1 = (unsigned char*)szInfo1;
	unsigned char *szInnerInfo2 = (unsigned char*)szInfo2;
	int i = 0;
LOOP:
	while(szInnerInfo1[i] == szInnerInfo2[i] )
	{
		if(szInnerInfo1[i] == 0)
		{
			return 0;
		}
		if(i == nLen - 1)
		{
			return 0;
		}
		i++;
	}
	if(fn_isalpha(szInnerInfo1[i]) && fn_isalpha(szInnerInfo2[i]))//试下自写isalpha
	{
		if(abs(szInnerInfo1[i] - szInnerInfo2[i]) == 32)
		{
			i++;
			goto LOOP;
		}
		return szInnerInfo1[i] - szInnerInfo2[i];
	}
	return szInnerInfo1[i] - szInnerInfo2[i];
}
char *CXMLNode::ReadAttributeValue(char *cAttributeName)
{
	if(!cAttributeName)
	{
		return NULL;
	}
	int nLen = strlen(cAttributeName);
	if(nLen > 32)
	{
		return NULL;
	}
	char szInnerAttributeName[64] = {0};
	strcpy(szInnerAttributeName, cAttributeName);
	StrToLower(szInnerAttributeName, nLen);
	int i = 0, j = 0;
	int nPos = -1;
	while(m_cProperty[i])
	{
		if((m_cProperty[i] == cAttributeName[0] || m_cProperty[i] == szInnerAttributeName[0] - 32)
			&& (m_cProperty[i + 1] == cAttributeName[1] || m_cProperty[i + 1] == szInnerAttributeName[1] - 32)
		)
		{
			if(!fn_strncmp(&m_cProperty[i], cAttributeName, nLen))
			{
				nPos = i + nLen;
				break;
			}			
		}
		i++;
	}
	if(nPos < 0)
	{
		return NULL;
	}
	char *cTemp = TrimSpace(&m_cProperty[nPos]);
	if(*cTemp != '=')
	{
		return NULL;
	}
	cTemp++;
	cTemp = TrimSpace(cTemp);
	if(*cTemp != '\"' && *cTemp != '\'')
	{
		return NULL;
	}
	cTemp++;
	while(cTemp[j] && cTemp[j] != '\'' && cTemp[j] != '\"')
	{
		g_szAttributeValue[j] = cTemp[j];
		j++;
	}
	g_szAttributeValue[j] = 0;
	return g_szAttributeValue;
}
CXMLNode *CXMLNode::ReadChildNode(int nPos)
{
	if(!m_pFirstChildNode || nPos < -1)
	{
		return NULL;
	}
	if(nPos == -1)
	{
		nPos = m_sChildNodePos;
		if(nPos < -1)
		{
			nPos = m_sChildNodePos = 0;
		}
	}
	int n = 0;
	CXMLNode *pRead = m_pFirstChildNode;
	for(; n < nPos && pRead; n++)
	{
		pRead = pRead->m_pFirstBrotherNode;
	}
	if(n == nPos)
	{
		return pRead;
	}
	return NULL;
}
CXMLNode *CXMLNode::ReadBrotherNode(int nPos)
{
	if(!m_pFirstBrotherNode || nPos < -1)
	{
		return NULL;
	}
	
	if(nPos == -1)
	{
		nPos = m_sBrotherNodePos;
		if(nPos < -1)
		{
			nPos = m_sBrotherNodePos = 0;
		}
	}
	int n = 0;
	CXMLNode *pRead = m_pFirstBrotherNode;
	for(; n < nPos && pRead; n++)
	{
		pRead = pRead->m_pFirstBrotherNode;
	}
	if(n == nPos)
	{
		
		return pRead;
	}
	return NULL;
}
