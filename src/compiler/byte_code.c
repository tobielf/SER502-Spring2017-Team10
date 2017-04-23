/**
 * @file byte_code.c
 * @brief Purpose: byte code operation
 * @version 0.3
 * @date 04.18.2017
 * @author Rundong Zhu
 */
#include <stdio.h>

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
    parsing_tree_st *child = parsing_tree_get_child(parsing_tree_node);

    char *data = parsing_tree_get_data(parsing_tree_node);

    if (data == "stmt_list")
        stmt_list(child);

}

/**
 * @brief handle stmt_list form parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 */
void *handle_stmt_list(parsing_tree_st *parsing_tree_node, symbol_table_st *symbol_table) {
    parsing_tree_st *child = parsing_tree_get_child(parsing_tree_get_child);

    char *data = parsing_tree_get_data(parsing_tree_node);

    if (data == "stmt_list")
        handle_stmt_list(child);

    if (data == "stmt")
        handle_stmt(child);
}

/**
 * @brief handle stmt form parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 */
void *handle_stmt(parsing_tree_st *parsing_tree_node, symbol_table_st *symbol_table) {
    parsing_tree_st *child = parsing_tree_get_child(parsing_tree_get_child);

    char *data = parsing_tree_get_data(parsing_tree_node);

    if (data == "decl_stmt")
        handle_decl_stmt_list(child);

    if (data == "assign_stmt")
        handle_assign_stmt(child);

    if (data == "if_stmt")
        handle_if_stmt(child);

    if (data == "for_stmt")
        handle_for_stmt(child);

    if (data == "print_stmt")
        handle_print_stmt(child);
}

/**
 * @brief generate decl_stmt byte code form link list and parsing tree.
 * @param byte_code, a valid link list.
 * @param node, a valid tree node
 * @return NULL on failed, otherwise a char array.
 */
char *handle_decl_stmt(link_list_st *byte_code, parsing_tree_st *parsing_tree_node) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    parsing_tree_st *id_node = parsing_tree_get_child(parsing_tree_node);
    char *operand = parsing_tree_get_data(id_node);

    bytecode_len = strlen("DEC ") + strlen(operand);
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "DEC %s", operand);

    new_node = link_node_new(bytecode, free_cb);
    link_list_append(bytecode, new_node)

    return operand;
}

/**
 * @brief generate assign_stmt byte code form link list and parsing tree.
 * @param byte_code, a valid link list.
 * @param node, a valid tree node.
 * @return NULL on failed, otherwise a char array.
 */
char *handle_assign_stmt(link_list_st *byte_code, parsing_tree_node_st *parsing_tree_node) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    parsing_tree_st *id_node = parsing_tree_get_child(parsing_tree_node);
    parsing_tree_st *expr_node = parsing_tree_get_child(parsing_tree_node);
    char *left_operand = parsing_tree_get_data(id_node);
    char *right_operand = handle_expr(expr_node);

    bytecode_len = strlen("MOV ") + strlen(left_operand) + strlen(" ") + strlen(right_operand);
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "MOV %s %s", left_operand, right_operand);

    new_node = link_node_new(bytecode, free);
    link_list_append(byte_code, new_node);

    return left_operand;
}

void *handle_if_stmt(parsing_tree_st *parsing_tree_node, symbol_table_st *symbol_table) {
    //TODO
}

void *handle_for_stmt(parsing_tree_st *parsing_tree_node, symbol_table_st *symbol_table) {
    //TODO
}

/**
 * @brief generate print_stmt byte code form link list and parsing tree.
 * @param node, a valid link list.
 * @param table, a valid tree node.
 * @return NULL on failed, otherwise a valid char array.
 */
char *handle_print_stmt(link_list_st *byte_code, parsing_tree_st *parsing_tree_node) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    parsing_tree_st *print_node = parsing_tree_get_child(parsing_tree_node);
    char *operand = parsing_tree_get_data(print_node);

    if (operand == "expr")
        handle_expr(operand);

    bytecode_len = strlen("OUT ") + strlen(operand);
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "OUT %s", operand);

    return operand;
}

/**
 * @brief handle expr form parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 */
void *handle_expr(parsing_tree_node_st *parsing_tree_node, symbol_table_st *symbol_table) {
    parsing_tree_st *child = parsing_tree_get_child(parsing_tree_node);

    char *data = parsing_tree_get_data(parsing_tree_node);

    if (data == "term")
        handle_term(child);

    if (data == "res1")
        handle_res1(child);
}

/**
 * @brief handle term form parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 */
void *handle_term(parsing_tree_node_st *parsing_tree_node, symbol_table_st *symbol_table) {
    parsing_tree_st *child = parsing_tree_get_child(parsing_tree_node);

    char *data = parsing_tree_get_data(parsing_tree_node);

    if (data == "factor")
        handle_factor(child);

    if (data == "res2")
        handle_res2(child);
}

/**
 * @brief generate res1 byte code form link list and parsing tree.
 * @param byte_code, a valid link list.
 * @param node, a valid tree node.
 * @return NULL on failed, otherwise a char array.
 */
char *handle_res1(link_list_st *byte_code, parsing_tree_node_st *parsing_tree_node) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    parsing_tree_st *operator_node = parsing_tree_get_child(parsing_tree_node);
    parsing_tree_st *term_node = parsing_tree_get_child(parsing_tree_node);
    char *left_operand = parsing_tree_get_data(operator_node);
    char *right_operand = handle_term(term_node);

    bytecode_len = strlen("ADD ") + strlen(left_operand) + strlen(" ") + strlen(right_operand);
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "ADD %s %s", left_operand, right_operand);

	
    //if (left_operand == "-") {
    //    bytecode_len = strlen("SUB ") + strlen(left_operand) + strlen(" ") + strlen(right_operand);
    //    bytecode = (char *)malloc(bytecode_len);
    //    snprintf(bytecode, bytecode_len, "SUB %s %s", left_operand, right_operand);
    //}

    new_node = link_node_new(bytecode, free);
    link_list_append(byte_code, new_node);

    return left_operand;
}

/**
 * @brief generate res1 byte code form link list and parsing tree.
 * @param byte_code, a valid link list.
 * @param node, a valid tree node.
 * @return NULL on failed, otherwise a char array.
 */
char *handle_factor(link_list_st *byte_code, parsing_tree_node_st *parsing_tree_node) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    parsing_tree_st *node = parsing_tree_get_child(parsing_tree_node);

    char *operand = parsing_tree_get_data(node);

    if (operand == "expr")
        handle_expr(operand);

    bytecode_len = strlen(operand);
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "%s", operand);

    return operand;
}

/**
* @brief generate res2 byte code form link list and parsing tree.
* @param byte_code, a valid link list.
* @param node, a valid tree node.
* @return NULL on failed, otherwise a valid link list.
*/

char *handle_res2(link_list_st *byte_code, parsing_tree_node_st *parsing_tree_node{
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    parsing_tree_st *operator_node = parsing_tree_get_child(parsing_tree_node);
    parsing_tree_st *factor_node = parsing_tree_get_child(parsing_tree_node);
    char *left_operand = parsing_tree_get_data(operator_node);
    char *right_operand = handle_factor(factor_node);

    if (left_operand == "*") {
        //bytecode_len = strlen("ADD ") + strlen(left_operand) + strlen(" ") + strlen(right_operand);
        //bytecode = (char *)malloc(bytecode_len);
        //snprintf(bytecode, bytecode_len, "ADD %s %s", left_operand, right_operand);
    }

    if (left_operand == "/") {
        //bytecode_len = strlen("SUB ") + strlen(left_operand) + strlen(" ") + strlen(right_operand);
        //bytecode = (char *)malloc(bytecode_len);
        //snprintf(bytecode, bytecode_len, "SUB %s %s", left_operand, right_operand);
    }

    if (left_operand == "%") {
        //bytecode_len = strlen("SUB ") + strlen(left_operand) + strlen(" ") + strlen(right_operand);
        //bytecode = (char *)malloc(bytecode_len);
        //snprintf(bytecode, bytecode_len, "SUB %s %s", left_operand, right_operand);
    }

    new_node = link_node_new(bytecode, free);
    link_list_append(byte_code, new_node);

    return left_operand;
}


#ifdef XTEST
void test_case_one() {
    printf("Case One");
}

int main() {
    test_case_one();
}

#endif // XTEST
