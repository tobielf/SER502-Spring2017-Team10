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
 * @brief output the usage information about the compiler
 */
static void s_usage();

/**
 * @brief main entrance of the compiler.
 * @return 0 on success; otherwise errno.
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        s_usage();
        return 0;
    }

    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    symbol_table_st *symbol_table = symbol_table_init();
    if (symbol_table == NULL)
        return ENOMEM;

    link_list_st *token_list = lexical_analysis(symbol_table);
    if (token_list == NULL)
        return ENOMEM;

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

static void s_usage() {
    printf("Usage:\n");
    printf("./compiler <input file> <output file>\n");
    printf("e.g ./compiler program1.ten program1.asm\n");
}
