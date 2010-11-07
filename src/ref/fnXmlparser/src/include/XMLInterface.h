//xml解析接口头文件
//
//////////////////////////////////////////////////////////////////////

#if !defined(__XMLINTERFACE_H__)
#define __XMLINTERFACE_H__
typedef void* XMLHandle; 
//初始化解析库,nNodeSpace为结点纵向或横向的最大深度,返回0为成功,返回-1为失败
int XMLInitLib(int nNodeSpace);

//修改最大深度,nNodeSpace为新的结点纵向或横向最大深度,成功返回原深度,失败返回-1
int XMLChangeNodeSpace(int nNodeSpace);

//装载XML文件,返回0为成功,返回-1为失败
int XMLLoadFile(char *szFileName);

//读取XML根结点句柄,返回NULL为失败,非空表示成功
XMLHandle XMLReadRootNode();

//释放XML结点树,返回0为成功,返回-1为失败
int XMLReleaseResource();

//读取子结点句柄,返回NULL为失败,非空表示成功
XMLHandle XMLReadChildNode(XMLHandle hParent);

//读取XML兄弟结点句柄,返回NULL为失败,非空表示成功
XMLHandle XMLReadBrotherNode(XMLHandle hPreNode);

//读取XML结点属性值,返回NULL为失败,非空表示成功
char *XMLReadAttributeValue(XMLHandle hNode, char *cAttributeName);	

#endif 
