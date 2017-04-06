/**
 * @file symbol.c
 * @brief symbol table implementation
 * @author Xiangyu Guo
 */
 #include "global.h"

#define STRMAX  (999)               /**< Abstract Syntax Tree size */
#define SYMMAX  (100)               /**< Symbol table size */

extern void error(char *);

char lexemes[STRMAX];               /**< Syntax Tree (Array representation) */
int lastchar = -1;                  /**< Index of Syntax Tree */
struct entry symtable[SYMMAX];      /**< Symbol Table */
int lastentry = 0;                  /**< Index of Symbol Table */

/**
 * @brief lookup the symbol table
 * @param s token
 * @return p entry of the symbol table
 */
int lookup(char s[])
{
    int p;
    for (p = lastentry; p > 0; p--)
        if (strcmp(symtable[p].lexptr, s) == 0)
            return p;
    return 0;
}

/**
 * @brief insert into the symbol table
 * @param s token
 * @param tok token type (Identifier)
 * @return lastentry entry of the symbol table
 */
int insert(char s[], int tok) {
    int len;
    len = strlen(s);
    if (lastentry + 1 >= SYMMAX)
        error("symbol table full");
    if (lastchar + len + 1 >= STRMAX)
        error("lexemes array full");

    lastentry++;
    symtable[lastentry].token = tok;
    symtable[lastentry].lexptr = &lexemes[lastchar + 1];
    lastchar = lastchar + len + 1;
    strcpy(symtable[lastentry].lexptr, s);
    printf("%s %d %d\n", s, tok, lastentry);
    return lastentry;
}
