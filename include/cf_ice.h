#ifndef _CF_ICE_H_
#define _CF_ICE_H_
#include <stdio.h>
#include <stdlib.h>
#include <pjlib.h>
#include <pjlib-util.h>
#include <pjnath.h>
#include "cf_common.h"
#include "cf_list.h"

#define CF_ICE_FOUND_MAX_LEN    64
#define CF_ICE_ADDR_MAX_LEN (sizeof("11:1222:333:444:555:666")-1)
#define CF_ICE_MAX_CAND 20

typedef enum {
    CF_ICE_ROLE_CONTROLLING,
    CF_ICE_ROLE_CONTROLLED
}CFIceRole;

typedef enum {
    CF_ICE_CAND_TYPE_HOST = 0, 
    CF_ICE_CAND_TYPE_SRFLX, 
    CF_ICE_CAND_TYPE_PRFLX, 
    CF_ICE_CAND_TYPE_RELAYED, 
    CF_ICE_CAND_TYPE_COUNT,
    CF_ICE_CAND_TYPE_UNKNOWN,
}CFIceCandType;

typedef struct {
    CFIceCandType 	type;   /* must */
    int status;
    int compId; /* must */
    uint8_t 	transportId;    
    uint8_t 	localPref;
    char 	foundation[CF_ICE_FOUND_MAX_LEN+1]; /* must */
    uint32_t 	prio;   /* must */
    char addr[CF_ICE_ADDR_MAX_LEN+1];   /* must */
    uint16_t addrPort;
    char baseAddr[CF_ICE_ADDR_MAX_LEN+1];
    uint16_t baseAddrPort;
    char relAddr[CF_ICE_ADDR_MAX_LEN+1];
    uint16_t relAddrPort;
}CFIceCandidate;

typedef struct {
    struct {
        int	    max_host;
        pj_bool_t   regular;
        pj_str_t    stun_srv;
        pj_str_t    turn_srv;
        pj_bool_t   turn_tcp;
        pj_str_t    turn_username;
        pj_str_t    turn_password;
        pj_bool_t   turn_fingerprint;
        const char *log_file;
        pj_str_t    ns;
    } opt;
    pj_caching_pool	 cp;
    pj_pool_t		*pool;
    pj_thread_t		*thread;
    pj_bool_t		 thread_quit_flag;
    pj_ice_strans_cfg	 ice_cfg;
    FILE		*log_fhnd;
    CFListHead conns;
}CFIceAgent;

typedef enum {
    CF_ICE_CONN_CB_ERR,
    CF_ICE_CONN_CB_GATHER_DONE,
    CF_ICE_CONN_CB_CONN_READY
} CFIceConnCbReason;



typedef struct {
    CFIceAgent *agent;
    
    pj_ice_strans	*strans;
    
    struct {
        char ufrag[80];
        char pwd[80];
        unsigned candCount;
        pj_ice_sess_cand cands[CF_ICE_MAX_CAND];
    } remoteInfo;
    
    void* cb;
    void* dataReady;
    void *userData;
    CFListHead list;
}CFIceConn;

typedef void(*CFIceConnCallBack)(CFIceAgent* agent, CFIceConn* conn, 
        void* userData, CFIceConnCbReason reason, 
        void* data1, void* data2, void* data3, void* data4);
typedef void(*CFIceConnectionDataReady)(CFIceAgent* agent, CFIceConn* conn, void* userData, char* data, int size);


int CFIceAgentInit(CFIceAgent* agent, const char* stunSvr, const char* turnSvr, BOOL turnTcp, const char* turnUsername, const char* turnPasswd, void* userData);
int CFIceAgentExit(CFIceAgent* agent);
CFIceAgent* CFIceAgentNew(const char* stunSvr, const char* turnSvr, BOOL turnTcp, const char* turnUsername, const char* turnPasswd, void* userData);
void CFIceAgentDestroy(CFIceAgent* agent);

CFIceConn* CFIceAgentNewConn(CFIceAgent* agent, int component, BOOL turnFingerprint, CFIceConnCallBack cb, void* userData);

int CFIceAgentStartGatherLocalCandidates(CFIceAgent* agent, CFIceConn* conn, CFIceRole role);

int CFIceAgentSetRemoteCandidates(CFIceAgent* agent, CFIceConn* conn, const CFIceCandidate* cands, 
        int count, int* settedCount,
        const char* ufrag, const char* pwd);
int CFIceAgentGetLocalUfragPwd(CFIceAgent* agent, CFIceConn* conn, const char** ufrag, const char** pwd);
int CFIceAgentGetRemoteUfragPwd(CFIceAgent* agent, CFIceConn* conn, const char** ufrag, const char** pwd);
int CFIceAgentGetLocalCandidates(CFIceAgent* agent, CFIceConn* conn, uint32_t compId, CFIceCandidate* cands, int* size);


int CFIceAgentStartNegoConn(CFIceAgent* agent, CFIceConn* conn);
int CFIceAgentSetConnDataReadyCb(CFIceAgent* pAgent, CFIceConn* conn, CFIceConnectionDataReady dataReady);
int CFIceAgentSendData(CFIceAgent* agent, CFIceConn* conn, uint32_t compId, char* data, int size);

int CFIceAgentDestroyConn(CFIceAgent* agent, CFIceConn* conn);  /* remember to free foundation!! */

const char* CFIceGetCandTypeName(CFIceCandType type);
CFIceCandType CFIceGetCandTypeByName(const char* name);

#endif
