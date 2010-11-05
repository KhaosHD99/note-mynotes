#include <stdlib.h>
#include <stdio.h>
#include "XMLInterface.h"

#define AD_PLAY_CONFIG_FILE "play_window.xml"

bool loadDefaultConfig();
void showWindowConfig();
bool initConfig();

int main()
{
	printf("this the fnxmlparser libs test : %s\r\n", AD_PLAY_CONFIG_FILE);
	initConfig();
	showWindowConfig();
	return 0;
}

//传入的r、g、b都是 0 至 255
#define		RGB565(r, g, b) \
	(	((((unsigned char)(r)) >> 3) << 11) | \
		((((unsigned char)(g)) >> 2) <<  5) | \
		((((unsigned char)(b)) >> 3)))

const int maxAdAreaCount = 5;

struct Area
{
	int x;
	int y;
	int width;
	int height;
};

struct InformationColor
{
	int titleColor;
	int phoneNumberColor;
	int timeColor;
	int phonNameColor;
};

static int adAreaCount;
static InformationColor infoColor;
static Area timerArea;
static Area advertisementArea[maxAdAreaCount];

bool loadDefaultConfig()
{
	adAreaCount = 3;
	advertisementArea[0].x = 0;
	advertisementArea[0].y = 0;
	advertisementArea[0].width = 320;
	advertisementArea[0].height = 234;
	advertisementArea[1].x = 320;
	advertisementArea[1].y = 0;
	advertisementArea[1].width = 160;
	advertisementArea[1].height = 66;
	advertisementArea[2].x = 320;
	advertisementArea[2].y = 66;
	advertisementArea[2].width = 160;
	advertisementArea[2].height = 120;

	timerArea.x = 320;
	timerArea.y = 186;
	timerArea.width = 160;
	timerArea.height = 48;


	infoColor.titleColor = RGB565(0xAC1C15>>16 & 0xFF, 0xAC1C15>>8 & 0xFF, 0xAC1C15 & 0xFF);
	infoColor.phoneNumberColor = RGB565(0xAC1C15>>16 & 0xFF, 0xAC1C15>>8 & 0xFF, 0xAC1C15 & 0xFF);
	infoColor.timeColor = RGB565(0x0000FF>>16 & 0xFF, 0x0000FF>>8 & 0xFF, 0x0000FF & 0xFF);
	infoColor.phonNameColor = RGB565(0xAC1C15>>16 & 0xFF, 0xAC1C15>>8 & 0xFF, 0xAC1C15 & 0xFF);
	return true;
}

void showWindowConfig()
{
	for(int i=0; i< adAreaCount; i++)
	{
		printf("area[%d], x:%4d, y:%04d, width:%04d, height:%04d\r\n",
			i,
			advertisementArea[i].x,
			advertisementArea[i].y,
			advertisementArea[i].width,
			advertisementArea[i].height
			);
	}

	printf("timeArea, x:%4d, y:%04d, width:%04d, height:%04d\r\n",
			timerArea.x,
			timerArea.y,
			timerArea.width,
			timerArea.height);
	printf("infoColor, titleColor:%4d, phoneNumberColor:%04d, timeColor:%04d, phonNameColor:%04d\r\n",
			infoColor.titleColor,
			infoColor.phoneNumberColor,
			infoColor.timeColor,
			infoColor.phonNameColor);
}

bool initConfig()
{
	//加载play_window.xml
	char *pAttribute = NULL;
	XMLHandle pRootElement = NULL;
	XMLHandle pAdvertisement = NULL;
	XMLHandle pAdArea = NULL;
	XMLHandle pTime = NULL;
	XMLHandle pTimeArea = NULL;
	int nNum;
	int nColor = 0;

	if (XMLInitLib(512) < 0)
	{
		printf("初始化Xml库失败,加载默认配置\n");
		//loadDefaultConfig();
		return true;
	}

 	//创建一个XML的文档对象
	int nRet = XMLLoadFile((char*)AD_PLAY_CONFIG_FILE);
    if(nRet < 0)
    {
    	printf("装入play_window.xml文件失败\r\n");
		nRet = 1;
		goto ERETURN;
    }
	nRet = 0;
    //获得根元素
    pRootElement = XMLReadRootNode();
    if(!pRootElement)
    {
    	printf("读取play_window根节点错误\r\n");
		nRet = 1;
    	goto ERETURN;
    }
	//-------------------------------获取广告播放区域位置---------------------------------//
    //广告播放区域
    pAdvertisement = XMLReadChildNode(pRootElement);
    if(!pAdvertisement)
    {
    	printf("获取广告播放区域失败\r\n");
		nRet = 2;
    	goto ERETURN;
    }
	pAttribute = XMLReadAttributeValue(pAdvertisement, (char*)"NUM");
	if(!pAttribute)
	{
		printf("获取广告播放区域数量错误\r\n");
		nRet = 3;
    	goto ERETURN;
    }
    nNum = atoi(pAttribute);
    if(nNum <= 0 || nNum > maxAdAreaCount)
    {
    	printf("获取广告播放区域数量错误 %d\r\n", nNum);
		nRet = 4;
    	goto ERETURN;
    }
	printf("nNum:[%d].\n",nNum);

	pAdArea = XMLReadChildNode(pAdvertisement);
	if (!pAdArea)
	{
    	printf("获取广告播放区域\r\n");
		nRet = 5;
    	goto ERETURN;
	}
    
	adAreaCount = 0;
	for(int i = 0; i < nNum; i++ )
	{
	    if(!pAdArea)
	    {
	    	printf("广告播放区域数量不足 %d %d\r\n", nNum, i);
			nRet = 6;
	    	goto ERETURN;
	    }
		//广告播放区域 X 值
	    pAttribute = XMLReadAttributeValue(pAdArea, (char*)"AD_X");
	    if(!pAttribute)
	    {
	    	printf("第%d个广告播放区域无 X \r\n", i + 1);
			nRet = 7;
	    	goto ERETURN;
	    }
	    sscanf(pAttribute, "%u", &advertisementArea[i].x);

		//广告播放区域 Y 值
	    pAttribute = XMLReadAttributeValue(pAdArea, (char*)"AD_Y");
	    if(!pAttribute || !pAttribute[0])
	    {
	    	printf("第%d个广告播放区域无 Y \r\n", i + 1);
			nRet = 8;
	    	goto ERETURN;
	    }
    	sscanf(pAttribute, "%u", &advertisementArea[i].y);

		//广告播放区域 WIDHT 值
	    pAttribute = XMLReadAttributeValue(pAdArea, (char*)"WIDHT");
	    if(!pAttribute || !pAttribute[0])
	    {
	    	printf("第%d个广告播放区域无 WIDHT \r\n", i + 1);
			nRet = 9;
	    	goto ERETURN;
	    }
    	sscanf(pAttribute, "%u", &advertisementArea[i].width);

		//广告播放区域 HEIGHT 值
	    pAttribute = XMLReadAttributeValue(pAdArea, (char*)"HEIGHT");
	    if(!pAttribute || !pAttribute[0])
	    {
	    	printf("第%d个广告播放区域无 HEIGHT \r\n", i + 1);
			nRet = 10;
	    	goto ERETURN;
	    }
    	sscanf(pAttribute, "%u", &advertisementArea[i].height);

		pAdArea = XMLReadBrotherNode(pAdArea);
	}  
    adAreaCount = nNum;//填写广告播放区域数量

	//-------------------------------获取时间区域位置---------------------------------//

	pTime = XMLReadBrotherNode(pAdvertisement);
	if (!pTime)
	{
		printf("获取时间播放区域错误.\n");
		nRet = 11;
		goto ERETURN;
	}

	//////
	nColor = 0;
	pAttribute = XMLReadAttributeValue(pTime, (char*)"TITLECOLOR");
	if(!pAttribute)
	{
	    printf("获取 TITLECOLOR 失败\r\n");
		nRet = 12;
	    goto ERETURN;
	}
	sscanf(pAttribute, "%08X", &nColor);
	infoColor.titleColor = RGB565(nColor>>16 & 0xFF, nColor>>8 & 0xFF, nColor & 0xFF);

	//////
	nColor = 0;
	pAttribute = XMLReadAttributeValue(pTime, (char*)"PHONENUMBERCOLOR");
	if(!pAttribute)
	{
	    printf("获取 PHONENUMBERCOLOR 失败\r\n");
		nRet = 13;
	    goto ERETURN;
	}
	sscanf(pAttribute, "%08X", &nColor);
	infoColor.phoneNumberColor = RGB565(nColor>>16 & 0xFF, nColor>>8 & 0xFF, nColor & 0xFF);

	//////
	nColor = 0;
	pAttribute = XMLReadAttributeValue(pTime, (char*)"TIMECOLOR");
	if(!pAttribute)
	{
	    printf("获取 TIMECOLOR 失败\r\n");
		nRet = 14;
	    goto ERETURN;
	}
	sscanf(pAttribute, "%08X", &nColor);
	infoColor.timeColor = RGB565(nColor>>16 & 0xFF, nColor>>8 & 0xFF, nColor & 0xFF);
	
	//////
	nColor = 0;
	pAttribute = XMLReadAttributeValue(pTime, (char*)"PHONENAMECOLOR");
	if(!pAttribute)
	{
	    printf("获取 PHONENAMECOLOR 失败\r\n");
		nRet = 15;
	    goto ERETURN;
	}
	sscanf(pAttribute, "%08X", &nColor);
	infoColor.phonNameColor = RGB565(nColor>>16 & 0xFF, nColor>>8 & 0xFF, nColor & 0xFF);

	//////
	pTimeArea = XMLReadChildNode(pTime);
	if (!pTimeArea)
	{
		printf("获取时间播放区域错误.\n");
		nRet = 16;
		goto ERETURN;
	}

	//时间播放区域 X 值
	pAttribute = XMLReadAttributeValue(pTimeArea, (char*)"TIME_X");
	if(!pAttribute || !pAttribute[0])
	{
	    printf("时间播放区域无 X \r\n");
		nRet = 17;
	    goto ERETURN;
	}
	sscanf(pAttribute, "%u", &timerArea.x);

	//时间播放区域 Y 值
	pAttribute = XMLReadAttributeValue(pTimeArea, (char*)"TIME_Y");
	if(!pAttribute || !pAttribute[0])
	{
	    printf("时间播放区域无 Y \r\n");
		nRet = 18;
	    goto ERETURN;
	}
    sscanf(pAttribute, "%u", &timerArea.y);

	//时间播放区域 WIDHT 值
	pAttribute = XMLReadAttributeValue(pTimeArea, (char*)"WIDHT");
	if(!pAttribute || !pAttribute[0])
	{
	    printf("时间播放区域无 WIDHT \r\n");
		nRet = 19;
	    goto ERETURN;
	}
    sscanf(pAttribute, "%u", &timerArea.width);

	//时间播放区域 HEIGHT 值
	pAttribute = XMLReadAttributeValue(pTimeArea, (char*)"HEIGHT");
	if(!pAttribute || !pAttribute[0])
	{
	    printf("时间播放区域无 HEIGHT \r\n");
		nRet = 20;
	    goto ERETURN;
	}
    sscanf(pAttribute, "%u", &timerArea.height);
ERETURN:
	XMLReleaseResource();
	if (nRet)
	{
		loadDefaultConfig();
		printf("加载xml配置失败，,加载默认配置.\n");
		return true;
	}
	return true;
}
