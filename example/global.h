/**
 * @file global.h
 * @brief macro definition used across the files
 * @author Xiangyu Guo
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BSIZE   (128)   /**< buffer size */
#define NONE    (-1)    /**< invalid value */
#define EOS     ('\0')  /**< end of string */

#define NUM     (256)   /**< value of Number */
#define DIV     (257)   /**< value of Divisor */
#define MOD     (258)   /**< value of Moduler */
#define ID      (259)   /**< value of Identifier */
#define DONE    (260)   /**< value of Done */

int tokenval;       /**< value of token attribute */
int lineno;         /**< value of lineno */

struct entry {
    char *lexptr;
    int token;
};
