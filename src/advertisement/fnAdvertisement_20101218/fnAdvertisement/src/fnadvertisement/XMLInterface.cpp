// XMLParser.cpp: implementation of the CXMLParser class.
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

//#include "XMLInterface.h"
#include "XMLParser.h"
#include "LogMsg.hpp"

#ifdef __cplusplus
extern"C"
{
#endif
/* Get Root Node */
xmlNodePtr xml_read_root_node(char *szFileName)
{
	CXMLParser *parser = CXMLParser::get_instance();
	return parser->read_root_node(szFileName);
}

/* Get Child Node */
xmlNodePtr xml_read_child_node(xmlNodePtr pNode)
{
	CXMLParser *parser = CXMLParser::get_instance();
	return parser->read_child_node(pNode);
}

/* Get Brother Node */
xmlNodePtr xml_read_brother_node(xmlNodePtr pNode)
{
	CXMLParser *parser = CXMLParser::get_instance();
	return parser->read_brother_node(pNode);
}

/* Get  Attribute */
xmlChar *xml_read_attribute_value(xmlNodePtr pNode, xmlChar *cAttrName)
{
	CXMLParser *parser = CXMLParser::get_instance();
	return parser->read_attribute_value(pNode, cAttrName);
}

void free_xml_parser()
{
  	//CXMLParser *parser = CXMLParser::get_instance();
	//delete parser;
}

#ifdef __cplusplus
}
#endif


