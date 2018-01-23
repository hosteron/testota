/* COPYRIGHT_CHUNFENG */
#ifndef CF_FS_TAB_FILE_H
#define CF_FS_TAB_FILE_H
#include "cf_list_file.h"

/* mount dev mountPoint -t type -o options */
typedef struct
{
	int is_comment;
	CFString*  comment;	
	
	CFString* dev;
	CFString* mountPoint;
	CFString* type;
	CFString* options;
	int dump;
	int pass;
    CFListHead list;
} CFFstabLine;

CFListHead* cf_fstab_line_parse_new(char* start, char* end);
CFFstabLine* cf_fstab_line_new(int is_comment, const char* comment, 
	const char* dev, const char* mountPoint, 
	const char* type, const char* options, 
	int dump, int pass);
void cf_fstab_line_free(CFListHead* line);
char* cf_fstab_line_get_dev(CFFstabLine* line);
char* cf_fstab_line_get_mount_point(CFFstabLine* line);
int cf_fstab_line_is_comment(CFFstabLine* line);
int cf_fstab_line_write(CFListHead* line, int fd);
CFFstabLine* cf_fstab_line_get_next(CFFstabLine* line);
void cf_fstab_line_append(CFFstabLine* line, CFFstabLine* newLine);
void cf_fstab_line_set(CFFstabLine* line, const char* dev, const char* mountPoint, const char* type, const char* options, int dump, int pass);

typedef struct cf_fstab_file{
    CFString* fileUri;
    CFFstabLine head;
}CFFstabFile;

CFFstabFile* cf_fstab_file_new(const char* fileUri);
void cf_fstab_file_free(CFFstabFile* file);
CFFstabLine* cf_fstab_file_get(CFFstabFile* file, const char* dev);
void cf_fstab_file_set(CFFstabFile* file, const char* dev, const char* mountPoint, const char* type, const char* options, int dump, int pass);
int cf_fstab_file_write(CFFstabFile* file, int fd);
int cf_fstab_file_print(CFFstabFile* file);
int cf_fstab_file_save(CFFstabFile* file, const char* fileUri);
#endif
