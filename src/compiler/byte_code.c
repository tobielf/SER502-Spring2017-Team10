/**
 * @file byte_code.c
 * @brief Purpose: byte code operation
 * @version 0.2
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
    link_list_st *child = parsing_tree_get_child(parsing_tree_node);
	link_list_st *data = parsing_tree_get_data(parsing_tree_node);
	if (data = "stmt_list)
		stmt_list(child);
}

/**
* @brief generate decl_stmt byte code form parsing tree and symbol table.
* @param node, a valid tree node.
* @param table, a valid symbol table object
* @return NULL on failed, otherwise a valid link list.
*/
char *decl_stmt(slink_list_st *byte_code, parsing_tree_node_st *root_node) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;
	
	parsing_tree_st *id_node = parsing_tree_get_child(root_node);
	char *operand = parsing_tree_get_data(id_node);
	
	bytecode_len = strlen("DEC ") + strlen(operand);
	bytecode = (char *)malloc(bytecode_len);
	snprintf(bytecode, bytecode_len, "DEC %s", operand);

	new_node = link_node_new(bytecode, free_cb);
	link_list_append(bytecode, new_node)
    return operand;
}

char *term(link_list_st *byte_code, parsing_tree_node_st *root_node) {
	//implement later
	return NULL;
}

char *res1(link_list_st *byte_code, parsing_tree_node_st *root_node) {
	//implement later
    return NULL;
}

char *res2(link_list_st *byte_code, parsing_tree_node_st *root_node) {
	//implement later
	return NULL;
}

/**
* @brief generate decl_stmt byte code form parsing tree and symbol table.
* @param node, a valid tree node.
* @param table, a valid symbol table object
* @return NULL on failed, otherwise a valid link list.
*/
char *expr_stmt(link_list_st *byte_code, parsing_tree_node_st *root_node) {
	char *bytecode = NULL;
	int bytecode_len = 0;
	link_node_st *new_node = NULL;

    parsing_tree_st *term_node = parsing_tree_get_child(root_node);
	parsing_tree_st *res1_node = parsing_tree_get_child(root_node);
	char *left_operand = term(term_node);
	char *right_operand = res1(res1_node);

	return NULL;
}

/**
 * @brief generate decl_stmt byte code form parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 * @return NULL on failed, otherwise a valid link list. 
 */
char *assign_stmt(link_list_st *byte_code, parsing_tree_node_st *root_node) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    parsing_tree_st *id_node = parsing_tree_get_child(root_node);
    parsing_tree_st *expr_node = parsing_tree_get_child(root_node);
	char *left_operand = parsing_tree_get_data(id_node);
	char *right_operand = expr_stmt(expr_node);
	
	bytecode_len = strlen("MOV ") + strlen(left_operand) + strlen(" ") + strlen(right_operand);
	bytecode = (char *)malloc(bytecode_len);
	snprintf(bytecode, bytecode_len, "MOV %s %s", left_operand, right_operand);

	new_node = link_node_new(bytecode, free);
	link_list_append(byte_code, new_node);

	return left_operand;
}

/**
* @brief generate print_stmt byte code form parsing tree and symbol table.
* @param node, a valid tree node.
* @param table, a valid symbol table object
* @return NULL on failed, otherwise a valid link list.
*/
char *print_stmt(link_list_st *byte_code, parsing_tree_node_st *root_node) {
	char *bytecode = NULL;
	int bytecode_len = 0;
	link_node_st *new_node = NULL;

	parsing_tree_st *expr_node = parsing_tree_get_child(root_node);
	char *operand = expr_stmt(expr_node);

	bytecode_len = strlen("OUT ") + strlen(operand);
	bytecode = (char *)malloc(bytecode_len);
	snprintf(bytecode, bytecode_len, "OUT %s", operand);

	return operand;
}

#ifdef XTEST
void test_case_one() {
    printf("Case One");
}

int main() {
    test_case_one();
}

#endif // XTEST
