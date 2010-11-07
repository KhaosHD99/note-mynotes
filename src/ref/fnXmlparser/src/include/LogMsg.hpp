#ifndef LOGMSG_H_
#define LOGMSG_H_
/*********************************************************************************
	LogMsg.hpp

	这个头文件规范化我们程序输出调试、警告、错误等信息的方式。
	现在信息分为五个级别，Linux提供了七个级别，我们不使用最高的两个级别。
	我们程序中可根据需要用。

	五个级别对应的宏函数如下：
	showDebug
	showInfo
	showWarning
	showError
	showCritical
	使用方式跟printf一样。

	其中，showError和showCritical只应在系统的errno有值的时候用，
	例如打开文件找不到，系统会设置errno的值。
	showError和showCritical的时候，除了输出你指定的信息，还会附带输出
	errno对应的信息，这样可方便你分析出错条件。

	编译的时候，如果定义了USE_SYSLOG，输出会进入到系统log文件，
	我们程序作为成品运行的时候要用这个方式；
	如果没有定义USE_SYSLOG，就直接打印到屏幕。
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

//下面两个加上了花括号，避免外面使用的时候出问题。但有else的情况仍然有些问题。
#define showError(fmt, ...) \
	{ printf("ERROR: %s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
	  perror(""); }

#define showCritical(fmt, ...) \
	{ printf("CRITICAL: %s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
	  perror(""); }


#endif //USE_SYSLOG


#endif //LOGMSG_H_

