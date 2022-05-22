

#ifndef HANDEL
#define HANDEL


// check if the option have been added

void check(char opt, char * p);
int ifcheck(char opt);
void checkalert(char m, char * p);

void writeto();
void prehandle(int argc, char ** argv);
void handling();
void endhandle();

void handle(int argc, char ** argv);


#endif