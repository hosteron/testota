/* COPYRIGHT_CHUNFENG */
#ifndef _CF_JSON_H_
#define _CF_JSON_H_
#include <stdlib.h>
#include "cJSON.h"
#include "cf_common.h"
typedef cJSON CFJson;

/*
#define cJSON_False 0
#define cJSON_True 1
#define cJSON_NULL 2
*/

#define CFJsonType  int
#define CF_JSON_TYPE_NUMBER cJSON_Number
#define CF_JSON_TYPE_STRING cJSON_String
#define CF_JSON_TYPE_OBJECT cJSON_Object
#define CF_JSON_TYPE_ARRAY  cJSON_Array

#define CFJsonForeach(__jObj, __tmpObj) \
    CFJson* __tmpObj;\
    for(__tmpObj = (__jObj)->child; __tmpObj; __tmpObj=(__tmpObj)->next)

#define CFJsonArrayForeach  CFJsonForeach
CFJsonType CFJsonGetType(CFJson* jObj);
CFJson* CFJsonParse(const char* jStr);
int CFJsonPut(CFJson* jObj);
CFJson* CFJsonNext(CFJson* jObj);
CFJson* CFJsonObjectGet(CFJson* jObj, const char* key);
const char* CFJsonStringGet(CFJson* jObj);
int CFJsonIntGet(CFJson* jObj, int* value);
int CFJsonDoubleGet(CFJson* jObj, double* value);
int CFJsonBoolGet(CFJson* jObj, BOOL* bl);
const char* CFJsonObjectGetString(CFJson* jObj, const char* key);
int CFJsonObjectGetInt(CFJson* jObj, const char* key, int* value);
int CFJsonObjectGetDouble(CFJson* jObj, const char* key, double* value);
int CFJsonObjectGetBool(CFJson* jObj, const char* key, BOOL* value);
int CFJsonArrayLen(CFJson* jObj);
CFJson* CFJsonArrayGet(CFJson* jObj, int idx);
const char* CFJsonArrayGetString(CFJson* jObj, int idx);
int CFJsonArrayGetInt(CFJson* jObj, int idx, int* value);
int CFJsonArrayGetDouble(CFJson* jObj, int idx, double* value);

CFJson* CFJsonObjectNew();
int CFJsonObjectIsNull(CFJson* obj);
int CFJsonObjectAdd(CFJson* obj, const char* key, CFJson* objAdd);
int CFJsonObjectAddInt(CFJson* obj, const char* key, int val);
int CFJsonObjectAddInt64(CFJson* obj, const char* key, long long val);
int CFJsonObjectAddDouble(CFJson* obj, const char* key, double val);
int CFJsonObjectAddString(CFJson* obj, const char* key, const char* cStr);
int CFJsonObjectAddBool(CFJson* obj, const char* key, BOOL val);
int CFJsonArrayAdd(CFJson* obj,  CFJson* objAdd);
int CFJsonArrayAddInt(CFJson* obj, int val);
int CFJsonArrayAddInt64(CFJson* obj, long long val);
int CFJsonArrayAddDouble(CFJson* obj, double val);
int CFJsonArrayAddString(CFJson* obj, const char* cStr);
int CFJsonArrayAddBool(CFJson* obj, BOOL val);
CFJson* CFJsonStringNew(const char* cStr);
inline CFJson* CFJsonIntNew(int num);
inline CFJson* CFJsonInt64New(long long num);
inline CFJson* CFJsonDoubleNew(double num);
CFJson* CFJsonBoolNew(BOOL bl);
CFJson* CFJsonArrayNew();
char* CFJsonNewCStr(CFJson* jObj);
int CFJsonGetString(CFJson* jObj, CFString* str);
int CFJsonGetUnformatedString(CFJson* jObj, CFString* str);
char* CFJsonPrint(CFJson* jObj);
#endif
