// XMLParser.cpp: implementation of the CXMLParser class.
//
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "XMLInterface.h"
#include "XMLParser.h"
CXMLParser g_XMLParser;
//初始化解析库,nNodeSpace为结点纵向或横向的最大深度,返回>=0为成功,返回-1为失败
int XMLInitLib(int nNodeSpace)
{
	return g_XMLParser.InitStackSpace(nNodeSpace);
}

//修改最大深度,nNodeSpace为新的结点纵向或横向最大深度,成功返回原深度,失败返回-1
int XMLChangeNodeSpace(int nNodeSpace)
{
	return g_XMLParser.InitStackSpace(nNodeSpace);
}

//装载XML文件,返回0为成功,返回-1为失败
int XMLLoadFile(char *szFileName)
{
	return g_XMLParser.LoadFile(szFileName);
}

//读取XML根结点句柄,返回NULL为失败,非空表示成功
XMLHandle XMLReadRootNode()
{
	return (XMLHandle)g_XMLParser.ReadRootNode();
}

//释放XML结点树,返回0为成功,返回-1为失败
int XMLReleaseResource()
{
	return g_XMLParser.ReleaseResource();
}

//读取子结点句柄,返回NULL为失败,非空表示成功
XMLHandle XMLReadChildNode(XMLHandle hParent)
{
	if(!hParent)
	{
		printf("ReadChildNode错误的参数\n");
		return  NULL;
	}
	CXMLNode *pNode = (CXMLNode*)hParent;
	return (XMLHandle)pNode->ReadChildNode();
}

//读取XML兄弟结点句柄,返回NULL为失败,非空表示成功
XMLHandle XMLReadBrotherNode(XMLHandle hPreNode)
{
	if(!hPreNode)
	{
		printf("ReadBrotherNode错误的参数\n");
		return  NULL;
	}
	CXMLNode *pNode = (CXMLNode*)hPreNode;
	return (XMLHandle)pNode->ReadBrotherNode();
}

//读取XML结点属性值,返回NULL为失败,非空表示成功
char *XMLReadAttributeValue(XMLHandle hNode, char *cAttributeName)
{
	if(!hNode)
	{
		printf("ReadAttributeValue错误的参数\n");
		return  NULL;
	}
	CXMLNode *pNode = (CXMLNode*)hNode;
	return pNode->ReadAttributeValue(cAttributeName);
}

