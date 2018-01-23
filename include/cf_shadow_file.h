/* COPYRIGHT_CHUNFENG */
#ifndef CF_SHADOW_FILE_H
#define CF_SHADOW_FILE_H

#include "cf_string.h"
#include "cf_list_file.h"

typedef struct
{
	CFString* name;
	CFString* e_password;
	int p_last_change;  /* nagetive value means blank*/
	int p_min_age;
	int p_max_age;
	int p_warn_period;
	int p_inactive_period;
	int a_expire_date;
	int reserved;
	CFListHead list;
} CFShadow;


CFListHead* parse_shadow_new(char* start, char* end);
void cf_shadow_free(CFShadow* shadow);
int cf_shadow_write(CFShadow* shadow, int fd);
CFShadow* cf_shadow_get_next(CFShadow* shadow);

typedef struct cf_shadow_file{
	CFString* fileUri;
	CFShadow head;
}CFShadowFile;
CFShadowFile* cf_shadow_file_new(const char* fileUri);
void cf_shadow_file_free(CFShadowFile* file);
int cf_shadow_file_write(CFShadowFile* file, int fd);
int cf_shadow_file_print(CFShadowFile* file);
int cf_shadow_file_save(CFShadowFile* file, const char* fileUri);
int cf_shadow_file_set_password_by_name(CFShadowFile* file, const char* name, const char* password);
#endif

