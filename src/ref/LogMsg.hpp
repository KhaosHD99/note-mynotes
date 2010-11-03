#ifndef LOGMSG_H_
#define LOGMSG_H_
/*********************************************************************************
	LogMsg.hpp

	���ͷ�ļ��淶�����ǳ���������ԡ����桢�������Ϣ�ķ�ʽ��
	������Ϣ��Ϊ�������Linux�ṩ���߸��������ǲ�ʹ����ߵ���������
	���ǳ����пɸ�����Ҫ�á�

	��������Ӧ�ĺ꺯�����£�
	showDebug
	showInfo
	showWarning
	showError
	showCritical
	ʹ�÷�ʽ��printfһ����

	���У�showError��showCriticalֻӦ��ϵͳ��errno��ֵ��ʱ���ã�
	������ļ��Ҳ�����ϵͳ������errno��ֵ��
	showError��showCritical��ʱ�򣬳��������ָ������Ϣ�����ḽ�����
	errno��Ӧ����Ϣ�������ɷ������������������

	�����ʱ�����������USE_SYSLOG���������뵽ϵͳlog�ļ���
	���ǳ�����Ϊ��Ʒ���е�ʱ��Ҫ�������ʽ��
	���û�ж���USE_SYSLOG����ֱ�Ӵ�ӡ����Ļ��
*********************************************************************************/
#include <syslog.h>
#include <error.h>


#ifdef USE_SYSLOG


#define showDebug(fmt, ...) \
	syslog(LOG_DEBUG, "%s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__);

#define showInfo(fmt, ...) \
	syslog(LOG_INFO, "%s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__);

#define showWarning(fmt, ...) \
	syslog(LOG_WARNING, "%s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__);

#define showError(fmt, ...) \
	syslog(LOG_ERR, "%s(%d) [%m] "fmt, __FILE__, __LINE__, ##__VA_ARGS__);

#define showCritical(fmt, ...) \
	syslog(LOG_CRIT, "%s(%d) [%m] "fmt, __FILE__, __LINE__, ##__VA_ARGS__);


#else //USE_SYSLOG


#define showDebug(fmt, ...) \
	printf("DEBUG: %s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#define showInfo(fmt, ...) \
	printf("INFO: %s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#define showWarning(fmt, ...) \
	printf("WARNING: %s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__)

//�������������˻����ţ���������ʹ�õ�ʱ������⡣����else�������Ȼ��Щ���⡣
#define showError(fmt, ...) \
	{ printf("ERROR: %s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
	  perror(""); }

#define showCritical(fmt, ...) \
	{ printf("CRITICAL: %s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
	  perror(""); }


#endif //USE_SYSLOG


#endif //LOGMSG_H_

