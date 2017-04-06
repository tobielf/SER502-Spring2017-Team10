/**
 * @file main.c
 * @brief main entrence of the compiler
 * @author Xiangyu Guo
 */
 #include "global.h"

extern void init();
extern void parse();

int main()
{
    init();
    parse();
    return 0;
}