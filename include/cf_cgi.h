/* COPYRIGHT_CHUNFENG */
#ifndef CF_CGI_H
#define CF_CGI_H
#include "cf_std.h"
#include "cf_string.h"
#include "cf_list.h"
#include "cf_json.h"
#include "cf_www.h"

/* drop out */
CFCgiKeyFuncPair* cf_cgi_key_func_pair_new(const char* key, CFCgiShowFunc func);
void cf_cgi_key_func_pair_free(CFCgiKeyFuncPair* pair);
int cf_cgi_key_func_pair_append(CFCgiKeyFuncPair* pairHead, const char* key, CFCgiShowFunc func);
void cf_cgi_key_func_pair_free_all(CFCgiKeyFuncPair* pairHead);
int cf_cgi_display_html(const char* htmFile, CFCgiKeyFuncPair* keyFuncHead, int show_fd);


/* AJAX API FOR CGI */
typedef struct request{
    const char* todo;
    int(*processUseJason)(CFJson* obj, int* stdio);
    int(*processUseQueryString)(const char* queryCStr, int* stdio);
    int(*authSessionUseJason)(CFJson* obj, int* stdio);
    int(*authSessionUseQueryString)(const char* queryCStr, int* stdio);
}RequestKeyFuncPair;
int CFCgiProcessRequest(RequestKeyFuncPair* KeyFuncPairs, int* stdio);
#define CFCgiResponse   CFFdPrintf
int CFCgiResponseHead(CFContentType contentType, int fd);
int CFCgiResponseErrorBody(int errorCode, int fd);
int CFCgiResponseOkBody(int fd);
#endif
