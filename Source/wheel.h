#ifndef WHEEL
#define WHEEL

cJSON * json;

void initjson();
void deletejson();

char * GetInput();
char * GetDefaultInput();
char * GetOutput();
char * GetDefaultOutput();
char * GetTimeFormat();
char * GetDefaultTimeFormat();


void SetInput(char * value);
void SetOutput(char * value);
void SetTimeFormat(char * value);

#endif