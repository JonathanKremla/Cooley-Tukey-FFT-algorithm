/**
 * @file funcDef.c
 * @author Jonathan Kremla
 * @date last edit 11.12.2021
 * @brief defining usage() and argumentParsing()
 */


#include "forkFFT.h"

/**
 * @brief defines the usage function, Usage and writes the Usage message (msg) to stderr
 * exits with EXIT_fAILURE.
 * 
 * @param msg Error message
 */
void usage(char* msg){
    fprintf(stderr, "Usage: %s",msg);
    exit(EXIT_FAILURE);
}

/**
 * @brief checks the Arguments given by argv of length argc.
 * @param argc  argument count
 * @param argv argument vector
 */
void argumentParsing(int argc, char *argv[argc]){
    if(argc != 1){
        usage("Synopsis: ./forkFFT ");
    }
}

