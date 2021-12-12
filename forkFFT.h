/**
 * @file forkFFT.h
 * @author Jonathan Kremla
 * @brief header File for forkFFT.c
 * @date last edit 11-12-2021
 */


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

/**
 * @brief defining PI as an approximation.
 */
#define PI 3.141592654

/**
 * @brief defining Dependencies for Child processes, pid for the child id, read/write for
 * the pipe fd from which the child reads/writes
 */
typedef struct Dependencies{
    pid_t pid;
    int read;
    int write;
} dependencies;

/**
 * @brief defining ComplexNumber struct for represinting ComplexNumbers.
 */
typedef struct ComplexNumber{
    float real;
    float imaginary;
}compNum;

/**
 * @brief declaring usage, for definition see funcDef.c
**/
void usage(char* msg);

/**
 * @brief declaring argumentParsing, for definition see funcDef.c
**/
void argumentParsing(int argc, char *argv[argc]);


