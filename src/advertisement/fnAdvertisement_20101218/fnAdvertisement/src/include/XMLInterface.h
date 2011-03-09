
#if !defined(__XMLINTERFACE_H__)
#define __XMLINTERFACE_H__

#include <libxml/parser.h>

typedef void* XMLHandle; 

#ifdef __cplusplus
extern"C"
{
#endif
/* Get Root Node */
xmlNodePtr xml_read_root_node(char *szFileName);
	
/* Get Child Node */
xmlNodePtr xml_read_child_node(xmlNodePtr);
	
/* Get Brother Node */
xmlNodePtr xml_read_brother_node(xmlNodePtr);

/* Get  Attribute */
xmlChar *xml_read_attribute_value(xmlNodePtr pNode, xmlChar *cAttrName);

void free_xml_parser();
#ifdef __cplusplus
}
#endif

#endif 
