#ifndef _CF_WWW_H_
#define _CF_WWW_H_
#include <cf_json.h>
#include <cf_list.h>
#include <cf_string.h>
typedef enum {CF_CONTENT_TYPE_TEXT_PLAIN, CF_CONTENT_TYPE_TEXT_HTML} CFContentType;
#define CF_CGI_RESPONSE_CODE_OK (200)
#define CF_CGI_RESPONSE_CODE_BAD_REQUEST  (400)
#define CF_CGI_RESPONSE_CODE_UNAUTH  (401)
#define CF_CGI_RESPONSE_CODE_NOT_FOUND    (404)
#define CF_CGI_RESPONSE_CODE_METHOD_NOT_ALLOWED (405)
#define CF_CGI_RESPONSE_CODE_SRVICE_UNAVAILABLE (503)

int cf_cgi_parse_query(const char* query, const char* key, CFString* value);
int cf_cgi_parse_query_double(const char* query, const char* key, double* value);

typedef int(*CFCgiShowFunc)(int);
typedef struct{
	CFString *key;
	CFCgiShowFunc func;
    CFListHead list;
} CFCgiKeyFuncPair;
#endif