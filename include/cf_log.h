/* COPYRIGHT_CHUNFENG */
#ifndef EVENT_SERVER_H
#define EVENT_SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
/*
	// Define these macros before include this head file
#define ERROR_LOG_FILE "/var/log/cf_error.log"
#define MESSAGE_LOG_FILE "/var/log/cf_message.log"
#define DEBUG_LOG_FILE "/var/log/cf_debug.log"
*/

enum CF_LOG_TYPE{CF_LOG_DEBUG, CF_LOG_MESSAGE, CF_LOG_ERROR};
int cf_log_file(enum CF_LOG_TYPE type, const char* file_path, const char* format, ...);
int cf_log_close_file();


#ifndef ERROR_LOG_FILE
#define CF_ERR(...) fprintf(stdout, "[E][%s:%d] ", __FILE__, __LINE__); fprintf(stdout, __VA_ARGS__);
#else
#define CF_ERR(...) cf_log_file(CF_LOG_ERROR, ERROR_LOG_FILE, "[E][%s:%d] ", __FILE__, __LINE__); cf_log_file(CF_LOG_ERROR, ERROR_LOG_FILE, __VA_ARGS__);
#endif

#define CF_SYS_ERR(...)   {CF_ERR(__VA_ARGS__);CF_ERR("For %s\n", strerror(errno));}
#define CF_ERR_OUT(_dest, ...)   {CF_ERR(__VA_ARGS__); goto _dest;}
#define CF_SYS_ERR_OUT(_dest, ...)   {CF_SYS_ERR(__VA_ARGS__); goto _dest;}

#define CF_DBG_TS() {struct timespec ts;    clock_gettime(CLOCK_MONOTONIC, &ts);    LCF_DBG("<%llds:%lldns>\n", (long long)ts.tv_sec, (long long)ts.tv_nsec);}


#ifndef MESSAGE_LOG_FILE
#define CF_MSG(...) fprintf(stdout, "[M][%s:%d] ", __FILE__, __LINE__);	fprintf(stdout, __VA_ARGS__);
#else
#define CF_MSG(...) cf_log_file(CF_LOG_MESSAGE, MESSAGE_LOG_FILE, "[M][%s:%d] ", __FILE__, __LINE__); cf_log_file(CF_LOG_MESSAGE, MESSAGE_LOG_FILE, __VA_ARGS__);
#endif


#ifndef DEBUG_LOG_FILE
#define CF_DBG(...) fprintf(stdout, "[D][%s:%d] ", __FILE__, __LINE__); fprintf(stdout, __VA_ARGS__);
#else
#define CF_DBG(...) cf_log_file(CF_LOG_DEBUG, DEBUG_LOG_FILE, "[D][%s:%d]", __FILE__, __LINE__); cf_log_file(CF_LOG_DEBUG, DEBUG_LOG_FILE, __VA_ARGS__);
#endif


#define CF_DBG_N() CF_DBG("\n");
#define CF_DBG_IN_FUNC() CF_DBG("==>%s()\n", __FUNCTION__);
#define CF_DBG_OUT_FUNC() CF_DBG("%s()==>\n", __FUNCTION__);

int CFEnvDbg(const char* dbgMark, const char* fmt, ...);

#endif
