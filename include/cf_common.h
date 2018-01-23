/* COPYRIGHT_CHUNFENG */
#ifndef _CF_COMMON_H_
#define _CF_COMMON_H_
#include <stdint.h>
#include <stdlib.h>
#include <cf_string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include "cf_config.h"

#ifdef __GNUC__
#define CF_GNUC_WARN_UNUSED_RESULT __attribute__ ((warn_unused_result))
#else
#define CF_GNUC_WARN_UNUSED_RESULT
#endif

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#if UINTPTR_MAX == 0xffffffff
/* 32-bit */
#define int8  char
#define uint8  unsigned char
#define int16  short
#define uint16  unsigned short
#define int32  int
#define uint32  unsigned int
#define int64  long long
#define uint64  unsigned long long
#elif UINTPTR_MAX == 0xffffffffffffffff
/* 64-bit */
#define int8  char
#define uint8  unsigned char
#define int16  short
#define uint16  unsigned short
#define int32  int
#define uint32  unsigned int
#define int64  long long
#define uint64  unsigned long long
#else
/* wtf */
#define int8  char
#define uint8  unsigned char
#define int16  short
#define uint16  unsigned short
#define int32  int
#define uint32  unsigned int
#define int64  long long
#define uint64  unsigned long long
#endif

void uint32_set_bits(uint32* reg, uint32 mask);
void uint32_clear_bits(uint32* reg, uint32 mask);
void uint32_modify_bits(uint32* reg, uint32 mask, uint32 value);

#ifndef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
#endif
#endif
#define container_of(__pointer, __type, __member) ((__type*)((char*)__pointer - offsetof(__type, __member)))

#define CF_CONST_STR_LEN(__str)   __str, (sizeof(__str)-1)
#define CF_CLEAR(__t)	memset(__t, 0, sizeof(*(__t)));

#define CF_MIN(__a, __b) (((__a)<(__b))?(__a):(__b))
#define CF_MAX(__a, __b) (((__a)>(__b))?(__a):(__b))
#define CF_ALIGN(__x, __a)	(((__x + __a - 1) / __a) * __a)

void CFHalfByteToHex(char hex[1], const char halfByte);
void CFByteToHex(char hex[2], const char byte);
int CFRawToHex(char* string, void* raw, size_t rawSize);

int cf_char_is_blank(char c);
void cf_char_strip(char** start, char** end, int strip_start, int strip_end);
char* strblank(const char* str);
char* strnblank(const char* str);

int CFStrToInt(const char* str, int* value);
int CFIntToString(char* str, int val);
long long cf_atoll_n(char* a, int n);
const char* cf_lltoa(long long int num);
int CFRandom();
const char* CFRandomStr(const char* prefix, int prefixSz, const char* suffix, int suffixSz, int randomStrSz);
typedef struct {
    uint64_t id;
    const char* string;
}CFIdStringPair;
int CFIdStringPairGetId(CFIdStringPair* pairs, const char* string, uint64_t* id);
const char* CFIdStringPairGetString(CFIdStringPair* pairs, uint64_t id);

/* Process management */
int cf_popen(const char*  args[], int* from_stdout, int* from_errout, int* to_stdin, int* pid_out);
#define CFPopen cf_popen
int cf_system(const char* args[], CFString* stdOutput, CFString* errorOutput);
#define CFSystem    cf_system
int cf_system2(CFString* stdOutput, CFString* errorOutput, const char* arg1, ...);
#define CFSystem2    cf_system2

/* Shared memory */
void* cf_create_shm(const char* key_path, size_t size);
int cf_delete_shm(const char* key_path);
void* cf_get_shm(const char* key_path);

/* I/O routines */
int CFFdPrintf(int fd, const char *fmt, ...);
int cf_string_to_file(const char* file_path, const char* str);
int CFIntToFile(const char* file, int val);
#define CFStringToFile  cf_string_to_file
int CFSafeStringToFile(const char* path, const char* str);
int cf_file_to_string(CFString* str, const char* file_path);
#define CFFileToString  cf_file_to_string
int cf_fd_to_string(CFString* str, int fd, int len);
#define CFFdToString    cf_fd_to_string
int CFFileToFile(const char* dest, const char* from, mode_t mode);
int CFFileToBuf(char* buf, int size, const char* filePath);
int CFFdToBuf(char* buf, int size, int fd);
int CFBufToFd(int fd, char* buf, int size);
int CFBufToFile(const char* file, char* buf, int size);
int CFFileToInt(int* val, const char* filePath);
#define CF_ASYNC_IO_OK    0
#define CF_ASYNC_IO_CLOSED    -1
#define CF_ASYNC_IO_FAILED    -2
int CFAsyncWrite(int fd, const void* buf, int bufLen, int* writed, int* writedThisTime);
int CFAsyncRead(int fd, void* buf, int bufLen, int* readed, int* readedThisTime);

int CFConnectToUnixSocket(const char* unixSockPath, int* fd, mode_t oFlag);

/* Daemon routines */
int CFDaemon(const char* pidFile, int lockPort);
int CFStopDaemon(const char* pidFile);
BOOL CFIsDaemonExited(int lockPort);
int cf_get_process_path(CFString* path, pid_t pid);
int cf_get_process_dir(CFString* dir, pid_t pid);

/* Filesystem utilities */
int cf_file_to_dir(CFString* dir, const char* file);
int CFFileIsCharDevice(const char* filePath);
int CFFileIsRegularFile(const char* filePath);
int CFFileIsFifo(const char* filePath);
void cf_mkdir(const char* dir, mode_t mode);
int cf_get_disk_uuid(const char* dev, CFString* uuid_out);
int cf_gen_grub2_cfg(const char* cfg_file, char* boot_dev, char* root_dev);

/* serial setup */
int CFSetupSerial(int fd, int nSpeed, int8_t nData, char nParity, int8_t nStop);

/* network */
#define MAC_PRINTF_MASK	"%02X:%02X:%02X:%02X:%02X:%02X"
#define MAC_PRINTF_PARAM(__mac)	__mac[0], __mac[1], __mac[2], __mac[3], __mac[4], __mac[5]

#define MAC_SCANF_MASK	"%x:%x:%x:%x:%x:%x"
#define MAC_SCANF_PARAM(__mac)	(uint32_t*)&__mac[0], (uint32_t*)&__mac[1], (uint32_t*)&__mac[2], (uint32_t*)&__mac[3], (uint32_t*)&__mac[4], (uint32_t*)&__mac[5]

int CFNewSockAddrFromString(const char* str, struct sockaddr** sockAddr, socklen_t* sockLen);
int CFSockAddrToString(struct sockaddr* sockAddr, socklen_t sockLen, char* str, size_t bufSz);
int CFSockAddrToIpString(struct sockaddr* sockAddr, socklen_t sockLen, char* str, size_t bufSz);

/* stream utility */
typedef struct CFStreamFinder {
	char* stuf;
	int stufSz;
	int n;
} CFStreamFinder;

int CFStreamFinderInit(CFStreamFinder* sf);

int CFStreamFinderStartFind(CFStreamFinder* sf, const char* stuf, int stufSz);

BOOL CFStreamFinderParseOne(CFStreamFinder* sf, char ch);

BOOL CFStreamFinderParse(CFStreamFinder* sf, char* buf, int size, int* ndlEndPos);

void CFStreamFinderRestartFind(CFStreamFinder* sf);

int CFStreamFinderExit(CFStreamFinder* sf);


char CFToHex(char ch, BOOL upcase);
char CFFromHex(char code);
void CFBufFromHex(char* buf, const char* hex, int size);
void CFBufToHex(char* hex, BOOL upcase, const char* buf, int size);

int CFSubTimeval(struct timeval* result, struct timeval* begin, struct timeval* end);


/* system settings */

int CFSetCurrentTime(int year, int month, int date, int hour, int minute);
int CFGetCurrentTime(int* year, int* month, int* date, int* hour, int* minute);
int CFSetTimeZone(const char* tz);
char* CFGetTimeZone();
#endif

