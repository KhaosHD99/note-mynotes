/*
* Copyright 广州泛网视讯有限公司
* All rights reserved.
* 
* 文件名称：XMLParser.h
* 
* 摘    要：XML分析库
* 
* 作    者：吴耀泉
*
* 修改者:   徐镇杰
* 
* 最后修改日期：2010年11月19日
*/

#if !defined(AFX_XMLPARSER_H__EB92D8A6_C995_4086_8B1C_92A31DB2F8C8__INCLUDED_)
#define AFX_XMLPARSER_H__EB92D8A6_C995_4086_8B1C_92A31DB2F8C8__INCLUDED_

#include <libxml/parser.h>
#include "LogMsg.hpp"

class CXMLParser  
{
	private:
		xmlDocPtr doc;	
		xmlNodePtr root_node;
		static CXMLParser *instance;
		CXMLParser();
		
	public:
		~CXMLParser();
		static CXMLParser *get_instance();
		int load_file(char *szFileName);
		xmlNodePtr read_root_node(char *szFileName);
		xmlNodePtr read_child_node(xmlNodePtr pNode);
		xmlNodePtr read_brother_node(xmlNodePtr pNode);
		xmlChar *read_attribute_value(xmlNodePtr pNode, xmlChar *cAttrName);
};
#endif // !defined(AFX_XMLPARSER_H__EB92D8A6_C995_4086_8B1C_92A31DB2F8C8__INCLUDED_)
