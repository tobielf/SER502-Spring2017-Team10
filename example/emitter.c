/**
 * @file emitter.c
 * @brief emitter syntax tree
 * @author Xiangyu Guo
 */
#include "global.h"

extern struct entry symtable[]; /**< symbol table */

/**
 * @brief emit the syntax tree
 * @param t token
 * @param tval token value
 */
void emit(int t, int tval)
{
    switch (t) {
        case '+':
        case '-':
        case '*':
        case '/':
            printf("%c\n", t);
            break;
        case DIV:
            printf("DIV\n");
            break;
        case MOD:
            printf("MOD\n");
            break;
        case NUM:
            printf("%d\n", tval);
            break;
        case ID:
            printf("%s\n", symtable[tval].lexptr);
            break;
        default:
            printf("token %d, tokenval %d\n", t, tval);
    }
}