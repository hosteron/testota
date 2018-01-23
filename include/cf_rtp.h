#ifndef _CF_RTP_H_
#define _CF_RTP_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "cf_fdevent.h"
#include "cf_buffer.h"
#include "cf_pipe.h"
#include "cf_common.h"
#include "lcf_log.h"

#ifndef CF_DEFAULT_RTP_CACHE_FRAMES
#define CF_DEFAULT_RTP_CACHE_FRAMES 30
#endif
#define CF_DEFAULT_MUPS 548
#define CF_RTP_HEAD_MIN_SIZE    12
#define CF_RTP_SENDER_PORT_START    5000
#define CF_RTP_SENDER_PORT_END    65534

typedef enum {
    CF_RTP_PAYLOAD_H264 = 0,
}CFRtpPayload;

typedef struct {
    uint32_t timestamp;
    CFBuffer buf;
}CFRtpCache;

typedef struct cf_rtp_sender {
    int mups;   /* max udp packet size, safe: 548 , typical: 1024, max: 1472*/
    uint8_t* rtpBuf;
    struct sockaddr_in destSockAddr;
    in_port_t selfPort;
    int sock;
    struct {
        uint32_t v:2;
        uint32_t p:1;
        uint32_t x:1;
        uint32_t cc:4;
        
        uint32_t m:1;
        uint32_t pt:7;
        
        uint32_t sn:16;
        
        uint32_t ts;
        uint32_t ssrc;
        
        /* CSRC list */
        int csrcLen;
        uint32_t *csrc;
    }rtpHdr;
    CFFdevents* evts;
    CFFdevent wrtEvt;
    BOOL wrtEvtInited;
    CFRtpPayload payload;
    CFRtpCache cacheBufs[CF_DEFAULT_RTP_CACHE_FRAMES];
    CFPipe fullBufs;
    int writed;
    CFPipe emptyBufs;
}CFRtpSender;

int CFRtpSenderInit(CFRtpSender* rs, int mups, 
        uint8_t pt, CFRtpPayload payload, uint32_t ssrc,
        CFFdevents* evts);

int CFRtpSenderSetSockFd(CFRtpSender* rs, int sockFd);

int CFRtpSenderAutoSetSockFd(CFRtpSender* rs);

int CFRtpSenderSetDest(CFRtpSender* rs, in_addr_t destAddr, in_port_t destPort);

uint16_t CFRtpSenderGetSelfPort(CFRtpSender* rs);

uint16_t CFRtpSenderGetDestPort(CFRtpSender* rs);

int CFRtpSenderSendFrame(CFRtpSender* rs, void* buf, int len, uint32_t ts);

int CFRtpSenderExit(CFRtpSender* rs);

#endif
