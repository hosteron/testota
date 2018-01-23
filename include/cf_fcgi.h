/* COPYRIGHT_CHUNFENG */
#ifndef _CF_FCGI_H_
#define _CF_FCGI_H_
#include <fcgi_stdio.h>
#include "cf_string.h"
#include "cf_list.h"
#include "cf_json.h"
#include "cf_www.h"

/* AJAX API FOR CGI */
typedef struct{
    const char* todo;
    int(*processUseJason)(CFJson* obj);
    int(*processUseQueryString)(const char* queryCStr);
    int(*authSessionUseJason)(CFJson* obj);
    int(*authSessionUseQueryString)(const char* queryCStr);
}CFFCgiRequestKeyFuncPair;

int CFFcgiProcessRequest(CFFCgiRequestKeyFuncPair* KeyFuncPairs);
#define CFFcgiResponse   FCGI_printf
int CFFcgiResponseHead(CFContentType contentType);
int CFFcgiResponseErrorBody(int errorCode);
int CFFcgiResponseOkBody();
int CFFcgiFpToString(CFString* str, FCGI_FILE* fp, int len);
#endif
