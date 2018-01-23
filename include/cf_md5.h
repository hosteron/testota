#ifndef _CF_MD5_H_
#define _CF_MD5_H_

struct CFMd5_struct {
	unsigned long int total[2];
	unsigned long int state[8];
	unsigned char buffer[256];
	unsigned char blen;
};


struct ikmd5_struct;
typedef struct CFMd5_struct CFMd5;

CFMd5 *CFMd5New(void);
void CFMd5Reset(CFMd5 *md5);
void CFMd5Hash(CFMd5 *md5, const unsigned char *data, size_t slen, int finish);
void CFMd5Destory(CFMd5 *md5);
void CFMd5Print(CFMd5 *md5, char *buf);
void CFMd5PrintDigest(CFMd5 *md5, unsigned char *digest);
void cf_md5(const char *data, char *buf);

#endif
