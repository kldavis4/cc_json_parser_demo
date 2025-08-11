#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = malloc(length + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }
    
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);
    
    return content;
}

cJSON* get_json_value_by_path(cJSON* json, const char* path) {
    if (!json || !path) {
        return NULL;
    }
    
    char* path_copy = strdup(path);
    char* token = strtok(path_copy, ".");
    cJSON* current = json;
    
    while (token && current) {
        current = cJSON_GetObjectItemCaseSensitive(current, token);
        token = strtok(NULL, ".");
    }
    
    free(path_copy);
    return current;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <json_file> <path>\n", argv[0]);
        printf("Example: %s test.json user.name\n", argv[0]);
        return 1;
    }
    
    const char* filename = argv[1];
    const char* path = argv[2];
    
    char* json_string = read_file(filename);
    if (!json_string) {
        return 1;
    }
    
    cJSON* json = cJSON_Parse(json_string);
    if (!json) {
        printf("Error: Invalid JSON format\n");
        free(json_string);
        return 1;
    }
    
    cJSON* value = get_json_value_by_path(json, path);
    
    if (value) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    cJSON_Delete(json);
    free(json_string);
    return 0;
}