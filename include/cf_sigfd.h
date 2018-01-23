/* COPYRIGHT_CHUNFENG */
#ifndef _CF_SIGFD_H_
#define _CF_SIGFD_H_

int cf_sigfd_open(int s, ...);
#define CFSigFdOpen cf_sigfd_open
void cf_sigfd_close();
#define CFSigFdClose    cf_sigfd_close
int cf_sigfd_get_next_signal(int fd);
#define CFSigFdGetNextSignal  cf_sigfd_get_next_signal
#endif