#ifndef _CF_MHB_H_
#define _CF_MHB_H_
#include <sys/socket.h>
#include "cf_common.h"
#include "cf_fdevent.h"
#include "cf_buffer.h"
#include "cf_list.h"

#define CF_MHB_HEADER_MAX_LEN   (8*1024)
#define CF_MHB_CONTENT_MAX_LEN   (8*1024)
#define CF_MHB_RECORD_MAX_LEN	512
#define CF_MHB_SERVER_MAX_BLOCKLOG	5
#define MAXIPADDRLEN			16

typedef struct cf_mhb_server CFMhbSvr;
typedef struct cf_mhb_server_conn CFMhbSvrConn;
typedef struct cf_mhb_header CFMhbHeader;

typedef enum {
    CF_MHB_ERR_NONE,
    CF_MHB_ERR_READ,
    CF_MHB_ERR_WRITE,
    CF_MHB_ERR_INTERNAL,
}CFMhbError;

typedef enum {
    CF_MHB_SVR_CB_NEW_CONN, /* para0: CFMhbSvrConn* sc, para1: NULL, para2: NULL, para3: NULL */
}CFMhbSvrCbReason;

typedef enum {
    CF_MHB_SVR_CONN_CB_REQ_HEADERS_RECVED,  /* para0: NULL, para1: NULL, para2: NULL, para3: NULL */
    CF_MHB_SVR_CONN_CB_REQ_BODY_READABLE, /* para0: uint8_t* buf, para1: size_t* sz, para2: NULL, para3: NULL */
    CF_MHB_SVR_CONN_CB_RESP_BODY_WRITABLE, /* para0: NULL, para1: NULL, para2: NULL, para3: NULL */
    
    CF_MHB_SVR_CONN_CB_DISCONNECTED, /* para0: NULL, para1: NULL, para2: NULL, para3: NULL */
    CF_MHB_SVR_CONN_CB_ERR  /* para0: CFMhbError* err, para1: NULL, para2: NULL, para3: NULL */
}CFMhbSvrConnCbReason;

typedef void(*CFMhbSvrCallBack)(CFMhbSvr* svr, CFMhbSvrCbReason cbReason, void* para0, void* para1, void* para2, void* para3, void* userData);
typedef void(*CFMhbSvrConnCallBack)(CFMhbSvrConn* sc, CFMhbSvrConnCbReason cbReason, void* para0, void* para1, void* para2, void* para3, void* userData);

struct cf_mhb_server {
    CFFdevents* evts;
    
    struct sockaddr* sockAddr;
    socklen_t sockAddrLen;
    
    int fd;
    CFFdevent* readEvt;
    CFListHead conns;
    CFMhbSvrCallBack cb;
    void* userData;
};

struct cf_mhb_header {
    char* key;
    char* value;
    CFListHead list;
};

#define CF_MHB_SVR_CONN_RD_BUF_SIZE 1024*2
#define CF_HMB_START_HEADER_MAX_PARTS 10
struct cf_mhb_server_conn {
    CFMhbSvr* server;
    
    struct sockaddr* clientSockAddr;
    socklen_t clientSockAddrLen;
    
    CFStreamFinder sf;
    char* reqStartHeaders[CF_HMB_START_HEADER_MAX_PARTS];
    CFListHead reqHeaders;
    char rdBuf[CF_MHB_HEADER_MAX_LEN];
    int rdBufSz;
    int lastParsed;
    
    char* respStartHeaders[CF_HMB_START_HEADER_MAX_PARTS];
    CFListHead respHeaders;
    CFBuffer wrtBuf;
    int writed;
    
    int fd;
    CFFdevent* rdEvt;
    CFFdevent* wrEvt;
    
    void *userData; /* store user data */
    
    CFMhbSvrConnCallBack cb;
    
    enum {
        CF_MHB_SVR_CONN_ST_RD_START_HEADER = 0,
        CF_MHB_SVR_CONN_ST_RD_HEADERS,
        CF_MHB_SVR_CONN_ST_RD_BODY,
        CF_MHB_SVR_CONN_ST_PROCESS,
        CF_MHB_SVR_CONN_ST_WR_HEADERS,
        CF_MHB_SVR_CONN_ST_WR_BODY
    }status;
    
    BOOL toBeDisConn;
    CFListHead list;
};

int CFMhbSvrInit(CFMhbSvr* svr, struct sockaddr* sockAddr, socklen_t sockLen, CFMhbSvrCallBack cb, void* userData, CFFdevents *events);

int CFMhbSvrExit(CFMhbSvr* svr);

void* CFMhbSvrGetUserData(CFMhbSvr* svr);

void CFMhbSvrConnSetCallBack(CFMhbSvrConn* sc, CFMhbSvrConnCallBack cb);

char** CFMhbSvrConnGetReqStartHeader(CFMhbSvrConn* sc);

CFMhbHeader* CFMhbSvrConnGetReqHeader(CFMhbSvrConn* sc, const char* header);

const char* CFMhbSvrConnGetReqHeaderValue(CFMhbSvrConn* sc, const char* header);

CFMhbHeader* CFMhbSvrConnGetRespHeader(CFMhbSvrConn* sc, const char* header);


void CFMhbSvrConnSetRespStartHeaders(CFMhbSvrConn* sc, const char* parts[CF_HMB_START_HEADER_MAX_PARTS], size_t len);

int CFMhbSvrConnAddRespHeader(CFMhbSvrConn* sc, const char* key, int keyLen, const char* value, int valueLen);

int CFMhbSvrConnDelRespHeader(CFMhbSvrConn* sc, const char* key);

int CFMhbSvrConnReqBodyReadFinished(CFMhbSvrConn* sc);

int CFMhbSvrConnMonitorWritable(CFMhbSvrConn* sc, BOOL monitor);

int CFMhbSvrConnWriteBody(CFMhbSvrConn *sc, const uint8_t* buf, size_t sz);

int CFMhbSvrConnFinishWriteBody(CFMhbSvrConn* sc);

void CFMhbSvrConnDisconnect(CFMhbSvrConn* sc);

void CFMhbSvrConnSetUserData(CFMhbSvrConn *sc, void* userData);

void* CFMhbSvrConnGetUserData(CFMhbSvrConn *sc);

void CFMhbSvrConnGetClientSockAddr(CFMhbSvrConn* sc, struct sockaddr** sockAddr, socklen_t* sockLen);

CFMhbSvr* CFMhbSvrConnGetMhbSvr(CFMhbSvrConn* sc);
#endif
