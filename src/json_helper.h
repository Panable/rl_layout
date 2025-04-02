#include "vendor/cJSON.h"
extern int GetInt(cJSON* json, const char* const string);
extern cJSON* GetObject(cJSON* json, const char* const string);
extern cJSON* GetArray(cJSON* json, const char* const string);
extern const char* GetString(cJSON* json, const char* const string);
extern char* file_to_buffer(const char* file_name);
extern cJSON* open_json(const char* file_name);
