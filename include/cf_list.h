/* COPYRIGHT_CHUNFENG */
#ifndef _CF_LIST_H_
#define _CF_LIST_H_
#include "cf_common.h"

typedef struct cf_list_head{
    struct cf_list_head *prev;
    struct cf_list_head *next;
} CFListHead;
void cf_list_init(CFListHead* node);
#define CFListInit  cf_list_init
#define cf_list_exit(...)
#define CFListExit   cf_list_exit
#define cf_list_get_next(__node) ((__node)->next)
#define CFListGetNext   cf_list_get_next
#define cf_list_get_prev(__node) ((__node)->prev)
#define CFListGetPrev   cf_list_get_prev
#define CFListGetHead(__node) (__node)
#define CFListGetTail(__node) cf_list_get_prev(__node)
#define cf_list_get_next_container(__ptr, __type, __member) container_of((__ptr)->next, __type, __member)
#define CFListGetNextContainer cf_list_get_next_container
#define cf_list_get_prev_container(__ptr, __type, __member) container_of((__ptr)->prev, __type, __member)
#define CFListGetPrevContainer cf_list_get_prev_container
void cf_list_insert_next(CFListHead* node, CFListHead* to_insert);
#define CFListInsertNext    cf_list_insert_next
void cf_list_insert_pre(CFListHead* node, CFListHead* to_insert);
#define CFListInsertPre cf_list_insert_pre
#define CFListAppend  cf_list_insert_pre
#define CFListPrepend(__node, __to_ins) ({cf_list_insert_pre(__node, __to_ins);__to_ins;})
int cf_list_del(CFListHead* to_delete);
#define CFListDel   cf_list_del
int cf_list_empty(CFListHead *head);
#define CFListEmpty cf_list_empty

#define CFListContainerGetNext(__CNode, type, member) \
    container_of((__CNode)->member.next, type, member)
    
#define CFListContainerGetPrev(__CNode, type, member) \
	 container_of((__CNode)->member.prev, type, member)

#define CFListForeach(__head, __node)   \
    CFListHead* __node;\
    for(__node=(__head)->next; __node!=__head; __node=(__node)->next)

#define CFListForeachSafe(__head, __node)\
    CFListHead *__node, *__nextNode;\
    for(__node=(__head)->next, __nextNode=(__node)->next; __node!=__head; __node=__nextNode, __nextNode=(__node)->next)

#define CFListContainerForeach(__CHead, __CNode, __type, __member)\
    __type *__CNode;\
    for(__CNode=container_of((__CHead)->__member.next, __type, __member); __CNode != __CHead; __CNode=container_of((__CNode)->__member.next, __type, __member))

#define CFListContainerForeachSafe(__CHead, __CNode, __type, __member)\
    __type *__CNode, *__nextNode;\
    for(__CNode=container_of((__CHead)->__member.next, __type, __member),__nextNode=container_of((__CNode)->__member.next, __type, __member);\
        __CNode != __CHead;\
        __CNode=__nextNode, __nextNode=container_of((__CNode)->__member.next, __type, __member)\
        )

#define CFListForeachContainer(__Head, __CNode, __type, __member)\
    __type *__CNode;\
    CFListHead* __next;\
    for(__next=(__Head)->next, __CNode=container_of(__next, __type, __member);\
        __next != __Head; \
        __next=(__next)->next, __CNode=container_of(__next, __type, __member)\
        )

#define CFListForeachContainerSafe(__Head, __CNode, __type, __member)\
    __type *__CNode;\
    CFListHead* __next, *__tmpNext;\
    for(__next=(__Head)->next, __CNode=container_of(__next, __type, __member),  __tmpNext=(__next)->next;\
        __next != __Head;\
        __next=__tmpNext,  __CNode=container_of(__next, __type, __member), __tmpNext=(__next)->next\
        )        


/* GLib like list implementation */
typedef struct cf_g_list{
	CFListHead list;
	void* data;
} CFGList;

#define CFGListInit(__list) (__list=NULL)
#define CFGListExit(__list) (__list=NULL)
CFGList* CFGListAppend(CFGList* head, void* data) CF_GNUC_WARN_UNUSED_RESULT;
CFGList* CFGListPrepend(CFGList* head, void* data) CF_GNUC_WARN_UNUSED_RESULT;
#define CFGListGetData(__head)	((__head)->data)
CFGList* CFGListGetNodeFromData(CFGList* head, void* data);
CFGList* CFGListGetPrev(CFGList* head);
CFGList* CFGListGetNext(CFGList* head);
#define CFGListGetHead(__head) {if (__head) (__head)->data; else NULL;}
#define CFGListGetTail(__head) CFGListGetPrev(__head)
CFGList* CFGListDel(CFGList* head, CFGList* toDel) CF_GNUC_WARN_UNUSED_RESULT;
CFGList* CFGListDelByData(CFGList* head, void* toDel) CF_GNUC_WARN_UNUSED_RESULT;
CFGList* CFGListDelFreeData(CFGList* head, CFGList* toDel, int(*freeFunc)(void*)) CF_GNUC_WARN_UNUSED_RESULT;
#define CFGListForeach(__head, __node) \
	CFGList *__node = NULL, *__checkNode = NULL; CFListHead *__nextNode = NULL; \
	if (__head) \
		for (__node=__head, __nextNode=(__node)->list.next; \
				__checkNode!=__head&&__node&&__head; \
				__head?(__checkNode=__node=container_of(__nextNode, CFGList, list)):NULL, __head?(__nextNode=(__node)->list.next):NULL)
#endif

