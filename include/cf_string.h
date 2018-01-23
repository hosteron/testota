/* COPYRIGHT_CHUNFENG */
#ifndef CFSTRING_H
#define CFSTRING_H

typedef struct
{
	char *str;
	unsigned int len;
	unsigned int alloc_size;
} CFString;

int CFStringInitLen(CFString* self, const char* start, unsigned int len);
int CFStringInit(CFString* self, const char* str);
CFString* cf_string_new(const char* str);
#define CFStringNew cf_string_new
CFString* cf_string_new_len(const char* start, unsigned int len);
#define CFStringNewLen  cf_string_new_len
CFString* cf_string_new_start_end(const char* start, const char* end);
#define CFStringNewStartEnd cf_string_new_start_end
int CFStringExit(CFString* string);
void cf_string_free(CFString* string);
#define CFStringFree    cf_string_free
CFString* cf_string_safe_cp_n(CFString* string, const char* source, unsigned int source_len);
#define CFStringSafeCpN cf_string_safe_cp_n
CFString* cf_string_safe_cp(CFString* string, const char* source);
#define CFStringSafeCp  cf_string_safe_cp
CFString* cf_string_safe_cat_n(CFString* string, const char* source, unsigned int source_len);
#define CFStringSafeCatN    cf_string_safe_cat_n
CFString* cf_string_safe_cat(CFString* string, const char* source);
#define CFStringSafeCat cf_string_safe_cat
#define cf_string_get_str(_string) ((_string)->str)
#define CFStringGetStr  cf_string_get_str
#define cf_string_get_len(_string) ((_string)->len)
#define CFStringGetLen  cf_string_get_len
#define cf_string_get_size(_string) ((_string)->alloc_size)
#define CFStringGetSize cf_string_get_size
#define CONST_STR_LEN(__str) (__str),sizeof(__str)-1
#endif
