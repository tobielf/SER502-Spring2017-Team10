/**
 * @file lexical.c
 * @brief Purpose: provide the lexical analysis for the code
 * @version 0.2
 * @date 04.20.2017
 * @author Katie MacArthur
 */

#include <stdio.h>
#include <"lexical.h">
#include <"symboltable.h">


/**
* @brief takes in symbol table and returns a linked list structure
* @param symbol_table
* @return link_list_st
*/

link_list_st *lexical_analysis(symbol_table_st *symbol_table) {

    if (symbol_table == NULL) {
        return NULL;
    }
}

#ifdef XTEST

void test_case_one() {

    lexical_analysis(NULL);
}

int main() {

    test_case_one();

    return 0;
}
#endif
