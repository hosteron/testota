#ifndef _CF_QUEUE_
#define _CF_QUEUE_
#include "cf_list.h"

typedef struct cf_queue{
	CFListHead list;
	int size;
    int currSize;
}CFQueue;

typedef struct cf_queue_data{
    void* data;
    CFListHead list;
}CFQueueData;
int CFQueueDataInit(CFQueueData* self, void* data);
int CFQueueDataExit(CFQueueData* self);
CFQueueData* CFQueueDataNew(void* data);
void CFQueueDataFree(CFQueueData* self);

int CFQueueInit(CFQueue* self, int size);
int CFQueueExit(CFQueue* self);
int CFQueuePush(CFQueue* self, void* data);
int CFQueuePop(CFQueue* self, void** pData);
#endif