/**
 * @file parser.c
 * @brief Purpose: implementation of parser.h 
 	which generate a parsing tree using token list and symbol table 
 * @version 0.1
 * @date 04.18.2017
 * @author Ximing
 */
#include <stdio.h>


#include "utils/parsing_tree.h"
#include "utils/symbol_table.h"
#include "utils/link_list.h"


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
    char *program_node_data = "program";
    char *stmt_list_node_data = "stmt_list";
    parsing_tree_st *program_node = parsing_tree_new(program_node_data, NULL);
    parsing_tree_st *stmt_list_node = parsing_tree_new(stmt_list_node_data, NULL);
    program_node = parsing_tree_set_child(stmt_list_node);
    /* manually set first statement as child of stmt_list node */
    /* recursively set the rest of statements as the right sibling of previous statement*/
    parsing_tree_st *first_stmt = generate_stmt(token_list, symbol_table);
    stmt_list_node = parsing_tree_set_child(first_stmt_root);
    parsing_tree_st *prev_stmt = first_stmt;
    while (token_list != NULL) {
            parsing_tree_st new_stmt = generate_stmt(token_list, symbol_table);
            prev_stmt = parsing_tree_set_sibling(new_stmt);
            prev_stmt = new_stmt;
    }
    return program_node;
}

/**
 * @brief: generate the statement list recursively accordig to the grammar rule
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated parsing tree
 */
parsing_tree_st *generate_stmt(link_list_st *token_list, symbol_table_st *symbol_table) {
    stmt_list_node *stmt_type = link_list_pop(token_list);
    switch (stmt_list_node.data) {
        case 'var':
            parsing_tree_st stmt_root = generate_decl_stmt(stmt_type);
            break;

        case 'print':
            parsing_tree_st stmt_root = generate_print_stmt(stmt_type);
            break;

        default:
            parsing_tree_st stmt_root = generate_assign_stmt(stmt_type);
            break;
    }
}

/**
 * @brief: generate the declare statement accordig to the grammar rule
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated root node of the declare statement subtree
 */
parsing_tree_st *generate_decl_stmt(link_list_st *token_list, symbol_table_st *symbol_table) {
    link_list_st *var_node = link_list_pop(token_list);
    if (var_node.data == "var") {
        parsing_tree_st *var_tree_node = parsing_tree_new(var_node.data, NULL);
        link_list_st *id_node = link_list_pop(token_list);
        if (symbol_table_lookup(symbol_table, id_node.data) == 1) {
            parsing_tree_st id_tree_node = parsing_tree_new(id_node.data, NULL);
            var_node = parsing_tree_set_sibling(id_node);
            link_list_st *semicolon = link_list_pop(token_list);
            if (semicolon.data == ";") {
                return var_tree_node;
            }
        }
    }
}

/**
 * @brief: generate the expression accordig to the grammar rule
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated first term of the expression
 */
parsing_tree_st *generate_expre(link_list_st *token_list, symbol_table_st *symbol_table){
    
}

/**
 * @brief: generate the print statement accordig to the grammar rule
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated root node of the print statement subtree
 */
parsing_tree_st *generate_print_stmt(link_list_st *token_list, symbol_table_st *symbol_table){
     link_list_st *print_node = link_list_pop(token_list);
     if (print_node.data == "print") {
        parsing_tree_st *print_tree_node = parsing_tree_new(print_node.data, NULL);
        parsing_tree_st *expre = generate_expre();
     }
}

/**
 * @brief: generate the assignment statement accordig to the grammar rule
 * @param: pointers to token list 
 * @param: pointers to symbol table
 * @return: the pointer to generated root node of the assignment statement subtree
 */
parsing_tree_st *generate_assign_stmt(link_list_st *token_list, symbol_table_st *symbol_table){

}




#ifdef XTEST

void test_one_setup(void *data) {
}

void test_two_setup(void *data) {
}

void test_case_one() {
    printf("Begin of test case of one\n");
    test_one_setup(NULL);
    syntax_analysis(NULL, NULL);
}

void test_case_two() {
    printf("Begin of test case of two\n");
    test_two_setup(NULL);
    syntax_analysis(NULL, NULL);

}

int main()
{
    test_case_one();
    test_case_two();
}

#endif
