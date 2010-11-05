// XMLNode.h: interface for the CXMLNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLNODE_H__62C0DE1E_9243_4DEE_AD79_20259B577A39__INCLUDED_)
#define AFX_XMLNODE_H__62C0DE1E_9243_4DEE_AD79_20259B577A39__INCLUDED_
#define PROPERTY_LEN				256 
#define NAME_LEN					32

class CXMLNode;

class CXMLNode  
{
public:
	CXMLNode *ReadChildNode(int nPos = -1);
	CXMLNode *ReadBrotherNode(int nPos = -1);
	char *ReadAttributeValue(char *cAttributeName);
	static void StrToLower(char *cStr, int nLen);
protected:
	char *TrimSpace(char *cText);
public:
	char m_cProperty[PROPERTY_LEN + 2];
	char m_cName[NAME_LEN + 2];
	short m_sChildNodePos;//子结点位置
	short m_sBrotherNodePos;//兄弟结点位置
	CXMLNode *m_pFirstChildNode;//首个子结点
	CXMLNode *m_pFirstBrotherNode;//首个兄弟结点

};
#define NODE_LEN			sizeof(CXMLNode)
#endif // !defined(AFX_XMLNODE_H__62C0DE1E_9243_4DEE_AD79_20259B577A39__INCLUDED_)
