/* COPYRIGHT_CHUNFENG */
#ifndef CF_SLIST_H
#define CF_SLIST_H
#include "cf_string.h"

typedef struct _CFSListNode_ CFSListNode;
struct _CFSListNode_
{
	void *data;
	CFSListNode *next;
};

typedef void(*CFFreeObjFunc)(void* obj);
CFSListNode* cf_slist_append(CFSListNode* head, void* data);
CFSListNode* cf_slist_del(CFSListNode* head, void* data_to_del);
CFSListNode* cf_slist_prepend(CFSListNode* head, void* data);
CFSListNode* cf_slist_reverse(CFSListNode* head);
void cf_slist_free(CFSListNode* head);
void cf_slist_free_all(CFSListNode* head, CFFreeObjFunc freeFunc);
#define cf_slist_get_next(node) (node->next)

#endif
