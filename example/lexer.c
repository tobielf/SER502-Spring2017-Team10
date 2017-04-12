/**
 * @file lexer.c
 * @brief lexical analyzer
 * @author Xiangyu Guo
 */
 #include "global.h"

extern void error(char *);
extern int lookup(char s[]);
extern int insert(char s[], int tok);

extern struct entry symtable[];     /**< symbol table */
char lexbuf[BSIZE];                 /**< buffer of lexical analyzer */

int lineno = 1;                     /**< line number of source code*/
int tokenval = NONE;                /**< token value after lexical analysis */

/**
 * @brief simple lexical analyzing
 */
int lexan() {
    int t;
    while (1) {
        t = getchar();
        if (t == ' ' || t == '\t')
            continue;
        else if (t == '\n')
            lineno = lineno + 1;
        else if (isdigit(t)) {
            ungetc(t, stdin);
            scanf("%d", &tokenval);
            return NUM;
        } else if (isalpha(t)) {
            int p, b = 0;
            while (isalnum(t)) {
                lexbuf[b] = t;
                t = getchar();
                b = b + 1;
                if (b >= BSIZE)
                    error("compiler error");
            }
            lexbuf[b] = EOS;
            if (t != EOF)
                ungetc(t, stdin);
            p = lookup(lexbuf);
            if (p == 0)
                p = insert(lexbuf, ID);
            tokenval = p;
            return symtable[p].token;
        } else if (t == EOF)
            return DONE;
        else {
            tokenval = NONE;
            return t;
        }
    }
}
