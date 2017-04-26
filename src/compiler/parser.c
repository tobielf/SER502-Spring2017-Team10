/**
 * @file parser.c
 * @brief Purpose: implementation of parser.h 
 	which generate a parsing tree using token list and symbol table 
 * @version 0.1
 * @date 04.18.2017
 * @author Ximing
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "utils/parsing_tree.h"
#include "utils/symbol_table.h"
#include "utils/link_list.h"

static void raise_syntax_error() {
    fprintf(stderr, "Syntax error\n");
    exit(EINVAL);
}

static parsing_tree_st *generate_decl_stmt(link_list_st *, symbol_table_st *);

static parsing_tree_st *generate_print_stmt(link_list_st *, symbol_table_st *);

static parsing_tree_st *generate_assign_stmt(link_list_st *, symbol_table_st *);

static parsing_tree_st *generate_expre(link_list_st *, symbol_table_st *);

static parsing_tree_st *generate_stmt(link_list_st *, symbol_table_st *);

/**
 * @brief: generate the statement list recursively accordig to the grammar rule
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated parsing tree
 */
static parsing_tree_st *generate_stmt(link_list_st *token_list, symbol_table_st *symbol_table) {
    link_node_st *stmt_type = link_list_top(token_list);
    parsing_tree_st *stmt_root = parsing_tree_new("stmt", NULL);
    parsing_tree_st *stmt_tree = NULL;
    parsing_tree_st *stmt_child = NULL;
    char *node_data = link_node_get_data(stmt_type);

    if (strcmp(node_data, "var") == 0) {
        stmt_tree = parsing_tree_new("decl_stmt", NULL);
        stmt_child = generate_decl_stmt(token_list, symbol_table);
    } else if (strcmp(node_data, "print") == 0) {
        stmt_tree = parsing_tree_new("print_stmt", NULL);
        stmt_child = generate_print_stmt(token_list, symbol_table);
    } else if (strcmp(node_data, "if") == 0) {
        stmt_tree = parsing_tree_new("if_stmt", NULL);
        // to do: stmt_child = generate_if_stmt(token_list, symbol_table);
    } else if (strcmp(node_data, "for") == 0) {
        stmt_tree = parsing_tree_new("for_stmt", NULL);
        // to do: stmt_child = generate_for_stmt(token_list, symbol_table);
    } else if (symbol_table_lookup(symbol_table, node_data) == IDENTIFIER) {
        stmt_tree = parsing_tree_new("assign_stmt", NULL);
        stmt_child = generate_assign_stmt(token_list, symbol_table);
    } else {
        raise_syntax_error();
    }

    parsing_tree_set_child(stmt_tree, stmt_child);
    parsing_tree_set_child(stmt_root, stmt_tree);
    return stmt_root;
}

/**
 * @brief: generate the declare statement accordig to the grammar rule
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated root node of the declare statement subtree
 */
static parsing_tree_st *generate_decl_stmt(link_list_st *token_list, symbol_table_st *symbol_table) {
    link_node_st *var_node = link_list_pop(token_list);
    char *node_data = link_node_get_data(var_node);
    if (strcmp(node_data, "var") != 0)
        raise_syntax_error();

    parsing_tree_st *var_tree_node = parsing_tree_new(strdup(node_data), free);
    link_node_free(var_node);

    link_node_st *id_node = link_list_pop(token_list);
    node_data = link_node_get_data(id_node);

    if (symbol_table_lookup(symbol_table, node_data) != IDENTIFIER)
        raise_syntax_error();

    parsing_tree_st *id_tree_node = parsing_tree_new(strdup(node_data), free);
    parsing_tree_set_sibling(var_tree_node, id_tree_node);
    link_node_free(id_node);

    return var_tree_node;
}

/**
 * @brief: generate the expression accordig to the grammar rule
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated first term of the expression
 */
static parsing_tree_st *generate_expre(link_list_st *token_list, symbol_table_st *symbol_table) {

}

/**
 * @brief: generate the print statement accordig to the grammar rule
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated root node of the print statement subtree
 */
static parsing_tree_st *generate_print_stmt(link_list_st *token_list, symbol_table_st *symbol_table) {
    link_node_st *print_node = link_list_pop(token_list);
    char *node_data = link_node_get_data(print_node);
    if (strcmp(node_data, "print") != 0)
        raise_syntax_error();

    parsing_tree_st *print_tree_node = parsing_tree_new(strdup(node_data), free);
    link_node_free(print_node);

    parsing_tree_st *expr_tree_node = generate_expre(token_list, symbol_table);
    parsing_tree_set_sibling(print_tree_node, expr_tree_node);

    return print_tree_node;
}

/**
 * @brief: generate the assignment statement accordig to the grammar rule
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated root node of the assignment statement subtree
 */
static parsing_tree_st *generate_assign_stmt(link_list_st *token_list, symbol_table_st *symbol_table) {
    link_node_st *assign_node = link_list_pop(token_list);
    char *node_data = link_node_get_data(assign_node);
    if (symbol_table_lookup(symbol_table, node_data) != IDENTIFIER)
        raise_syntax_error();

    parsing_tree_st *id_tree_node = parsing_tree_new(strdup(node_data), free);
    link_node_free(assign_node);

    link_node_st *is_node = link_list_pop(token_list);
    node_data = link_node_get_data(is_node);
    if (strcmp(node_data, "is") != 0)
        raise_syntax_error();

    parsing_tree_st *is_tree_node = parsing_tree_new(strdup(node_data), free);
    link_node_free(is_node);
    parsing_tree_set_sibling(id_tree_node, is_tree_node);

    parsing_tree_st *expr_tree_node = generate_expre(token_list, symbol_table);
    parsing_tree_set_sibling(is_tree_node, expr_tree_node);

    return id_tree_node;
}

/**
 * @brief: get the token_list and symbol_table parse it into a parsing tree 
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated parsing tree
 */
parsing_tree_st *syntax_analysis(link_list_st *token_list, symbol_table_st *symbol_table) {
    if (token_list == NULL || symbol_table == NULL) {
        return NULL;
    }
    
    /* create 'program' node and 'sttm_list' node */
    /* set the 'stmt_list' node as child node of 'program' node */
    parsing_tree_st *program_tree_node = parsing_tree_new("program", NULL);
    parsing_tree_st *stmt_list_tree_node = parsing_tree_new("stmt_list", NULL);
    parsing_tree_set_child(program_tree_node, stmt_list_tree_node);
    /* manually set first statement as child of stmt_list node */
    /* recursively set the rest of statements as the right sibling of previous statement*/
    while (1) {
        parsing_tree_st *stmt = generate_stmt(token_list, symbol_table);
        parsing_tree_set_child(stmt_list_tree_node, stmt);

        link_node_st *semicolon_node = link_list_pop(token_list);
        char *node_data = link_node_get_data(semicolon_node);
        // todo lookup node_data on symbol table for "DELIMETER"
        link_node_free(semicolon_node);
        parsing_tree_st *semicolon = parsing_tree_new(";", NULL);
        parsing_tree_set_sibling(stmt, semicolon);

        if (link_list_top(token_list) == NULL)
            break;
        stmt_list_tree_node = parsing_tree_new("stmt_list", NULL);
        parsing_tree_set_sibling(semicolon, stmt_list_tree_node);
    }
    return program_tree_node;
}

#ifdef XTEST

/**
 * @brief: print the data of one node in the parsing tree
 * @param: node of parsing tree
 * @return: no return value
 */
int print_data(parsing_tree_st *parsing_tree_node){
    if (parsing_tree_node != NULL)
        printf("%s\n", parsing_tree_get_data(parsing_tree_node));
    return TREE_TRAVERSE_CONTINUE;
}

int print_list_data(link_node_st *node) {
    if (node != NULL)
        printf("%s\n", link_node_get_data(node));
    return LINK_LIST_CONTINUE;
}

void test_case_two() {
    printf("Begin of test case of two\n");
    /* set up phase*/
    /* create a mockup token list */
    link_list_st *token_list = link_list_init();
    link_node_st *var_node = link_node_new("var", NULL);
    link_node_st *id_node = link_node_new("i", NULL);
    link_node_st *semicolon = link_node_new(";", NULL);
    link_list_append(token_list, var_node);
    link_list_append(token_list, id_node);
    link_list_append(token_list, semicolon);

    var_node = link_node_new("var", NULL);
    id_node = link_node_new("j", NULL);
    semicolon = link_node_new(";", NULL);
    link_list_append(token_list, var_node);
    link_list_append(token_list, id_node);
    link_list_append(token_list, semicolon);
    /* create a mockup symbol table */
    symbol_table_st *symbol_table = symbol_table_init();
    symbol_table_insert(symbol_table, "i", IDENTIFIER);
    symbol_table_insert(symbol_table, "j", IDENTIFIER);
    link_list_traverse(token_list, print_list_data, NULL);
    /* generate the parsing tree */
    parsing_tree_st *decl_stmt = syntax_analysis(token_list, symbol_table);
    parsing_tree_prefix_traverse(decl_stmt, print_data, NULL);

    symbol_table_fini(symbol_table);
    parsing_tree_free(decl_stmt);
    link_list_free(token_list);
}


/**
 * @brief: this test case generate a tree from a declare statement and print it out
 * @param: (no parameter)
 * @return: the pointer to generated root node of the assignment statement subtree
 */
void test_case_one() {
    printf("Begin of test case of one\n");
    /* set up phase*/
    /* create a mockup token list */
    link_list_st *token_list = link_list_init();
    link_node_st *var_node = link_node_new("var", NULL);
    link_node_st *id_node = link_node_new("i", NULL);
    link_node_st *semicolon = link_node_new(";", NULL);
    link_list_append(token_list, var_node);
    link_list_append(token_list, id_node);
    link_list_append(token_list, semicolon);
    /* create a mockup symbol table */
    symbol_table_st *symbol_table = symbol_table_init();
    symbol_table_insert(symbol_table, "i", IDENTIFIER);
    link_list_traverse(token_list, print_list_data, NULL);
    /* generate the parsing tree */
    parsing_tree_st *decl_stmt = syntax_analysis(token_list, symbol_table);
    parsing_tree_prefix_traverse(decl_stmt, print_data, NULL);

    symbol_table_fini(symbol_table);
    parsing_tree_free(decl_stmt);
    link_list_free(token_list);
}

int main()
{
    test_case_one();
    test_case_two();
}

#endif
