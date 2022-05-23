#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cJSON\cJSON.h"
#include "wheel.h"

#include "arcs.h"
#include "handle.h"
#include "option.h"

extern const int time_format_max_len;


char * thought = NULL;

extern option * uni_options;
extern option * both_ok_options;
extern option * pair_options;
extern option I;
extern option O;
extern option V;
extern option H;
extern option CONFIG;
extern option TF;
extern option DEFAULT;

extern FILE * input;
extern FILE * output;


extern int true;
extern int false;

char options = 0x00;

void check(char opt, char * p){
    checkalert(opt, p);
    options |= opt;
}

int ifcheck(char opt){
    return options & opt ? true : false;
}

void checkalert(char m, char * p){
    if (ifcheck(m)){
        printf("The option %s has appeared in your command before.", p);
        exit(HAVE_SET_MASK);
    }
}
extern char * inputpath;
extern char * outputpath;
extern char * timeformat;
// write content to the target
void writeto() {
    time_t n = time(NULL);
    struct tm *now = localtime(&n);
    if (timeformat == NULL) {
        timeformat = GetTimeFormat();
    }
    if (options & DEFAULT.mask){
        timeformat = GetDefaultTimeFormat();
    }
    if (strlen(timeformat) > time_format_max_len) {
        printf("Time format string is too long, please use -config and -tf to specify the time format string.\n");
        exit(1);
    }
    char buffer[128] = {0};

    
    strftime(buffer, 127, timeformat, now);
    if (options & I.mask) {
        // if open a input file
        fseek(input, 0, SEEK_END);
        int inputfilelen = ftell(input);
        char *inputcontentbuffer = (char *) malloc(inputfilelen + 1);
        if (!inputcontentbuffer) {
            printf("Something wrong with your system. It just causes an heap allocation error.");
            exit(HEEP_ERROR);
        }
        inputcontentbuffer[inputfilelen] = 0;
        fseek(input, 0, SEEK_SET);
        for (int i = 0; i < inputfilelen; ++i) {
            inputcontentbuffer[i] = (char) fgetc(input);
        }
        if (thought != NULL) {
            printf("Writing\n\n\"%s%s%s\"\n\n\n to %s\n", buffer, inputcontentbuffer, thought, inputpath);
            fprintf(output, "%s%s%s\n", buffer, inputcontentbuffer, thought);
        } else {
            printf("Writing\n\n\"%s%s%s\"\n\n\n to %s\n", buffer, inputcontentbuffer, thought, outputpath);
            fprintf(output, "%s%s\n", buffer, inputcontentbuffer);
        }
        free(inputcontentbuffer);
    } else {
        if (thought) {
            printf("Writing\n\n\"%s%s\"\n\n\n to %s\n", buffer, thought, outputpath);
            fprintf(output, "%s%s\n", buffer, thought);
        } else {
            printf("Alert: you haven't input anything to the output.\n");
        }
    }
}

// main handle function
void prehandle(int argc, char ** argv) {
    initjson();
    initoptions();
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(CONFIG.interfaces[0], argv[i])) {
            options |= _config;
        }else if(!strcmp(DEFAULT.interfaces[0], argv[i])){
            options |= _default;
            options |= _i | _o;
            DEFAULT.handle(argv[i]);
        }
    }
    if (options & _default){
        if (options & _config) {
            I.handle(inputpath);
            O.handle(outputpath);
        }
        return;
    }
    for (int i = 1; i < argc; ++i) {
        const option * o = optget(argv[i]);
        // if it was a valid option
        if (o->mask && o->mask != _config) {
            if (o->type == PAIR) {
                // we need pair
                if (i == argc - 1) {
                    // but only get one
                    switch (o->mask) {
                        case _o:
                            printf("A target is expected after the %s option.\n", argv[i]);
                            exit(NEED_PARAMETER);
                        case _tf:
                            printf("A time format string is expected after the %s option.\n", argv[i]);
                            exit(NEED_PARAMETER);
                    }
                } else {
                    // if we can get next one
                    if ('-' == argv[i + 1][0]) {
                        // if the next is an option
                        printf("A parameter is expected after %s, not an option.", argv[i]);
                        exit(NEED_PARAMETER);
                    } else {
                        // if the next is not an option
                        // pay attention to -config
                        check(o->mask, argv[i]);
                        o->handle(argv[++i]);
                    }
                }
            } else if (o->type == BOTH_OK) {
                if (i < argc - 1) {
                    if ('-' != argv[i + 1][0]) {
                        // pay attention to -config
                        check(o->mask, argv[i]);
                        o->handle(argv[++i]);
                    } else {
                        check(o->mask, argv[i]);
                        o->handle(NULL);
                    }
                }else {
                    check(o->mask, argv[i]);
                    o->handle(NULL);
                }
            } else{
                check(o->mask, argv[i]);
                o->handle(argv[i]);
            }
        } else if (o->mask == _config){
            continue;
        }else {
            if (i == argc - 1) {
                thought = argv[i];
            } else {
                if ('-' == argv[i][0]) {
                    reportnooption(argv[i]);
                    exit(NO_SUCH_OPTION);
                } else {
                    printf("The thought %s are supposed to appears at the end. Or you may need a pair of \" around a sentence.",
                           argv[i]);
                    exit(THOUGHT_APPEAR_BAD);
                }
            }
        }
    }
}
void handling(){
    if (!(options & _o)){
        outputpath = GetOutput();
        output = fopen(outputpath, "a");
    }
    writeto();
}

void endhandle(){
    deletejson();
    fclose(input);
    fclose(output);
}

void handle(int argc, char ** argv){
    prehandle(argc, argv);
    handling();
    endhandle();
}
