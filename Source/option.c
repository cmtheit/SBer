
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".\cJSON\cJSON.h"
#include "wheel.h"
#include "arcs.h"
#include "option.h"
#include "handle.h"

FILE * input;
FILE * output;
char * inputpath;
char * outputpath;
char * timeformat = NULL;
extern char * version;
extern char * helpinfo;


const int uni_optnum = 4;
const int pair_optnum = 2;
const int both_ok_optnum = 1;
const option emptyopt = {{NULL}, 0x00, 0x00, NULL};
option I;
option O;
option V;
option H;
option TF;
option CONFIG;
option DEFAULT;
option * uni_options[] = {&V, &H, &CONFIG, &DEFAULT};
option * pair_options[] = {&O, &TF};
option * both_ok_options[] = {&I};


extern char options;

void * handle_V(char * p){
    printf("SBer version: %s\nWhat's your deeply thought today?\n", version);
    return NULL;
}

void * handle_I(char * p){
    if(p == NULL){
        inputpath = GetInput();
        input = fopen(inputpath, "r");
        if(input == NULL){
            printf("Something wrong with your configure input file.");
            exit(STH_WRONG_WITH_CONFIGURE);
        }
    }else{
        inputpath = p;
        input = fopen(p, "r");
        if (!input){
            printf("File %s not found.", p);
            endhandle();
            exit(FILE_NOT_FOUND);

        }
        if(options & CONFIG.mask){
            SetInput(p);
        }
    }
    return NULL;
}

void * handle_O(char * p){
    outputpath = p;
    output = fopen(outputpath, "r");
    if (output == NULL){
        printf("\nTarget file cannot found, do you want to create it?[Y/n]\n");
        char c;
        scanf("%c", &c);
        if (c == 'Y' || c == 'y'){
            output = fopen(p, "w");
        }else{
            outputpath = GetOutput();
            printf("\nOutput file has been set to saved %s\n", outputpath);
            output = fopen(outputpath, "a");
            return NULL;
        }
    }else{
        fclose(output);
        output = fopen(p, "a");
    }
    if(options & CONFIG.mask){
        SetOutput(p);
    }
    return NULL;
}

void * handle_CONFIG(char * p){
// do nothing
  return NULL;
}

void * handle_H(char * p){
    printf("%s", helpinfo);
    return NULL;
}

void * handle_TF(char * p){
    timeformat = p;
    if (options & CONFIG.mask){
        SetTimeFormat(p);
    }
    return NULL;
}

void * handle_DEFAULT(char * p){
    inputpath = GetDefaultInput();
    outputpath = GetDefaultOutput();
    input = fopen(inputpath, "r");
    output = fopen(outputpath, "a");
    if (!input){
        printf("Default input file %s not found.", inputpath);
        exit(FILE_NOT_FOUND);
    }
    return NULL;
}

void reportnooption(char * o){
    printf("No options named \"%s\"\n", o);
}

void initoption(option * target, char * opts[], char type, char mask, Handle handle){
    for (int i = 0; i < 4; ++i) {
        target->interfaces[i] = opts[i];
    }
    target->type = type;
    target->mask = mask;
    target->handle = handle;
}

void initoptions(){
    char * vc[] = {"-v", "-ver", "-version", NULL};
    char * cc[] = {"-config", NULL, NULL, NULL};
    char * hc[] = {"-h", "-help", NULL, NULL};
    char * oc[] = {"-o", "-out", "-output", NULL};
    char * tfc[] = {"-tf", "-tformat", "-timeformat", NULL};
    char * ic[] = {"-i", "-in", "-input", NULL};
    char * dc[] = {"--default", NULL, NULL, NULL};
    initoption(&V, vc, UNI, _v, &handle_V);
    initoption(&CONFIG, cc, UNI, _config, &handle_CONFIG);
    initoption(&H, hc, UNI, _h, &handle_H);
    initoption(&O, oc, PAIR, _o, &handle_O);
    initoption(&TF, tfc, PAIR, _tf, &handle_TF);
    initoption(&I, ic, BOTH_OK, _i, &handle_I);
    initoption(&DEFAULT, dc, UNI, _default, &handle_DEFAULT);
}
// find if the p string is an option
const option * optget(char * p){
    for (int i = 0; i < uni_optnum; ++i){
        for(int j = 0; uni_options[i]->interfaces[j]; ++j){
            if(!strcmp(uni_options[i]->interfaces[j], p)){
                return uni_options[i];
            }
        }
    }
    for (int i = 0; i < both_ok_optnum; ++i){
        for(int j = 0; both_ok_options[i]->interfaces[j]; ++j){
            if(!strcmp(both_ok_options[i]->interfaces[j], p)){
                return both_ok_options[i];
            }
        }
    }
    for (int i = 0; i < pair_optnum; ++i){
        for(int j = 0; pair_options[i]->interfaces[j]; ++j){
            if(!strcmp(pair_options[i]->interfaces[j], p)){
                return pair_options[i];
            }
        }
    }
    return &emptyopt;
}
