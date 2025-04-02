#include "vendor/cJSON.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define get_obj cJSON_GetObjectItemCaseSensitive

int GetInt(cJSON* json, const char* const string)
{
    assert(json);
    cJSON* jInt = cJSON_GetObjectItemCaseSensitive(json, string);
    assert(jInt);
    assert(cJSON_IsNumber(jInt));
    return jInt->valueint;
}

cJSON* GetObject(cJSON* json, const char* const string)
{
    assert(json);
    cJSON* jObject = cJSON_GetObjectItemCaseSensitive(json, string);
    assert(jObject);
    assert(cJSON_IsObject(jObject));
    return jObject;
}

cJSON* GetArray(cJSON* json, const char* const string)
{
    assert(json);
    cJSON* jArray = cJSON_GetObjectItemCaseSensitive(json, string);
    assert(jArray);
    assert(cJSON_IsArray(jArray));
    return jArray;
}

const char* GetString(cJSON* json, const char* const string)
{
    assert(json);
    cJSON* jString = cJSON_GetObjectItemCaseSensitive(json, string);
    assert(jString);
    assert(cJSON_IsString(jString));
    return jString->valuestring;
}

char* file_to_buffer(const char* file_name)
{
    FILE* file = fopen(file_name, "r");
    assert(file);

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);


    char* buffer = malloc(size + 1);


    fread(buffer, 1, size, file);
    fclose(file);
    return buffer;
}

cJSON* open_json(const char* file_name)
{
    char* buffer = file_to_buffer(file_name);

    cJSON* json = cJSON_Parse(buffer);

    if (!json) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr)
            fprintf(stderr, "Error at %s", error_ptr);
    }

    free(buffer);
    return json;
}

