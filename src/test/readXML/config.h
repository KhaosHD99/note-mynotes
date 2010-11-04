/*
** FileName:    config.h
** Author:        hansen
** Date:        May 11, 2007
** Comment:        配置文件类,主要用来读取xml配置文件中的一些配置信息 
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
        //加载配置文件
        mXmlConfigFile.LoadFile();    
        
        //得到配置文件的根结点
        mRootElem=mXmlConfigFile.RootElement();
    }
 
public:
    //得到nodeName结点的值
    string GetValue(const string& nodeName);
 
private:
    //禁止默认构造函数被调用
    //CMmsConfig();
 
private:
    TiXmlDocument    mXmlConfigFile;
    TiXmlElement*    mRootElem;
 
};
 
#endif


