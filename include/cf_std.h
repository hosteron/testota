/* COPYRIGHT_CHUNFENG */
#ifndef CF_STD_H
#define CF_STD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "cf_byte_order.h"
#define CF_ARRAY_SIZE(__ary)   (sizeof(__ary)/sizeof(__ary[0]))
#define CFMalloc    malloc
#define CFFree  free

void CFPrintSysInfo(int fd);
#endif

