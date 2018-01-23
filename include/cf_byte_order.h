#ifdef __GNUC__

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define _CF_BYTE_ORDER_LITTLE_ENDIAN_
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define _CF_BYTE_ORDER_BIG_ENDIAN_
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#define _CF_BYTE_ORDER_PDP_ENDIAN_
#endif

#else

#ifndef _CF_BYTE_ORDER_LITTLE_ENDIAN_
#ifndef _CF_BYTE_ORDER_BIG_ENDIAN_
#ifndef _CF_BYTE_ORDER_PDP_ENDIAN_
#error please specify BYTE ORDER in CFLAGS
#endif
#endif
#endif

#endif



#ifdef _CF_BYTE_ORDER_LITTLE_ENDIAN_
#define CF_HTOLS(_s)    (_s)
#define CF_HTOLL(_l)    (_l)
#define CF_HTOBS(_s)    ((_s)<<8|(_s)>>8)
#define CF_HTOBL(_l)    ((_s)<<24|(((_s)&0x0000FF00)<<8)|(((_s)&0x00FF0000)>>8)|(_s)>>24)
#define CF_LTOHS(_s)    (_s)
#define CF_LTOHL(_l)    (_l)
#define CF_BTOHS(_s)    CF_HTOBS(_s)
#define CF_BTOHL(_l)    CF_HTOBL(_l)
#define CF_HTONS(_s)    CF_HTOBS(_s)
#define CF_HTONL(_l)    CF_HTOBL(_l)
#define CF_NTOHS(_s)    CF_HTOBS(_s)
#define CF_NTOHL(_l)    CF_HTOBL(_l)
#elif defined _CF_BYTE_ORDER_BIG_ENDIAN_
#define CF_HTOLS(_s)    ((_s)<<8|(_s)>>8)
#define CF_HTOLL(_l)    ((_s)<<24|(((_s)&0x0000FF00)<<8)|(((_s)&0x00FF0000)>>8)|(_s)>>24)
#define CF_HTOBS(_s)    (_s)
#define CF_HTOBL(_l)    (_l)
#define CF_LTOHS(_s)    (_s)
#define CF_LTOHL(_l)    (_l)
#define CF_BTOHS(_s)    CF_HTOBS(_s)
#define CF_BTOHL(_l)    CF_HTOBL(_l)
#define CF_NTOHS(_s)    (_s)
#define CF_HTONS(_s)    (_s)
#define CF_NTOHL(_l)    (_s)
#define CF_HTONL(_l)    (_s)
#elif defined _CF_BYTE_ORDER_PDP_ENDIAN_
#error FIX ME: PDP BYTE ORDER NOT SUPPORT CURRENTLY
#endif
