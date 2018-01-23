/* COPYRIGHT_CHUNFENG */
#ifndef _CF_HASH_TABLE_
#define _CF_HASH_TABLE_
#include "cf_common.h"
#include "cf_list.h"
typedef struct{
    void* ptr;
    CFListHead list;
}CFHashTableNode;

typedef struct{
    int size;
    CFHashTableNode* nodeArray;
    int count;
    int(*hashFn)(void* key);
    void*(*ptrToKeyFn)(void* ptr);
    BOOL(*ptrKeyMatchFn)(void* ptr, void* key);
}CFHashTable;

int CFHashTableInit(CFHashTable* tbl, int size, int(*hashFn)(void* key), void*(*ptrToKeyFn)(void* ptr), BOOL(*ptrKeyMathFn)(void* ptr, void* key));
CFHashTable* CFHashTableNew(int size, int(*hashFn)(void* key), void*(*ptrToKeyFn)(void* ptr), BOOL(*ptrKeyMathFn)(void* ptr, void* key));
int CFHashTableFree(CFHashTable* tbl); 
int CFHashTableAdd(CFHashTable* pthis, void* ptr);
void* CFHashTableGet(CFHashTable* tbl, void* key);
int CFHashTableDel(CFHashTable* pthis, void* key);
int CFHashTableExit(CFHashTable* tbl);
#endif
