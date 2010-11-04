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
        cout<<"��ȡ��������"<<endl;
        return "";
    }
 
    TiXmlElement* pElem=mRootElem->FirstChildElement(nodeName.c_str());
    if(!pElem)
    {
        cout<<"��ȡ"<<nodeName<<"������"<<endl;
        return "";
    }
 
    return pElem->GetText();
 
}
