#ifndef FFFTHEADER_H_
#define FFFTHEADER_H_


#endif // FFFTHEADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <math.h>
#include <errno.h>

#define PI 3.141592654

typedef struct Dependencies{
    pid_t pid;
    int read;
    int write;
} dependencies;

typedef struct ComplexNumber{
    double real;
    double imaginary;
}compNum;

void usage(char* msg);

void argumentParsing(int argc, char *argv[argc]);


