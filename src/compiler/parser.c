/**
 * @file parser.c
 * @brief Purpose: implementation of parser.h 
 	which generate a parsing tree using token list and symbol table 
 * @version 0.1
 * @date 04.18.2017
 * @author Ximing
 */



#include "utils/parsing_tree.h"
#include "utils/symbol_table.h"
#include "utils/link_list.h"


/**
* @brief: get the token_list and symbol_table parse it into a parsing tree 
* @arg: pointers to token_list and symbol table
* @return: the pointer to generated parsing tree
*/
parsing_tree_st *parse_tree = syntax_analysis(token_list_st* token_list, symbol_table_st* symbol_table) {
    if (token_list == NULL || symbol_table == NULL) {
        return NULL;
    }
}



#ifdef XTEST

void test_one_setup(void*) {
}

void test_two_setup(void*) {
}

void test_case_one() {
    printf("Begin of test case of one\n");
    test_one_setup(NULL);
    syntax_analysis(NULL, NULL);
    return 0;
}

void test_case_two() {
    printf("Begin of test case of two\n");
    test_two_setup(NULL);
    syntax_analysis(NULL, NULL);
    return 0;

}

int main()
{
    test_case_one();
    test_case_two();
}

#endif
