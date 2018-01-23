/* COPYRIGHT_CHUNFENG */
#ifndef CF_FDEVENT_H
#define CF_FDEVENT_H

#include <sys/select.h>
#include "cf_config.h"
#include "cf_list.h"

#define CF_EVT_DBG  "CF_EVT_DBG"
typedef struct cf_fdevent CFFdevent;
typedef struct cf_fdevents CFFdevents;
typedef int(*CFEventAction)(CFFdevents* events, CFFdevent* event, int fd, void* data);
#ifdef CONFIG_FD_EVENTS_BACKEND_SELECT

struct cf_fdevent{
    const char* name;
	int fd;
	CFEventAction read_action;
	CFEventAction write_action;
	CFEventAction exception_action;
	void *read_parameter;
	void *write_parameter;
	void * exception_parameter;
    CFListHead list;
    CFListHead toProcessList;
};

struct cf_fdevents{
	CFListHead eventHead;
    CFListHead toProcessHead;
	fd_set read_fdset;
	fd_set write_fdset;
	int read_max_fd;
	int write_max_fd;
};

CFFdevent* cf_fdevent_new(int fd, const char* name,
					CFEventAction read_action, void* read_parameter,
					CFEventAction write_action, void* write_parameter,
					CFEventAction exception_action, void* exception_parameter);
#define CFFdeventNew    cf_fdevent_new
int cf_fdevent_init(CFFdevent* self, int fd, const char* name,
					CFEventAction read_action,   /* NULL means no monitor on read ability */
					void* read_parameter,
					CFEventAction write_action,  /* NULL means no monitor on write ability */
					void* write_parameter,
					CFEventAction exception_action,  /* NULL means no monitor on write ability */
					void* exception_parameter);
#define CFFdeventInit   cf_fdevent_init
int cf_fdevent_free(CFFdevent* self);
#define CFFdeventFree   cf_fdevent_free
int cf_fdevent_append(CFFdevent* self, CFFdevent* new_event);
#define CFFdeventAppend cf_fdevent_append
int cf_fdevent_exit(CFFdevent* pthis);
#define CFFdeventExit   cf_fdevent_exit

int cf_fdevents_init(CFFdevents* pthis);
#define CFFdeventsInit  cf_fdevents_init
int cf_fdevents_exit(CFFdevents* pthis);
#define CFFdeventsExit  cf_fdevents_exit
CFFdevents* cf_fdevents_new();
#define CFFdeventsNew   cf_fdevents_new
int cf_fdevents_free(CFFdevents* self);
#define CFFdeventsFree  cf_fdevents_free
int cf_fdevents_add(CFFdevents* self, CFFdevent* new_event);
#define CFFdeventsAdd   cf_fdevents_add
int CFFdeventsAddIfNotAdded(CFFdevents* evts, CFFdevent* evt);
int cf_fdevents_del(CFFdevents* self, CFFdevent* event_to_del);
#define CFFdeventsDel   cf_fdevents_del
int cf_fdevents_del_all(CFFdevents* pthis);
#define CFFdeventsDelAll    cf_fdevents_del_all
int cf_fdevents_del_free(CFFdevents* self, CFFdevent* event_to_del);

#define CFFdeventsDelFree   cf_fdevents_del_free
int cf_fdevents_del_close(CFFdevents* pthis, CFFdevent* event);

#define CFFdeventsDelClose  cf_fdevents_del_close
int cf_fdevents_del_close_free(CFFdevents* pthis, CFFdevent* event);

#define CFFdeventsDelCloseFree  cf_fdevents_del_close_free
int cf_fdevents_trigger(CFFdevents* self);

#define CFFdeventsLoop  cf_fdevents_trigger
int CFFdeventGetFd(CFFdevent* evt);


#elif defined CONFIG_FD_EVENTS_BACKEND_GLIB
#include <glib.h>
typedef struct CF_GSource {
    GSource gSource;
    int fd;
    GPollFD pFd;
}CFGSource;

struct cf_fdevent{
    const char* name;
    int fd;
    union {
        CFEventAction rdAction;
        CFEventAction wrtAction;
        CFEventAction excepAction;
    }uAction;
    union {
        void *rdParam;
        void *wrtParam;
        void *exceptParam;
    }uParam;
    
    CFGSource* source;
    GSourceFuncs sourceFuncs;
    BOOL attached;
    
    CFFdevents* events;
};

struct cf_fdevents{
	GMainContext* mainCtx;
    GMainLoop* mLoop;
};

CFFdevent* CFFdeventNew(int fd, const char* name,
					CFEventAction read_action, void* read_parameter,
					CFEventAction write_action, void* write_parameter,
					CFEventAction exception_action, void* exception_parameter);

int CFFdeventInit(CFFdevent* self, int fd, const char* name,
					CFEventAction read_action,   /* NULL means no monitor on read ability */
					void* read_parameter,
					CFEventAction write_action,  /* NULL means no monitor on write ability */
					void* write_parameter,
					CFEventAction exception_action,  /* NULL means no monitor on write ability */
					void* exception_parameter);

int CFFdeventFree(CFFdevent* self);

int CFFdeventExit(CFFdevent* pthis);

int CFFdeventGetFd(CFFdevent* evt);

int CFFdeventsInit(CFFdevents* pthis);

int CFFdeventsExit(CFFdevents* pthis);

CFFdevents* CFFdeventsNew();

int CFFdeventsFree(CFFdevents* self);

int CFFdeventsAdd(CFFdevents* self, CFFdevent* newEvt);

int CFFdeventsDel(CFFdevents* self, CFFdevent* delEvt);

int CFFdeventsDelAll(CFFdevents* pthis);

int CFFdeventsLoop(CFFdevents* self);

#define CFFdeventsGetGMainContext(__evts)   ((__evts)->mainCtx)

#else
#include <sys/epoll.h>
#define FD_COUNT (1000)
struct cf_fdevent{
    const char* name;
    int fd;
    enum {
        CF_FDEVENT_READ,
        CF_FDEVENT_WRITE,
        CF_FDEVENT_EXCEPTION
    }type;
    union {
        CFEventAction rdAction;
        CFEventAction wrtAction;
        CFEventAction excepAction;
    }uAction;
    union {
        void *rdParam;
        void *wrtParam;
        void *exceptParam;
    }uParam;
    struct epoll_event epEvt;
    
//    BOOL toBeDel;
//    BOOL toBeExit;
 //   BOOL toBeFree;
};

struct cf_fdevents{
	int epFd;
    int rdEpFd;
    struct epoll_event rdEpEvt;
    int wrtEpFd;
    struct epoll_event wrtEpEvt;
    
    int exceptEpFd;
    struct epoll_event exceptEpEvt;
    
    struct epoll_event outEpEvts[3];
    struct epoll_event outEvts[100];
    
    unsigned int cnt;
    BOOL delAll;
};

CFFdevent* CFFdeventNew(int fd, const char* name,
					CFEventAction read_action, void* read_parameter,
					CFEventAction write_action, void* write_parameter,
					CFEventAction exception_action, void* exception_parameter);

int CFFdeventInit(CFFdevent* self, int fd, const char* name,
					CFEventAction read_action,   /* NULL means no monitor on read ability */
					void* read_parameter,
					CFEventAction write_action,  /* NULL means no monitor on write ability */
					void* write_parameter,
					CFEventAction exception_action,  /* NULL means no monitor on write ability */
					void* exception_parameter);

int CFFdeventFree(CFFdevent* self);

int CFFdeventExit(CFFdevent* pthis);

int CFFdeventGetFd(CFFdevent* evt);

int CFFdeventsInit(CFFdevents* pthis);

int CFFdeventsExit(CFFdevents* pthis);

CFFdevents* CFFdeventsNew();

int CFFdeventsFree(CFFdevents* self);

int CFFdeventsAdd(CFFdevents* self, CFFdevent* newEvt);

int CFFdeventsDel(CFFdevents* self, CFFdevent* delEvt);

int CFFdeventsDelAll(CFFdevents* pthis);

int CFFdeventsLoop(CFFdevents* self);
#endif
#endif
