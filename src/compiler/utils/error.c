/**
 * @file error.c
 * @brief dealing with compiler error
 * @version 1.0
 * @date 04.21.2017
 * @author Xiangyu Guo
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void error_msg(int lineno, char *msg) {
    fprintf(stderr, "line %d: %s\n", lineno, msg);
    exit(EINVAL);
}

void error_errno(int error_number) {
    fprintf(stderr, "%s\n", strerror(error_number));
    exit(error_number);
}