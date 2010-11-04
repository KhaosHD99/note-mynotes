/*
** FileName:    config.h
** Author:        hansen
** Date:        May 11, 2007
** Comment:        �����ļ���,��Ҫ������ȡxml�����ļ��е�һЩ������Ϣ 
*/
 
#ifndef _CONFIG
#define _CONFIG
 
#include <string>
#include "tinyxml.h"
 
using namespace std;
 
class CConfig
{
public:
    explicit CConfig(const char* xmlFileName)
        :mXmlConfigFile(xmlFileName),mRootElem(0)
    {
        //���������ļ�
        mXmlConfigFile.LoadFile();    
        
        //�õ������ļ��ĸ����
        mRootElem=mXmlConfigFile.RootElement();
    }
 
public:
    //�õ�nodeName����ֵ
    string GetValue(const string& nodeName);
 
private:
    //��ֹĬ�Ϲ��캯��������
    //CMmsConfig();
 
private:
    TiXmlDocument    mXmlConfigFile;
    TiXmlElement*    mRootElem;
 
};
 
#endif


