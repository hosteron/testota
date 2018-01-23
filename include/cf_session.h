#ifndef _CF_AUTH_SESSION_
#define _CF_AUTH_SESSION_
#include <time.h>
#include "cf_common.h"

#define CF_SESSION_PHRASE_LEN  (25*2)
typedef struct{
    char sessionPhrase[CF_SESSION_PHRASE_LEN+1];
    time_t authTime;
    time_t expireSeconds;
}CFSession;

int CFSessionInit(CFSession* session, const char sPh[CF_SESSION_PHRASE_LEN], time_t expireSeconds);
CFSession* CFSessionNew(const char sPh[CF_SESSION_PHRASE_LEN], time_t expireSeconds);
BOOL CFSessionTimeout(CFSession* session);
int CFSessionAuth(CFSession* session, const char phrase[CF_SESSION_PHRASE_LEN+1]);
int CFSessionUpdate(CFSession* session, const char phrase[CF_SESSION_PHRASE_LEN+1]);
int CFSessionFree(CFSession* toFree);
#endif
