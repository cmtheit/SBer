#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include ".\cJSON\cJSON.h"
#include "wheel.h"
#include "handle.h"
#include "arcs.h"


void initjson(){
    FILE * config = fopen("D:\\SBer\\Source\\config.json", "r");
    if(config == NULL){
        printf("config.json cannot find. Please place the whole package SBer under \"D:\", or it cannot find the json file.");
        char buffer[100] = {0};
        getcwd(buffer, 100);
        printf("%s", buffer);
        exit(-1);
    }
    fseek(config, 0, SEEK_END);
    int tail = ftell(config);
    fseek(config, 0, SEEK_SET);
    char * jsonstring = (char*)malloc(tail + 1);
    if(!jsonstring){
        printf("Heap overflow.Please check if your mechine is ok.");
        exit(-1);
    }
    jsonstring[tail] = '\0';
    for (int i = 0; i < tail; ++i){
        jsonstring[i] = fgetc(config);
    }
    json = cJSON_Parse(jsonstring);
    free(jsonstring);
    fclose(config);
}

static char * Get(const char * key){
    cJSON * keyjson = cJSON_GetObjectItemCaseSensitive(json, key);
    char * value = cJSON_GetStringValue(keyjson);
    return value;
}

static char * GetDefault(const char * key){
    cJSON * df = cJSON_GetObjectItemCaseSensitive(json, "default");
    cJSON * dfkey = cJSON_GetObjectItemCaseSensitive(df, key);
    char * dfvalue = cJSON_GetStringValue(dfkey);
    return dfvalue;
}

static void Set(char * key, char * value){
    cJSON * keyjson = cJSON_GetObjectItemCaseSensitive(json, key);
    cJSON_SetValuestring(keyjson, value);
}

char * GetInput(){
    return Get("input");
}

char * GetDefaultInput(){
    return GetDefault("input");
}

char * GetOutput(){
    return Get("output");
}

char * GetDefaultOutput(){
    return GetDefault("output");
}

char * GetTimeFormat(){
    return Get("timeformat");
}

char * GetDefaultTimeFormat(){
    return GetDefault("timeformat");
}

void SetInput(char * value){
   Set("input", value); 
}

void SetOutput(char * value){
    Set("output", value);
}

void SetTimeFormat(char * value){
    Set("timeformat", value);
}

extern char options;
void deletejson(){
    if (options & _config && options & (_i | _o)) {
        FILE * config = fopen("D:\\SBer\\Source\\config.json", "w");
        char *thejson = cJSON_Print(json);
        fprintf(config, "%s", thejson);
        fclose(config);
    }
    cJSON_Delete(json);
}
