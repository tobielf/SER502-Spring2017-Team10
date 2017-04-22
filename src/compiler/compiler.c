/**
 * @file compiler.c
 * @brief Purpose: main entrance of the compiler
 * @version 0.1
 * @date 04.16.2017
 * @author Xiangyu Guo
 */
#include <stdio.h>
#include <errno.h>

#include "utils/link_list.h"
#include "utils/symbol_table.h"
#include "utils/parsing_tree.h"


#include "utils/error.h"

#include "lexical.h"
#include "parser.h"
#include "byte_code.h"

/**
 * @brief print out the data in the link list node.
 * @param node a valid link node.
 * @return LINK_LIST_CONTINUE, next node;
 *         LINK_LIST_STOP, stop here.
 */
int print_byte_code(link_node_st *node)
{
    char *str = link_node_get_data(node);
    if (str != NULL) {
        printf("%s\n", str);
        return LINK_LIST_CONTINUE;
    }
    return LINK_LIST_STOP;
}

/**
 * @brief main entrance of the compiler.
 * @return 0 on success; otherwise errno.
 */
int main()
{
    symbol_table_st *symbol_table = symbol_table_init();
    if (symbol_table == NULL)
        return ENOMEM;

    link_list_st *token_list = lexical_analysis(symbol_table);
    if (token_list == NULL)
        return ENOMEM;

    /**
    * @brief: get the token_list and symbol_table parse it into a parsing tree 
    * @arg: pointers to token_list and symbol table
    * @return: the pointer to generated parsing tree
    */
    parsing_tree_st *parse_tree = syntax_analysis(token_list, symbol_table);
    if (parse_tree == NULL)
        return ENOMEM;

    link_list_free(token_list);

    link_list_st *byte_code = semantic_analysis(parse_tree, symbol_table);
    if (byte_code == NULL)
        return ENOMEM;

    parsing_tree_free(parse_tree);

    link_list_traverse(byte_code, print_byte_code);

    link_list_free(byte_code);

    return 0;
}
