/**
* @file lexical.c
* @brief Purpose: provide the lexical analysis for the code
* @version 0.3
* @date 04.27.2017
* @author Katie MacArthur
*/

#include <stdio.h>
#include "stdlib.h"
#include <memory.h>
#include <ctype.h>
#include "/Users/katiemacarthur/Documents/SER502-Spring2017-Team10/src/compiler/utils/error.h"
#include <errno.h>
#include "/Users/katiemacarthur/Documents/SER502-Spring2017-Team10/src/compiler/lexical.h"
#include "/Users/katiemacarthur/Documents/SER502-Spring2017-Team10/src/compiler/utils/symbol_table.h"
#include "/Users/katiemacarthur/Documents/SER502-Spring2017-Team10/src/compiler/utils/link_list.h"


/**
* @brief takes in symbol table and returns a linked list structure
* @param symbol_table
* @return link_list_st
*/
link_list_st *lexical_analysis(symbol_table_st *symbol_table) {

    if (symbol_table == NULL) {
        return NULL;
    }

    char char_in = getc(stdin);

    link_list_st* link_list = link_list_init();

    while (strcmp(char_in, EOF) != 0) {
        char *token_buff = (char *)malloc(sizeof(char)*256);
        int token_length = 0;

        while (strcmp(char_in, " ") != 0 | strcmp(char_in, ";") != 0 | strcmp(char_in, "\n") != 0 |
               strcmp(char_in, "\t") != 0 | strcmp(char_in, "(") != 0 | strcmp(char_in, ")") != 0 |
               strcmp(char_in, "{") != 0 | strcmp(char_in, "}") != 0) {

            token_buff[token_length] = char_in;
            token_length++;
            char_in = getc(stdin);
        }

        token_buff[token_length] = '\0';

        if (strcmp(char_in, ";") == 0 | strcmp(char_in, "(") == 0 | strcmp(char_in, ")") == 0 |
            strcmp(char_in, "{") == 0 | strcmp(char_in, "}") == 0) {
            link_list_st* new_node = link_node_new(strdup(char_in),free);
            link_list_append(link_list,new_node);
        } else {
            link_list_st* new_node = link_node_new(strdup(token_buff),free);
            link_list_append(link_list,new_node);

            int search = symbol_table_lookup(symbol_table, strdup(token_buff));
            if (search == -1) {
                if (isalpha(token_buff)) {
                    symbol_table_insert(symbol_table, strdup(token_buff), IDENTIFIER);
                } else {
                    symbol_table_insert(symbol_table, strdup(token_buff), NUMBER);
                }
            }
        }
        free(token_buff);
    }

}
/**
#ifdef XTEST

void test_case_one() {

    lexical_analysis(NULL);
}

 void test_case_two() {

 lexical_analysis(symbol_table_init());
 }
**/

int main() {

    //test_case_one();
    //test_case_two();
    return 0;
}
//#endif
