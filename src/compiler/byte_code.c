/**
 * @file byte_code.c
 * @brief Purpose: byte code operation
 * @date 04.18.2017
 * @author Rundong Zhu
 */


#include "utils/link_list.h"
#include "utils/symbol_table.h"
#include "utils/parsing_tree.h"

#include "utils/error.h"

#include "byte_code.h"

/**
 * @brief generate byte code form parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 * @return NULL on failed, otherwise a valid link list.
 */
link_list_st *semantic_analysis(parsing_tree_st *parsing_tree_node, symbol_table_st *symbol_table) {
    return NULL;
}

#ifdef XTEST
void test_case_one() {
    printf("Case One");
}

int main() {
    test_case_one();
}

#endif // XTEST
