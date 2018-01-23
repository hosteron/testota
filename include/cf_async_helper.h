

#ifndef _CF_ASYNC_HELPER_H_
#define _CF_ASYNC_HELPER_H_
int CFAsyncOpenLocalFd(int fd);
int CFAsyncOpenLocalFile(const char* file, int flags, mode_t mode);
#endif

