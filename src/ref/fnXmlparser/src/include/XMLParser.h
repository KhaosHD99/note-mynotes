// XMLParser.h: interface for the CXMLParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLPARSER_H__EB92D8A6_C995_4086_8B1C_92A31DB2F8C8__INCLUDED_)
#define AFX_XMLPARSER_H__EB92D8A6_C995_4086_8B1C_92A31DB2F8C8__INCLUDED_

#include "XMLNode.h"

struct NODE_STACK_DATA
{
	CXMLNode	*pPreNode;
	int			nNodeFlag;//0为父结点 1为兄结点
};
//#define STACK_SPACE			(16 * 1024)
class CNodeStack
{
public:
	CNodeStack();
	int InitStackSpace(int nStackSpace);
	int ExistData(){return m_nNum > 0 && m_nNum <= m_nStaceSpace;}
	void Clear();
	int Push(CXMLNode *pPreNode, int nNodeFlag); //-1表示push失败
	int Pop();//返加结点标志 -1 pop失败
public:
	NODE_STACK_DATA  *m_DataList;
	int m_nNum;
	int m_nStaceSpace;
};
class CXMLParser  
{
public:
	CXMLParser();
	virtual ~CXMLParser();
	int InitStackSpace(int nStackSpace);
	int LoadFile(char *szFileName);
	CXMLNode *ReadRootNode();
	int ReleaseResource();

	

	//根结点(以根结点为头的一稞树)
	CXMLNode *m_pRootNode;
	

protected:
	CXMLNode *RarseFile(char *cText);//解释
	int PreProcess(char *cText, int nLen);//
	int LinePreProcess(char *cText, int nLen);
	int SpacePreProcess(char *cText, int nLen);	
	char *TrimSpace(char *cText);
	int GetEndFlagLen(char *cText);
	int GetSelfInfo(char *szText);
	int FindMatchInfo(char *cText, char *cInfoProperty, int nLen);
	int ClearNodeTree(CXMLNode *pHead);
	char *RemoveXMLDeclare(char *cText);
	int ReadXMLNode(CXMLNode *pPreNode);
protected:

	int m_nNum;
	int m_nRet;
	char *m_cText;	

	char m_cInfoFlag[NAME_LEN];//结点名
	char m_cInfoProperty[PROPERTY_LEN];
	CNodeStack m_Stack;
};
#endif // !defined(AFX_XMLPARSER_H__EB92D8A6_C995_4086_8B1C_92A31DB2F8C8__INCLUDED_)
