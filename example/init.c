/**
 * @file init.c
 * @brief initialize the compiler
 * @author Xiangyu Guo
 */
#include "global.h"

extern void insert();

struct entry keywords[] = {
    {"mod", MOD},
    {"div", DIV},
    {0, 0}
};

/**
 * @brief initialize the symbol table
 */
void init ()
{
    struct entry *p;
    for (p = keywords; p->token; p++)
        insert(p->lexptr, p->token);
}