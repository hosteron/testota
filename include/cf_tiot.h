#ifndef _CF_TIOT_H_
#define _CF_TIOT_H_

#define CF_TIOT_ID_SZ 6

typedef struct tiot_manager CFTiotMan;

typedef enum {
    CF_TIOT_MAN_CB_ERROR,
    CF_TIOT_MAN_CB_NOTIFY,
}CFTiotManCbReason;

typedef void(*CFTiotTx)(CFTiotMan* man, const uint8_t* data, int size);
typedef void(*CFTiotManCb)(CFTiotMan* man, CFTiotManCbReason reason, void* userData, void* data1, void* data2);

struct tiot_manager {
    CFTiotTx tx;
    CFListHead devs;
    
    CFTiotManCb cb;
    void* userData;
};

typedef enum {
    CF_TIOT_DEV_SMART_SLOT,
    CF_TIOT_DEV_SMOKE_DETECTOR,
    CF_TIOT_DEV_A
}CFTiotDevType;

typedef struct {
    uint8_t id[CF_TIOT_ID_SZ];
    BOOL enable;
}CFTiotDevCtl;

typedef struct {
    uint8_t id[CF_TIOT_ID_SZ];
    BOOL enabled;
    BOOL online;
    BOOL powerlow;
}CFTiotDevInfo;

typedef struct {
    uint8_t id[CF_TIOT_ID_SZ];
    BOOL enabled;
    BOOL online;
    BOOL powerLow;
}CFTiotDevNotify;


typedef struct {
    CFTiotDevCtl baseCtl;
    BOOL on;
}CFTiotSmartSlotCtl;

typedef struct {
    CFTiotDevInfo baseInfo;
    BOOL on;
    BOOL ShortCircuit;
}CFTiotDevInfo;

typedef struct {
    CFTiotDevInfo baseNotify;
    BOOL on;
    BOOL ShortCircuit;
}CFTiotDevNotify;


int CFTiotManInit(CFTiotMan* man, CFTiotTx tx, CFTiotManCb cb, void* userData);
int CFTiotManExit(CFTiotMan* man);

int CFTiotManProcessRx(CFTiotMan* man, const uint8_t* data, int size);

int CFTiotManAddDev(CFTiotMan* man);

int CFTiotManDelDev(CFTiotMan* man, char id[CF_TIOT_ID_SZ]);

int CFTiotManGetDevCount(CFTiotMan* man);

CFListHead* CFTiotManGetDevIdList(CFTiotMan* man);

int CFTiotManEnableDev(CFTiotMan* man, BOOL enable);

int CFTiotManDevCtl(CFTiotMan* man, CFTiotDevCtl* ctl);

CFTiotDevInfo* CFTiotManGetDevInfo(CFTiotMan* man, char id[CF_TIOT_ID_SZ]);

CFTiotDevType CFTiotDevGetTypeById(const uint8_t id[CF_TIOT_ID_SZ]);
CFTiotDevType CFTiotDevInfoGetType(const CFTiotDevInfo *info);
CFTiotDevType CFTiotDevNotifyGetType(const CFTiotDevNotify *notify);
CFTiotDevType CFTiotDevCtlGetType(const CFTiotDevCtl *ctl);

#endif
