#ifndef _CF_BUFFER_
#define _CF_BUFFER_
#include "cf_std.h"
#include "cf_common.h"
typedef struct cf_buffer{
    size_t minSize;
    size_t unit;
    size_t curr_size;
    size_t len;
    void* data;
}CFBuffer;

int CFBufferInit(CFBuffer* pthis, size_t minSize, size_t unit);
int CFBufferExit(CFBuffer* pthis);
CFBuffer* CFBufferNew(size_t minSize, size_t unit);
int CFBufferCp(CFBuffer* to, const void* source, size_t len);
int CFBufferCat(CFBuffer* to, const void* source, size_t len);
int CFBufferClear(CFBuffer* buf);
int CFBufferRead(int fd, CFBuffer* to, BOOL async);
int CFBufferWrite(int fd, CFBuffer* from, BOOL async);
void* CFBufferGetPtr(CFBuffer* buf);
size_t CFBufferGetSize(CFBuffer* buf);
int CFBufferFree(CFBuffer* buf);
#endif

