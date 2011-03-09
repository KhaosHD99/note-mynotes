/*
* Copyright ���ݷ�����Ѷ���޹�˾
* All rights reserved.
* 
* �ļ����ƣ�XMLParser.cpp
* 
* ժ    Ҫ��XML������
* 
* ��    �ߣ���ҫȪ
*
* �޸���:   �����
* 
* ����޸����ڣ�2010��11��19��
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "XMLParser.h"

CXMLParser::CXMLParser()
{
	doc = NULL;
	root_node = NULL;
}

CXMLParser::~CXMLParser()
{
	xmlFreeDoc(doc);
	showInfo("XMLParser Destructed\n");
}

/* ************************************************************************************************
				                           			       Single Instance
**************************************************************************************************/
CXMLParser* CXMLParser::instance = NULL;
CXMLParser* CXMLParser::get_instance()
{
	if(!instance)
		instance = new CXMLParser;
	
	return instance;
}

int CXMLParser::load_file(char *szFileName)
{
	if(!szFileName)
	{
		return -1;
	}
	
	xmlNodePtr curElement;
	xmlAttrPtr curProp;
    
	doc = xmlReadFile(szFileName,
		              NULL,
		              XML_PARSE_NOBLANKS);
	
	/* validate */
	if (!doc)
	{ 	
		showError("open doc %s fail\n", szFileName);
		return -1; 
	}
	root_node = xmlDocGetRootElement(doc);
	
	return 0;
}
	
xmlNodePtr CXMLParser::read_root_node(char *szFileName)
{	
	if(load_file(szFileName))
		return NULL;
	
	return root_node;
}

xmlNodePtr CXMLParser::read_child_node(xmlNodePtr pNode)
{
	return pNode->children;
}

xmlNodePtr CXMLParser::read_brother_node(xmlNodePtr pNode)
{
	return pNode->next;
}

xmlChar *CXMLParser::read_attribute_value(xmlNodePtr pNode, xmlChar *cAttrName)
{
	return xmlGetProp(pNode, cAttrName);
}

