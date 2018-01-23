/* COPYRIGHT_CHUNFENG */
#ifndef _CF_PIPE_H_
#define _CF_PIPE_H_
#include "cf_list.h"

typedef struct {
	void* data;
	CFListHead list;
}CFPipeNode;

typedef struct {
	CFPipeNode* nodes;
	CFPipeNode emptyNodes;
	CFPipeNode fullNodes;
	int size;
}CFPipe;

int CFPipeInit(CFPipe* pp, int size);
int CFPipePush(CFPipe* pp, void* data);
void* CFPipePop(CFPipe* pp);
void* CFPipeGetData(CFPipe* pp);
int CFPipeExit(CFPipe* pp);

void* CFPipeGetEmpty(CFPipe* pp);

#endif

