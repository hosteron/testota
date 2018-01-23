/* COPYRIGHT_CHUNFENG */
#ifndef CF_LIST_FILE_H
#define CF_LIST_FILE_H
#include "cf_common.h"
#include "cf_string.h"
#include "cf_list.h"

typedef CFListHead*(*CFLineItemParseFunc)(char*, char*);
typedef void(*CFLineItemFreeFunc)(CFListHead* node); 
typedef int(*CFLineItemWriteFunc)(CFListHead* node, int fd);

CFListHead* cf_list_file_new(const char* filePath, CFLineItemParseFunc linParsefunc);
void cf_list_file_free(CFListHead* list, CFLineItemFreeFunc lineItemFreeFunc);
int cf_list_file_write(CFListHead* file, int fd, CFLineItemWriteFunc lineItemWriteFunc);
int cf_list_file_save(CFListHead* file, const char* fileUri, CFLineItemWriteFunc lineItemWriteFunc);
#define cf_print_list_file(__file__, lineItemWriteFunc) cf_write_list_file(__file__, 1, lineItemWriteFunc)
#endif
