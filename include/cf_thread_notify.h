#ifndef _CF_THREAD_NOTIFY_H_
#define _CF_THREAD_NOTIFY_H_
#include "cf_fdevent.h"

typedef struct cf_thread_notify CFThreadNotify;

typedef void(*CFThreadNotifyCb)(CFThreadNotify* ntf, void* userData);

struct cf_thread_notify {
    int pipeFd[2];
    CFFdevents* evts;
    CFFdevent* rdEvt;
    
    CFThreadNotifyCb cb;
    void* userData;
};

CFThreadNotify* CFThreadNotifyNew(CFThreadNotifyCb cb, void* userData, CFFdevents* evts);
void CFThreadNotifyDestroy(CFThreadNotify* ntf);
int CFThreadNotifyNotify(CFThreadNotify* ntf);
#endif
