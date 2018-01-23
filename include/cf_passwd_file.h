/* COPYRIGHT_CHUNFENG */
#ifndef _CF_PASSWD_FILE_H_
#define _CF_PASSWD_FILE_H_

#include "cf_string.h"
#include "cf_list_file.h"

typedef struct cf_passwd
{
	CFString* name;
	CFString* password;
    int uid;
    int gid;
    CFString* userInfo;
    CFString* home;
    CFString* shell;
	CFListHead list;
} CFPasswd;


CFListHead* parse_passwd_new(char* start, char* end);
void cf_passwd_free(CFPasswd* passwd);
int cf_passwd_write(CFPasswd* passwd, int fd);
CFPasswd* cf_passwd_get_next(CFPasswd* passwd);

typedef struct cf_passwd_file{
	CFString* fileUri;
	CFPasswd head;
}CFPasswdFile;

CFPasswdFile* cf_passwd_file_new(const char* fileUri);
void cf_passwd_file_free(CFPasswdFile* file);
int cf_passwd_file_write(CFPasswdFile* file, int fd);
int cf_passwd_file_print(CFPasswdFile* file);
int cf_passwd_file_save(CFPasswdFile* file, const char* fileUri);
CFPasswd* cf_passwd_list_get_by_name(CFPasswd* head, const char* name);
#define CFPasswdFileForeach(__file, __passwd) CFListContainerForeach(&(__file)->head, __passwd, CFPasswd, list)

#endif
