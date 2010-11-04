/*
** FileName:    config.cpp
** Author:        hansen
** Date:        May 11, 2007
** Comment:        
*/
 
#include "config.h"
#include <iostream>
 
string CConfig::GetValue(const string& nodeName)
{
    if(!mRootElem)
    {
        cout<<"读取根结点出错"<<endl;
        return "";
    }
 
    TiXmlElement* pElem=mRootElem->FirstChildElement(nodeName.c_str());
    if(!pElem)
    {
        cout<<"读取"<<nodeName<<"结点出错"<<endl;
        return "";
    }
 
    return pElem->GetText();
 
}
