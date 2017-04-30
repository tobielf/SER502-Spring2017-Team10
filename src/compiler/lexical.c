/**
 * @file lexical.c
 * @brief Purpose: provide the lexical analysis for the code
 * @version 1.0
 * @date 04.27.2017
 * @author Katie MacArthur
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include <errno.h>

#include "./utils/error.h" 
#include "./utils/symbol_table.h"
#include "./utils/link_list.h"
#include "./utils/link_node.h"

#include "lexical.h"

#define DEFAULT_TOKEN_BUFF_SIZE     (256)
#define ENLARGE_FACTOR              (2)

static void emit_token(link_list_st *token_list, char *token_buff) {
    link_node_st* new_node = link_node_new(strdup(token_buff),free);
    link_list_append(token_list, new_node);
}

static void emit_error() {

}
/**
* @brief takes in symbol table and returns a linked list structure
* @param symbol_table
* @return link_list_st
*/
link_list_st *lexical_analysis(symbol_table_st *symbol_table) {

    if (symbol_table == NULL) 
        return NULL;

    char *token_buff = (char *)malloc(DEFAULT_TOKEN_BUFF_SIZE);
    int token_buff_size = DEFAULT_TOKEN_BUFF_SIZE;
    int token_length = 0;
    int char_in;

    link_list_st* link_list = link_list_init();

    while ((char_in = getchar()) != EOF) {
        if (char_in == ' ' || char_in == '\t' || 
            char_in == '\r' || char_in == '\n')
            continue;

        if (char_in == '(' || char_in == ')' || 
            char_in == '{' || char_in == '}' ||
            char_in == ';') {
            // Special symbols.
            token_buff[token_length++] = char_in;
            token_buff[token_length++] = '\0';

            emit_token(link_list, token_buff);
            token_length = 0;
        } else if (isalpha(char_in)) {
            // Starting from alpha, possible: KEYWORD or IDENTIFIER.
            while (isalpha(char_in)) {
                token_buff[token_length++] = char_in;
                char_in = getchar();
                if (token_length >= token_buff_size) {
                    token_buff = realloc(token_buff,
                                        sizeof(char) * token_buff_size * ENLARGE_FACTOR);
                    if (token_buff == NULL)
                        exit(ENOMEM);
                    token_buff_size *= ENLARGE_FACTOR;
                }
            }
            if (!isalpha(char_in))
                ungetc(char_in, stdin);
            token_buff[token_length++] = '\0';
            if (symbol_table_lookup(symbol_table, token_buff) == NONE) {
                symbol_table_insert(symbol_table, token_buff, IDENTIFIER);
            }
            emit_token(link_list, token_buff);
            token_length = 0;
        } else if (char_in == '=' || char_in == '<' || char_in == '>') {
            token_buff[token_length++] = char_in;
            char_in = getchar();
            if (char_in == '=' || char_in == '<' || char_in == '>') {
                token_buff[token_length++] = char_in;
            } else {
                ungetc(char_in, stdin);
            }
            token_buff[token_length++] = '\0';
            if (symbol_table_lookup(symbol_table, token_buff) == NONE) {
                emit_error();
            }
            emit_token(link_list, token_buff);
            token_length = 0;
        } else if (char_in == '+' || char_in == '%' || 
                   char_in == '*' || char_in == '/' ) {
            token_buff[token_length++] = char_in;
            token_buff[token_length++] = '\0';
            emit_token(link_list, token_buff);
            token_length = 0;
        } else if (char_in == '-') {
            int look_ahead = getchar();
            token_buff[token_length++] = char_in;
            if (!isdigit(look_ahead)) {
                token_buff[token_length++] = '\0';
                emit_token(link_list, token_buff);
                token_length = 0;
            }
            ungetc(look_ahead, stdin);
        } else if (isdigit(char_in)) {
            while (isdigit(char_in)) {
                token_buff[token_length++] = char_in;
                char_in = getchar();
                if (token_length >= token_buff_size) {
                    token_buff = realloc(token_buff,
                                         sizeof(char) * token_buff_size * ENLARGE_FACTOR);
                    if (token_buff == NULL)
                        exit(ENOMEM);
                    token_buff_size *= ENLARGE_FACTOR;
                }
            }
            if (!isdigit(char_in))
                ungetc(char_in, stdin);
            token_buff[token_length++] = '\0';
            emit_token(link_list, token_buff);
            symbol_table_insert(symbol_table, token_buff, NUMBER);
            token_length = 0;
        }
    }
    free(token_buff);

    return link_list;
}

#ifdef XTEST

int print_list(link_node_st *node, void *cb_data) {
    printf("%s\n", (char *)link_node_get_data(node));
    return LINK_LIST_CONTINUE;
}

void test_case_one(char *file_name) {

    lexical_analysis(NULL);
}

void test_case_two(char *file_name) {
    symbol_table_st *symbol_table;
    freopen(file_name, "r", stdin);
    symbol_table = symbol_table_init();
    link_list_st *token_list = lexical_analysis(symbol_table);
    link_list_traverse(token_list, print_list, NULL);
    symbol_table_fini(symbol_table);
    link_list_free(token_list);
}


int main(int argc, char *argv[]) {
    if (argc != 2)
        return 0;

    test_case_one(argv[1]);
    test_case_two(argv[1]);
    return 0;
}
#endif
