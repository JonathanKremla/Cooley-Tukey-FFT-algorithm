#include "ffftHeader.h"


void usage(char* msg){
    fprintf(stderr, "Usage: %s",msg);
    exit(EXIT_FAILURE);
}

//Synopsis: ./ffft floatingPointNumb ...
void argumentParsing(int argc, char *argv[argc]){
    if(argc != 1){
        usage("wrong Input");
    }
}

