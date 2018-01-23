#ifndef _CF_RTP_PAY_H_
#define _CF_RTP_PAY_H_

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

# ifdef USE_UCLIB
#include <endian.h>
#define __ORDER_BIG_ENDIAN__ __BIG_ENDIAN
#endif 

#define CF_DEFAULT_MUPS 548
#define CF_RTP_HEAD_MIN_SIZE    12

typedef int(*CFRtpFrameProcess)(void* rtpBuf, int len, void* userData);

typedef enum {
    CF_RTP_PAYLOAD_H264 = 0,
}CFRtpPayload;

typedef struct {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint8_t v:2;
    uint8_t p:1;
    uint8_t x:1;
    uint8_t cc:4;
#else
    uint8_t cc:4;
    uint8_t x:1;
    uint8_t p:1;
    uint8_t v:2;
#endif

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint8_t m:1;
    uint8_t pt:7;
#else
    uint8_t pt:7;
    uint8_t m:1;
#endif
    uint16_t sn:16;
    
    uint32_t ts;
    uint32_t ssrc;
    
    /* CSRC list */
    uint32_t csrc;
}__attribute__((__packed__ )) CFRtpHdr;

typedef struct {
    #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint8_t fz:1;
    uint8_t nalRefIdc:2;
    uint8_t type:5;
    #else
    uint8_t type:5;
    uint8_t nalRefIdc:2;
    uint8_t fz:1;
    #endif
}__attribute__((__packed__ )) CFNaluHdr;

typedef struct {
    #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint8_t s:1;
    uint8_t e:1;
    uint8_t r:1;
    uint8_t type:5;
    #else
    uint8_t type:5;
    uint8_t r:1;
    uint8_t e:1;
    uint8_t s:1;
    #endif
}__attribute__((__packed__ )) CFFuAHdr;

typedef struct cf_rtp_sender {
    int mups;   /* max udp packet size, safe: 548 , typical: 1024, max: 1472*/
    uint8_t* rtpBuf;
    
    CFRtpPayload payload;
    uint16_t sn;
    int writed;
}CFRtpPay;

int CFRtpPayInit(CFRtpPay* rp, int mups, 
        uint8_t pt, CFRtpPayload payload, uint32_t ssrc);

int CFRtpPayGenFrames(CFRtpPay* rp, uint8_t* dataPtr, int dataSize, uint32_t ts, CFRtpFrameProcess process, void* userData);

int CFRtpPayExit(CFRtpPay* rp);

#endif
