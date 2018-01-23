/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pthis program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#ifndef _CF_CMD_H_
#define _CF_CMD_H_
#include <cf_common.h>
#include <cf_fdevent.h>
#include <cf_string.h>
#include <cf_buffer.h>

#define CF_CMD_PROTOCL_VER "CFCmd/0.1"
#define CF_CMD_PROTOCOL_VER_LEN    sizeof(CF_CMD_PROTOCL_VER)
typedef struct mds_cmd_request{
    unsigned char version[CF_CMD_PROTOCOL_VER_LEN];  /* Also used for  maigc */
    uint32 bodySize;
    CFBuffer body; /* pointer to packet body, body begins with guest's name(NULL terminated string)*/
    uint16 chksum;
}CFCmdReq;
int CFCmdReqInit(CFCmdReq* req);
int CFCmdReqExit(CFCmdReq* req);
int CFCmdReqChksum(CFCmdReq* req);
BOOL CFCmdReqChksumOK(CFCmdReq* req);

typedef struct mds_cmd_response{
    unsigned char version[CF_CMD_PROTOCOL_VER_LEN];  /* Also used for  magic */
    uint32 bodySize;
    CFBuffer body;
    uint16 chksum;
}CFCmdResp;
int CFCmdRespInit(CFCmdResp*);
int CFCmdRespExit(CFCmdResp*);
int CFCmdRespChksum(CFCmdResp*);
BOOL CFCmdRespChksumOK(CFCmdResp*);
BOOL CFCmdRespIsHeadValid(CFCmdResp* head);

typedef struct mds_cmd_ctl CFCmdCtl;
struct mds_cmd_ctl{
    BOOL async;
    CFString unixSockPath;
    int fd;
    CFCmdCtl*(*processResponse)(CFCmdCtl* ctlReq, CFBuffer* respBuf, void* userPtr);
    void* userPtr;

    CFFdevent readEvt;
    CFCmdReq request;
    int tmpReaded;
    CFFdevent writeEvt;
    CFCmdResp response;
    int tmpWrited;

    CFFdevents* events;
    enum{
        CF_CMD_CTL_ST_IDLE,
        CF_CMD_CTL_ST_CONNECTED_IDLE,
        CF_CMD_CTL_ST_WRITE_REQ_VER,
        CF_CMD_CTL_ST_WRITE_REQ_BODY_SIZE,
        CF_CMD_CTL_ST_WRITE_REQ_BODY,
        CF_CMD_CTL_ST_WRITE_REQ_CHKSUM,
        CF_CMD_CTL_ST_READ_RESP_VER,
        CF_CMD_CTL_ST_READ_RESP_BODY_SIZE,
        CF_CMD_CTL_ST_READ_RESP_BODY,
        CF_CMD_CTL_ST_READ_RESP_CHKSUM,
        CF_CMD_CTL_ST_PROCESS_RESP
    } status;
    enum{
        CF_CTL_REQ_RESULT_OK,
        CF_CTL_REQ_RESULT_ERROR
    } reqResult;
};
int CFCmdCtlInit(CFCmdCtl* pthis, CFFdevents* events);
int CFCmdCtlConnect(CFCmdCtl* ctl, const char* unixSockPath);
int CFCmdCtlRequest(CFCmdCtl* ctl, void* reqData, int reqDataLen, 
        CFCmdCtl*(*processResponse)(CFCmdCtl* ctlReq, CFBuffer* respBuf, void* userPtr), void* userPtr);
int CFCmdCtlExit(CFCmdCtl* ctl);
int CFCmdCtlResetToIdle(CFCmdCtl* pthis);
CFCmdCtl* CFCmdCtlNew(CFFdevents* events);
int CFCmdCtlDestory(CFCmdCtl* pthis);
int CFCmdCtlGetResponseBodySize(CFCmdCtl* pthis);
void* CFCmdCtlGetResponseBodyPtr(CFCmdCtl* pthis);

typedef struct mds_cmd_svr CFCmdSvr;
typedef struct mds_cmd_svr_sock_conn {
    CFCmdSvr* cmdSvr;
    const char* unixSockPath;  /* unix socket path */
    int fd;
    CFFdevent readEvt;
}CFCmdSvrSockConn;

typedef struct mds_cmd_svr_data_conn{
    CFCmdSvr* cmdSvr;
    int fd;

    CFFdevent readEvt;
    CFCmdReq request;
    int tmpReaded;
    CFFdevent writeEvt;
    CFCmdResp response;
    int tmpWrited;
    enum{
        CF_CMD_SVR_DATA_CONN_ST_IDLE,
        CF_CMD_SVR_DATA_CONN_ST_READ_REQ_VER,
        CF_CMD_SVR_DATA_CONN_ST_READ_REQ_BODY_SIZE,
        CF_CMD_SVR_DATA_CONN_ST_READ_REQ_BODY,
        CF_CMD_SVR_DATA_CONN_ST_READ_REQ_CHKSUM,
        CF_CMD_SVR_DATA_CONN_ST_PROCESS,
        CF_CMD_SVR_DATA_CONN_ST_WRITE_RESP_VER,
        CF_CMD_SVR_DATA_CONN_ST_WRITE_RESP_BODY_SIZE,
        CF_CMD_SVR_DATA_CONN_ST_WRITE_RESP_BODY,
        CF_CMD_SVR_DATA_CONN_ST_WRITE_RESP_CHKSUM

    } status;

    CFListHead list;
}CFCmdSvrDataConn;
CFCmdSvrDataConn* CFCmdSvrDataConnNew(CFCmdSvr* svr, int fd);
int CFCmdSvrDataConnInit(CFCmdSvrDataConn* pthis, CFCmdSvr* svr, int fd);
int CFCmdSvrDataConnFree(CFCmdSvrDataConn* pthis);
int CFCmdSvrDataConnExit(CFCmdSvrDataConn* pthis);

struct mds_cmd_svr{
        void* usrData;
        CFCmdSvrSockConn sockConn;
        CFCmdSvrDataConn dataConnHead;
    int(*processRequest)(CFCmdSvrDataConn* dc, CFBuffer* reqBuf, CFBuffer* respBuf, void* usrData);
    CFFdevents* events;
};
int CFCmdSvrInit(CFCmdSvr* pthis, const char* unixSockPath, int maxDataConns,
                int(*processRequest)(CFCmdSvrDataConn* dc, CFBuffer* reqBuf, CFBuffer* respBuf, void* usrData), void* usrData,
                CFFdevents* events);
int CFCmdSvrExit(CFCmdSvr* pthis);
int CFCmdSvrDataConnResponse(CFCmdSvrDataConn* pthis);
#endif
