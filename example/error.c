/**
 * @file error.c
 * @brief dealing with compiler error
 * @author Xiangyu Guo
 */
#include "global.h"

/**
 * @brief print out the error message to stderr and exit the program
 * @param m error message
 */
void error(char *m)
{
    fprintf(stderr, "line %d: %s\n", lineno, m);
    exit(1);
}