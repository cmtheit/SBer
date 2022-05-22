#include "arcs.h"

#ifndef OPTION
#define OPTION


typedef void*(*Handle)(char*) ;

typedef struct option{
    const char * interfaces[4];
    char type;
    char mask;
    Handle handle;
}option;

void reportnooption(char * o);

void initoption(option * target, char * opts[], char type, char mask, Handle handle);
void initoptions();
const option * optget(char * opt);

#endif 