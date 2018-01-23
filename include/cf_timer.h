/* COPYRIGHT_CHUNFENG */
#ifndef _CF_TIMER_H_
#define _CF_TIMER_H_
#include <time.h>
#include <sys/time.h>
#include "cf_list.h"
typedef struct cf_timer CFTimer;
typedef  void(*CFTimerAction)(CFTimer* tmer, void* data);
#ifndef CONFIG_TIMER_USE_UALARM
#include <sys/timerfd.h>
#include "cf_fdevent.h"
struct cf_timer{
    const char* name;
    CFFdevents* evts;
    CFFdevent tmrRdEvt;
    CFTimerAction actionFunc;
    void* userData;
};

int CFTimerSystemInit(CFFdevents* evts);

int CFTimerSystemExit();

int CFTimerInit(CFTimer* tmr, const char* name, 
        const struct itimerspec *time, CFTimerAction actionFunc, void* userData, 
        CFFdevents* evts);

int CFTimerInitStopped(CFTimer* tmr, const char* name, 
        CFTimerAction actionFunc, void* userData, 
        CFFdevents* evts);

CFTimer* CFTimerNew(const char* name, 
        const struct itimerspec *time, CFTimerAction actionFunc, void* userData, 
        CFFdevents* evts);

int CFTimerMod(CFTimer* tmr, CFTimerAction actionFunc, 
        const struct itimerspec *newTime, struct itimerspec *oldTime);

int CFTimerModTime(CFTimer* tmr, time_t start_sec, long start_nsec,
        time_t intv_sec, long intv_nsec);
        
int CFTimerCancel(CFTimer* timer);

int CFTimerExit(CFTimer* tmr);

int CFTimerDestroy(CFTimer* tmr);

typedef CFTimer*(*CFSimpleTimerHndl)(CFTimer* tmr, void* usrData);

int CFSimpleTimer(const char* name, CFSimpleTimerHndl hndl, void* usrData, 
        int start_sec, int start_nsec,
        int intv_sec, int intv_nsec,
        CFFdevents* evts);

#define CFTimersTrigger()

#else
struct cf_timer{
    const char* name;
    struct timeval start_clock;
    struct timeval expires;
    void* data;
    void(*function)(void* data);
    CFListHead list;
    CFListHead processList;
};
int CFTimerInit(CFTimer* tmr, const char* name, void(*function)(void* data), void* data);
CFTimer* CFTimerNew(const char* name, void(*function)(void* data), void* data);
int CFTimerDestroy(CFTimer* timer);
int CFTimerAdd(CFTimer* tmr, struct timeval* expires);
int CFTimerAdd2(CFTimer* tmr, int sec, int msec);
int CFTimerCancel(CFTimer* timer);
int CFTimerExit(CFTimer* timer);
int CFTimerSystemInit(int checkIntval);
int CFTimerSystemExit();
int CFTimersTrigger();	/* this function must be called cyclly */

#endif

#endif
