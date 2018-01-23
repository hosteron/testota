/* COPYRIGHT_CHUNFENG */
#ifndef _CF_NETWORKD_H_
#define _CF_NETWORKD_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include "cf_common.h"

int CFIfConfig(unsigned int ioc_req, void * req);
int CFGetIfFlags(const char* eth, short* flags);
int CFIsLinkOk(const char* ifname, BOOL *ok);
int CFGetIfAddr(const char* ifname, struct sockaddr* addr);
int CFGetIfMask(const char* ifname, struct sockaddr* addr);
int CFGetIfBroadcastAddr(const char* ifname, struct sockaddr* addr);
#endif

