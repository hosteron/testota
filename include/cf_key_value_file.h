/* COPYRIGHT_CHUNFENG */
#ifndef CF_KEY_VALUE_FILE_H
#define CF_KEY_VALUE_FILE_H

#include "cf_list_file.h"
#include "cf_string.h"

typedef struct cf_key_value_pair
{
	int is_comment;
	CFString *commont;
	CFString *key;
	CFString *value;
	CFListHead list;
} CFKeyValuePair;
CFKeyValuePair* cf_key_value_pair_new(int is_commont, const char* key, const char* value);
void cf_key_value_pair_free(CFListHead* node);
#define cf_key_value_pair_set_type(pair, _is_comment) ((pair)->is_comment=_is_comment)
#define cf_key_value_pair_is_comment(pair) ((pair)->is_comment)
#define cf_key_value_pair_set_key(pair, _key) cf_string_safe_cp((pair)->key, _key)
#define cf_key_value_pair_set_value(pair, _value) cf_string_safe_cp((pair)->value, _value)
#define cf_key_value_pair_get_key(pair) ((pair)->key->str)
#define cf_key_value_pair_get_value(pair)	((pair)->value->str)
int cf_key_value_pair_write(CFListHead* node, int fd, char eq);
#define cf_key_value_pair_print(pair) cf_key_value_pair_write((pair), 1)
CFKeyValuePair* parse_key_value_pair_line_new(char* start, char* end);

typedef struct cf_key_value_file{
    CFString* fileUri;
    CFKeyValuePair pairHead;
    char eq;
}CFKeyValueFile;

CFKeyValueFile* cf_key_value_file_new(const char* fileUri, char eq);
void cf_key_value_file_free(CFKeyValueFile* file);
int cf_key_value_file_write(CFKeyValueFile* file, int fd);
int cf_key_value_file_print(CFKeyValueFile* file);
int cf_key_value_file_save(CFKeyValueFile* file, const char* fileUri);
const char* cf_key_value_file_get(CFKeyValueFile* file, const char* key);
void cf_key_value_file_set(CFKeyValueFile* file, const char* key, const char* value);
void cf_key_value_file_set_by_pair(CFKeyValueFile* file, CFKeyValuePair* pair);

#endif
