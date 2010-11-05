//XMLParser.cpp: implementation of the CXMLParser class.
//
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


#include "XMLParser.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXMLParser::CXMLParser()
{
	m_pRootNode = NULL;
	m_nNum = 0;
	m_nRet = 0;
	m_cText = NULL;	
	memset(m_cInfoFlag, 0, NAME_LEN);//结点名
	memset(m_cInfoProperty, 0, PROPERTY_LEN);		
}

CXMLParser::~CXMLParser()
{


}
int CXMLParser::InitStackSpace(int nStackSpace)
{
	return m_Stack.InitStackSpace(nStackSpace);
}
int CXMLParser::LoadFile(char *szFileName)
{
	if(!szFileName)
	{
		return -1;
	}
	if(!m_Stack.m_DataList)
	{
		return -1;
	}
	int nFileLen = 0;
	int fd = 0;
	fd = open(szFileName, O_RDWR, 0);
	if(fd < 0)
	{
		printf("read open file fail %d\r\n", fd);
		return -1;
	}
			

	struct stat statdata = {0};
	fstat(fd, &statdata);
	printf("read file len %d\r\n", (int)statdata.st_size);	
	nFileLen = statdata.st_size;
	int nAllocLen = nFileLen + 1;
	int nModLen = nAllocLen % 8;
	if(nModLen)
	{
		nAllocLen += 8 - nModLen;
	}
	char *pBuf = (char*)malloc(nAllocLen);	
	if(!pBuf)
	{
		close(fd);
		return -1;
	}
	int nReadLen = read(fd, pBuf, nFileLen);
	close(fd);
	if(nReadLen != nFileLen)
	{
		free(pBuf);
		return -1;
	}
	pBuf[nFileLen] = 0;
	if(m_pRootNode)
	{
		ClearNodeTree(m_pRootNode);
		m_pRootNode = NULL;
	}
	m_pRootNode = RarseFile(pBuf);
	free(pBuf);
	if(!m_pRootNode)
	{
		return -1;
	}	
	return 0;
}
CXMLNode *CXMLParser::ReadRootNode()
{
	if(!m_pRootNode)
	{
		return NULL;
	}
	return m_pRootNode->m_pFirstChildNode;
}
char *CXMLParser::RemoveXMLDeclare(char *cText)
{
	/////////////
	//ljr
	///分析xml头标识是否正确，并去掉
	cText = TrimSpace(cText);
	if(cText[0] != '<' || cText[1] != '?')
	{
		return NULL;
	}
	cText += 2;
	while(*cText != '>')
	{
		cText++;
	}
	cText++;
	return cText;
	///////////////////////////
}
CXMLNode *CXMLParser::RarseFile(char *cText)
{
	if(!cText)
	{
		return NULL;
	}
	if(!cText[0])
	{
		return NULL;
	}
	int nLen = strlen(cText);
	LinePreProcess(cText, nLen);
	#ifdef FN_USE_SDRAM2	
		CXMLNode *pHead = (CXMLNode *)FN_alloc(SDRAM2, NODE_LEN, 8);
	#else
		CXMLNode *pHead = (CXMLNode*)malloc(NODE_LEN);
	#endif	
	
	if(!pHead)
	{
		printf("mem alloc fail\r\n");
		return NULL;
	}
	memset(pHead, 0, sizeof(CXMLNode));
	char *pRet = RemoveXMLDeclare(cText);
	if(pRet)
	{
		cText = pRet; 
	}
	int nRet = 0;
	m_cText = cText;
	nRet = ReadXMLNode(pHead);
	if(nRet < 0)
	{
		printf("analyse fail\r\n");
		//清除结点树
		ClearNodeTree(pHead);
		return NULL;
	}
	return pHead;	
}
/************************************************************************
信息预处理函数 PreProcess

参数:
cText 			信息串
nLen			信息串长度

返回:
	
备注:
1、本函数用于信息预处理,替换特殊显示信息.
************************************************************************/
int CXMLParser::PreProcess(char *cText, int nLen)
{
	cText[nLen] = 0;
	int n = 0;
	while(n < nLen)
	{
		if(cText[n] == '&')
		{
			if(cText[n + 1] == '#')
			{
				int nAsc = 0;
				sscanf(cText + n + 2, "%d", &nAsc);
				cText[n] = nAsc;
				int nDataLen = 1;
				if(cText[n + 3] >= '0' && cText[n + 3] <= '9')
				{
					nDataLen = 2;
				}
				if(cText[n + 4] >= '0' && cText[n + 4] <= '9')
				{
					nDataLen = 3;
				}
				int nInner = nLen - (n + 2 + nDataLen) + 1;
				if(nInner < 0)
				{
					nInner = 0;
				}
				memcpy(cText + n + 1, cText + n + 2 + nDataLen, nInner);
				nLen -= 1 + nDataLen;
			}			
			else if((cText[n + 1] == 'n' || cText[n + 1] == 'N') 
				&& (cText[n + 2] == 'b' || cText[n + 2] == 'B'))
			{
				//&nbsp; 空格
				cText[n] = ' ';//替换为空格
				int nDataLen = 5;
				int nInner = nLen - (n + 1 + nDataLen) + 1;
				if(nInner < 0)
				{
					nInner = 0;
				}
				memcpy(cText + n + 1, cText + n + 1 + nDataLen, nInner);
				nLen -= nDataLen;
			}			
			else if((cText[n + 1] == 'q' || cText[n + 1] == 'Q') 
				&& (cText[n + 2] == 'u' || cText[n + 2] == 'U'))
			{
				//&quot; 引号
				cText[n] = '\"';//替换为引号
				int nDataLen = 5;
				int nInner = nLen - (n + 1 + nDataLen) + 1;
				if(nInner < 0)
				{
					nInner = 0;
				}
				memcpy(cText + n + 1, cText + n + 1 + nDataLen, nInner);
				nLen -= nDataLen;
			}
			else if((cText[n + 1] == 'a' || cText[n + 1] == 'A') 
				&& (cText[n + 2] == 'm' || cText[n + 2] == 'M'))
			{
				//&amp;
				cText[n] = '&';//替换
				int nDataLen = 4;
				int nInner = nLen - (n + 1 + nDataLen) + 1;
				if(nInner < 0)
				{
					nInner = 0;
				}
				memcpy(cText + n + 1, cText + n + 1 + nDataLen, nInner);
				nLen -= nDataLen;
			}
			else if((cText[n + 1] == 'l' || cText[n + 1] == 'L') 
				&& (cText[n + 2] == 't' || cText[n + 2] == 'T'))
			{
				//&lt;
				cText[n] = '<';//替换
				int nDataLen = 3;
				int nInner = nLen - (n + 1 + nDataLen) + 1;
				if(nInner < 0)
				{
					nInner = 0;
				}
				memcpy(cText + n + 1, cText + n + 1 + nDataLen, nInner);
				nLen -= nDataLen;
			}
			else if((cText[n + 1] == 'g' || cText[n + 1] == 'G') 
				&& (cText[n + 2] == 't' || cText[n + 2] == 'T'))
			{
				//&gt;
				cText[n] = '>';//替换
				int nDataLen = 3;
				int nInner = nLen - (n + 1 + nDataLen) + 1;
				if(nInner < 0)
				{
					nInner = 0;
				}
				memcpy(cText + n + 1, cText + n + 1 + nDataLen, nInner);
				nLen -= nDataLen;
			}

			else if((cText[n + 1] == 'e' || cText[n + 1] == 'E') 
				&& (cText[n + 2] == 'u' || cText[n + 2] == 'U'))
			{
				//&euro;
				cText[n] = ':';//替换
				int nDataLen = 5;
				int nInner = nLen - (n + 1 + nDataLen) + 1;
				if(nInner < 0)
				{
					nInner = 0;
				}
				memcpy(cText + n + 1, cText + n + 1 + nDataLen, nInner);
				nLen -= nDataLen;
			}			
		}
		n++;
	}
	cText[nLen] = 0;
	return 0;
}
int CXMLParser::LinePreProcess(char *cText, int nLen)
{
	cText[nLen] = 0;
	int i = 0;
	int n = 0;
	while(n < nLen)
	{
		if(cText[n] != '\r' 
			&& cText[n] != '\n'
			&& cText[n] != '\t'
		)
		{
			cText[i++] = cText[n];
		}
		n++;
	}
	cText[i] = 0;
	return 0;
}
int CXMLParser::SpacePreProcess(char *cText, int nLen)
{
	cText[nLen] = 0;
	int i = 0;
	int n = 0;
	while(n < nLen)
	{
		if(cText[n] != ' ')
		{
			cText[i++] = cText[n];
		}
		n++;
	}
	cText[i] = 0;
	return 0;
}
/************************************************************************
结点树清除函数 ClearTree

参数:
pNode 			头结点

返回:
	无
备注:
1、本函数用于清除以pNode为头结点的信息树,通过递归调用实现清除过程.
************************************************************************/
int CXMLParser::ReleaseResource()
{
	if(!m_pRootNode)
	{
		return 0;
	}	
	int nRet = ClearNodeTree(m_pRootNode);
	m_pRootNode = NULL;
	return nRet;
}
/************************************************************************
结点树清除函数 ClearTree

参数:
pNode 			头结点

返回:
	无
备注:
1、本函数用于清除以pNode为头结点的信息树,通过递归调用实现清除过程.
************************************************************************/
int CXMLParser::ClearNodeTree(CXMLNode *pHead)
{
	if(!pHead)
	{
		return 0;
	}	
	m_Stack.Clear();
	CXMLNode *pNode = pHead;
	int nNodeFlag = 0;

	while(pNode->m_pFirstChildNode || pNode->m_pFirstBrotherNode)
	{
		//0为父结点 1为兄结点	
		if(pNode->m_pFirstChildNode)
		{
			m_Stack.Push(pNode, 0);
			pNode = pNode->m_pFirstChildNode;
		}
		else if(pNode->m_pFirstBrotherNode)
		{
			m_Stack.Push(pNode, 1);
LOOPCLEAR:				
			pNode = pNode->m_pFirstBrotherNode;
		}
		else
		{
			break;
		}
	}
DIRECTCLERA:
	#ifdef FN_USE_SDRAM2	
		MEM_free(SDRAM2, pNode, NODE_LEN);
	#else
		free(pNode);
	#endif		
	if(m_Stack.ExistData())
	{
		nNodeFlag = m_Stack.m_DataList[m_Stack.m_nNum - 1].nNodeFlag;
		pNode = m_Stack.m_DataList[m_Stack.m_nNum - 1].pPreNode;
		if(!nNodeFlag)
		{
			pNode->m_pFirstChildNode = NULL;
			if(pNode->m_pFirstBrotherNode)
			{	
				m_Stack.m_DataList[m_Stack.m_nNum - 1].nNodeFlag = 1;			
				goto LOOPCLEAR;
			}
		}
		m_Stack.Pop();
		goto DIRECTCLERA;		
	}
	return 0;
}
char *CXMLParser::TrimSpace(char *cText)
{
	while(*cText == ' ' || *cText == '\t' || *cText == '\r' || *cText == '\n')
	{
		cText++;
	}
	return cText;
}
/************************************************************************
结尾标签串长度计算函数 GetEndFlagLen

参数:
cText 			信息串

返回:
	信息长度
备注:
	1、本函数用于读取结尾标签串长度.
************************************************************************/
int CXMLParser::GetEndFlagLen(char *cText)
{
	int nLen = 0;
	while(*cText && *cText != '>' && *cText != '<')
	{		 
		cText++;
		nLen++;
	}
	if(*cText != '>')
	{
		return -1;
	}
	return nLen + 1;
}

int CXMLParser::GetSelfInfo(char *szText)
{
	int k = 0;
	while(szText[k])
	{
		if(szText[k] == '>')
		{
			if(k == 0)
			{
				return 0;
			}
			if(szText[k - 1] == '/')
			{
				return 1;
			}
			break;
		}
		k++;
	}
	return 0;
}
/************************************************************************
配对标签查找函数 FindMatchInfo

参数:
cText 			信息串
cInfoProperty	标签串
nLen			标签长度,最大为4
返回:
	匹配: 1(true)
	无匹配: 0(false)
备注:
	1、本函数用于查找标签结尾配对.
************************************************************************/
int CXMLParser::FindMatchInfo(char *cText, char *cInfoProperty, int nLen)
{
	int n = 0;
	int nCnt = 0;
	switch(nLen)
	{
	case 1:
		if(!cText[0] || !cText[1])
		{
			return 0;
		}
		while(cText[n + 1])
		{
			if((cText[n] == cInfoProperty[0] || cText[n] == cInfoProperty[0] - 32)
				&& cText[n + 1] == '>' 
				&& cText[n - 1] == '<')
			{
				//登记查到的新的同类型信息,若同类型信息总数为偶数,即为不匹配
				nCnt++;
				n += 2;
				int nMatch = GetSelfInfo(cText + n);
				if(nMatch > 0)
				{
					nCnt--;
				}				
				continue;
			}
			if(cText[n] == '/' 
				&& (cText[n + 1] == cInfoProperty[0] || cText[n + 1] == cInfoProperty[0] - 32))
			{
				//查到匹配信息
				if(!nCnt)
				{
					return 1;
				}
				nCnt--;
			}
			n++;
		}
		break;
	case 2:
		if(!cText[0] || !cText[1] || !cText[2])
		{
			return 0;
		}
		while(cText[n + 2])
		{
			if((cText[n] == cInfoProperty[0] || cText[n] == cInfoProperty[0] - 32)
				&& (cText[n + 1] == cInfoProperty[1] || cText[n + 1] == cInfoProperty[1] - 32)
				 && cText[n - 1] == '<')
			{
				//登记查到的新的同类型信息,若同类型信息总数为偶数,即为不匹配
				nCnt++;
				n += 3;
				int nMatch = GetSelfInfo(cText + n);
				if(nMatch > 0)
				{
					nCnt--;
				}				
				continue;
			}
			if(cText[n] == '/' 
				&& (cText[n + 1] == cInfoProperty[0] - 32 || cText[n + 1] == cInfoProperty[0])
				&& (cText[n + 2] == cInfoProperty[1] - 32 || cText[n + 2] == cInfoProperty[1])
				 && cText[n - 1] == '<')
			{
				//查到匹配信息
				if(!nCnt)
				{
					return 1;
				}
				nCnt--;
			}
			n++;
		}
		break;
	case 3:
		if(!cText[0] || !cText[1] || !cText[2] || !cText[3])
		{
			return 0;
		}
		while(cText[n + 3])
		{
			if((cText[n] == cInfoProperty[0] + 32 || cText[n] == cInfoProperty[0]) 
				&& (cText[n + 1] == cInfoProperty[1] - 32 || cText[n + 1] == cInfoProperty[1])
				&& (cText[n + 2] == cInfoProperty[2] - 32 || cText[n + 2] == cInfoProperty[2])
				 && cText[n - 1] == '<')
			{
				//登记查到的新的同类型信息,若同类型信息总数为偶数,即为不匹配
				nCnt++;
				n += 4;
				int nMatch = GetSelfInfo(cText + n);
				if(nMatch > 0)
				{
					nCnt--;
				}				
				continue;
			}
			if(cText[n] == '/' 
				&& (cText[n + 1] == cInfoProperty[0] - 32 || cText[n + 1] == cInfoProperty[0])
				&& (cText[n + 2] == cInfoProperty[1] - 32 || cText[n + 2] == cInfoProperty[1])
				&& (cText[n + 3] == cInfoProperty[2] - 32 || cText[n + 3] == cInfoProperty[2])
				 && cText[n - 1] == '<')
			{
				//查到匹配信息
				if(!nCnt)
				{
					return 1;
				}
				nCnt--;
			}
			n++;
		}
		break;
	case 4:
		if(!cText[0] || !cText[1] || !cText[2] || !cText[3] || !cText[4])
		{
			return 0;
		}
		while(cText[n + 4])
		{
			if((cText[n] == cInfoProperty[0] + 32 || cText[n] == cInfoProperty[0])
				&& (cText[n + 1] == cInfoProperty[1] - 32 || cText[n + 1] == cInfoProperty[1])
				&& (cText[n + 2] == cInfoProperty[2] - 32 || cText[n + 2] == cInfoProperty[2])
				&& (cText[n + 3] == cInfoProperty[3] - 32 || cText[n + 3] == cInfoProperty[3])
				 && cText[n - 1] == '<')
			{
				//登记查到的新的同类型信息,若同类型信息总数为偶数,即为不匹配
				nCnt++;
				n += 5;
				int nMatch = GetSelfInfo(cText + n);
				if(nMatch > 0)
				{
					nCnt--;
				}				
				continue;
			}
			if(cText[n] == '/' 
				&& (cText[n + 1] == cInfoProperty[0] - 32 || cText[n + 1] == cInfoProperty[0])
				&& (cText[n + 2] == cInfoProperty[1] - 32 || cText[n + 2] == cInfoProperty[1])
				&& (cText[n + 3] == cInfoProperty[2] - 32 || cText[n + 3] == cInfoProperty[2])
				&& (cText[n + 4] == cInfoProperty[3] - 32 || cText[n + 4] == cInfoProperty[3])
				 && cText[n - 1] == '<')
			{
				//查到匹配信息
				if(!nCnt)
				{
					return 1;
				}
				nCnt--;
			}
			n++;
		}
		break;
	}

	return 0;//无匹配
}

/************************************************************************
结点读取函数 ReadXMLNode   由递归改为循环

参数:
pPreNode		根结点

返回:
	正常值: >=0
	异常值: <0
备注:
	1、本函数用于读取结点树.
************************************************************************/
int CXMLParser::ReadXMLNode(CXMLNode *pPreNode)
{
	if(!m_cText || !pPreNode)
	{
		return -1;//不能解析的语法, 返回失败
	}
	m_Stack.Clear();
	m_Stack.Push(pPreNode, 0);//压入根结点
LOOP_PARSE://循环解析
	m_cText = TrimSpace(m_cText);
	if(!m_cText[0])
	{
		printf("结束返回\r\n");
		return 0;//结束返回
	}	
	if(*m_cText != '<')
	{
		return -1;
	}
	m_cText++;
	if(*m_cText == '!')//去除注释标签
	{		 
		while(*m_cText != '>')
		{
			if(!*m_cText)
			{
				printf("XML去除注释错误\r\n");
				return -1;
			}
			m_cText++;
		}
		m_cText++;
		goto LOOP_PARSE;
	}
	m_cText = TrimSpace(m_cText);

	//本次调用读完全部子结点
	if(*m_cText == '/')//无子结点,本结点收敛 上级结点收敛
	{		
		m_nNum = GetEndFlagLen(m_cText);
		m_cText = m_cText + m_nNum;

		//当前是读子结点
		if(!m_Stack.ExistData())
		{
			return -1;
		}
		if(!m_Stack.m_DataList[m_Stack.m_nNum - 1].nNodeFlag)//读子结点
		{
			m_Stack.m_DataList[m_Stack.m_nNum - 1].nNodeFlag = 1;//改读兄弟结点
			goto LOOP_PARSE;
		}
		
		do
		{
			m_Stack.Pop();
		}while(m_Stack.ExistData() && m_Stack.m_DataList[m_Stack.m_nNum - 1].nNodeFlag);//读兄弟结点

		if(!m_Stack.ExistData())
		{
			return -1;
		}
		m_Stack.m_DataList[m_Stack.m_nNum - 1].nNodeFlag = 1;//改读兄弟结点
		goto LOOP_PARSE;
	}
	//取结点名称
	m_nNum = 0;
	while(*m_cText 
		&& *m_cText != '/' 
		&& *m_cText != '>' 
		&& *m_cText != ' ' 
		&& *m_cText != '\t' 
		&& *m_cText != '\r' 
		&& *m_cText != '\n')
	{
		m_cInfoFlag[m_nNum++] = *m_cText++;
		if(m_nNum == NAME_LEN - 1)
		{
			return -1;
		}
	}
	m_cInfoFlag[m_nNum] = 0;

	m_cText = TrimSpace(m_cText);
	m_nNum = 0;
	if(*m_cText != '>' && *m_cText != '/')//含属性
	{
		//读取结点属性信息		
		while(*m_cText && *m_cText != '>' && !(*m_cText == '/' && *(m_cText + 1) == '>'))
		{
			m_cInfoProperty[m_nNum++] = *m_cText++;
			if(m_nNum == PROPERTY_LEN - 1)//需要另作处理
			{
				return  -1;
			}			
		}
		m_cInfoProperty[m_nNum] = 0;		
	}
	#ifdef FN_USE_SDRAM2	
		CXMLNode *pNode = (CXMLNode *)FN_alloc(SDRAM2, NODE_LEN, 8);
	#else
		CXMLNode *pNode = (CXMLNode*)malloc(NODE_LEN);
	#endif		
	
	if(!pNode)
	{
		return -1;
	}
	memset(pNode, 0, NODE_LEN);	

	memcpy(pNode->m_cName, m_cInfoFlag, NAME_LEN);
	if(m_nNum)
	{
		memcpy(pNode->m_cProperty, m_cInfoProperty, m_nNum);
		pNode->m_cProperty[m_nNum] = 0;
	}
	if(!m_Stack.ExistData())
	{
	#ifdef FN_USE_SDRAM2	
		MEM_free(SDRAM2, pNode, NODE_LEN);
	#else
		free(pNode);
	#endif			
		return -1;
	}

	if(!m_Stack.m_DataList[m_Stack.m_nNum - 1].nNodeFlag)
	{
		m_Stack.m_DataList[m_Stack.m_nNum - 1].pPreNode->m_pFirstChildNode = pNode;//连入父结点
	}
	else
	{
		m_Stack.m_DataList[m_Stack.m_nNum - 1].pPreNode->m_pFirstBrotherNode = pNode;//连入兄结点
	}

	m_cText = TrimSpace(m_cText);
	if(m_cText[0] == '/' && m_cText[1] == '>')	//不含子结点
	{
		m_cText+= 2;
		m_cText = TrimSpace(m_cText);
		if(0 > m_Stack.Push(pNode, 1))//压入兄结点
		{
			return -1;
		}
		goto LOOP_PARSE;
	}
	if(*m_cText == '>')	//含子结点
	{
		m_cText++;
		m_cText = TrimSpace(m_cText);
		if(0 > m_Stack.Push(pNode, 0))//压入父结点
		{
			return -1;
		}
		goto LOOP_PARSE;
	}
	return -1;
}

CNodeStack::CNodeStack()
{
	m_DataList = NULL;
	m_nNum = 0;
	m_nStaceSpace = 0;
}
int CNodeStack::InitStackSpace(int nStackSpace)
{
	if(m_nNum)
	{
		printf("当前有数据未清空\n");
		return -1;
	}
	if(nStackSpace < 4 || nStackSpace > 64 * 1024)
	{
		printf("指定数据空间 %d 不合理\n", nStackSpace);
		return -1;
	}
	int nOldLen = m_nStaceSpace;
	if(m_DataList)
	{
		delete []m_DataList;
		m_DataList = NULL;
		m_nStaceSpace = 0;
	}
	m_DataList = new NODE_STACK_DATA[nStackSpace];
	m_nStaceSpace = nStackSpace; 
	return nOldLen;
}
void CNodeStack::Clear()
{
	m_nNum = 0;
}
int CNodeStack::Push(CXMLNode *pPreNode, int nNodeFlag)//-1表示push失败
{
	if(m_nNum >= m_nStaceSpace || m_nNum < 0)
	{
		return -1;
	}
	m_DataList[m_nNum].pPreNode = pPreNode;
	m_DataList[m_nNum].nNodeFlag = nNodeFlag;
	m_nNum++;
	return m_nNum;

}
int CNodeStack::Pop()//返回结点标志 -1 pop失败
{
	if(m_nNum > m_nStaceSpace || m_nNum <= 0)
	{
		return -1;
	}
	m_nNum--;	
	return m_DataList[m_nNum].nNodeFlag;

}
