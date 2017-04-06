/**
 * @file parser.c
 * @brief a simple parser on arithmatic expression
 * @author Xiangyu Guo
 */
#include "global.h"

int lookahead;          /**< check more input to consume? */

extern void error(char *);
extern int lexan();
extern void emit(int t, int tval);

void expr();
void term();
void factor();
void match();

/**
 * @brief entry to the parser.
 */
void parse() {
    lookahead = lexan();
    while (lookahead != DONE) {
        expr();
        match(';');
    }
}

/**
 * @brief parsing non-terminals based on first rule: expr.
 */
void expr() {
    int t;
    term();
    while(1) {
        switch (lookahead) {
            case '+':
            case '-':
                t = lookahead;
                match(lookahead);
                term();
                emit(t, NONE);
                continue;
            default:
                return;
        }
    }
}

/**
 * @brief parsing non-terminals based on second rule: term.
 */
void term()
{
    int t;
    factor();
    while(1) {
        switch (lookahead) {
            case '*':
            case '/':
            case DIV:
            case MOD:
                t = lookahead;
                match(lookahead);
                factor();
                emit(t, NONE);
                continue;
            default:
                return;
        }
    }
}

/**
 * @brief parsing on terminals.
 */
void factor()
{
    switch (lookahead) {
        case '(':
            match('(');
            expr();
            match(')');
            break;
        case NUM:
            emit(NUM, tokenval);
            match(NUM);
            break;
        case ID:
            emit(ID, tokenval);
            match(ID);
            break;
        default:
            error("syntax error");
    }
}

/**
 * @brief match the input string with grammar and consume the input string.
 * @param t token to be consume.
 * @return return successfully consumed, exit syntax error.
 */
void match(int t)
{
    if (lookahead == t)
        lookahead = lexan();
    else
        error("syntax error");
}
