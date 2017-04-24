/**
 * @file byte_code.c
 * @brief Purpose: byte code operation
 * @version 4.0
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

    if (strcmp(data, "stmt_list") == 0)
        stmt_list(child);  //calling process to handle stmt_list

    return NULL;
}

/**
 * @brief handle stmt_list form parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 */
void *handle_stmt_list(parsing_tree_st *parsing_tree_node, symbol_table_st *symbol_table) {
    parsing_tree_st *child = parsing_tree_get_child(parsing_tree_node);
    char *data = parsing_tree_get_data(parsing_tree_node);

    if (strcmp(data, "stmt") == 0) {
        handle_stmt(child);
    } else {
        //error();
    }

    parsing_tree_st *sibling_1 = parsing_tree_get_sibling(child);
    char *data_sibling_1 = parsing_tree_get_data(sibling_1);
    parsing_tree_st *sibling_2 = parsing_tree_get_sibling(sibling_1);
    char *data_sibling_2 = parsing_tree_get_data(sibling_2);

    if (strcmp(data_sibling, ";") == 0 && sibling_2 == NULL)
        break;

    if (strcmp(data_sibling_2, "stmt_list") != 0) {
        //error();
    }
}

/**
 * @brief handle stmt form parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 */
void *handle_stmt(parsing_tree_st *parsing_tree_node, symbol_table_st *symbol_table) {
    parsing_tree_st *child = parsing_tree_get_child(parsing_tree_node);
    char *data = parsing_tree_get_data(parsing_tree_node);

    if (strcmp(data, "decl_stmt") == 0) {
        handle_decl_stmt(child);
    }
    else if (strcmp(data, "assign_stmt") == 0) {
        handle_assign_stmt(child);
    }
    else if (strcmp(data, "if_stmt") == 0) {
        handle_if_stmt(child);
    }
    else if (strcmp(data, "for_stmt") == 0) {
        handle_for_stmt(child);
    }
    else if (strcmp(data, "print_stmt") == 0) {
        handle_print_stmt(child);
    }
    else
    {
        //error();
    }
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

    parsing_tree_st *var_node = parsing_tree_get_child(parsing_tree_node);
    parsing_tree_st *id_node = parsing_tree_get_sibling(var_node);
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
    parsing_tree_st *sibling = parsing_tree_get_sibling(id_node);
    char *sibling_data = parsing_tree_get_data(sibling);
    if (strcmp(sibling_data, "is") != 0) {
        //error();
    }
    parsing_tree_st *expr_node = parsing_tree_get_sibling(sibling);
    char *left_operand = parsing_tree_get_data(id_node);
    char *right_operand = parsing_tree_get_data(expr_node);
    if (strcmp(right_operand, "expr") == 0) {
        handle_expr(expr_node);
    }
    else {
        //error();
    }

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
    char *print_data = parsing_tree_get_data(print_node);

    if (strcmp(print_data, "print") != 0) {
        //error();
    }

    parsing_tree_st *operand_node = parsing_tree_get_sibling(print_node);
    char *operand = parsing_tree_get_data(operand_node);
    if (strcmp(operand, "expr") == 0) {
        handle_expr(operand);
    }

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
    parsing_tree_st *term_node = parsing_tree_get_child(parsing_tree_node);
    char *term_data = parsing_tree_get_data(term_node);
    parsing_tree_st *res1_node = parsing_tree_get_sibling(term_node);
    char *res1_data = parsing_tree_get_data(res1_node);

    if (strcmp(data, "term") == 0 && strcmp(res1_data, "res1") == 0) {
        handle_term(term_node);
    }
    else {
        //error();
    }
        
    if (parsing_tree_get_child(res1_node) != NULL) {
        handle_res1(res1_node);
    }
}

/**
 * @brief handle term form parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 */
void *handle_term(parsing_tree_node_st *parsing_tree_node, symbol_table_st *symbol_table) {
    parsing_tree_st *factor_node = parsing_tree_get_child(parsing_tree_node);
    char *factor_data = parsing_tree_get_data(factor);
    parsing_tree_st *res2_node = parsing_tree_get_sibling(factor_node);
    char *res2_data = parsing_tree_get_data(res2_node);

    if (strcmp(factor_data, "factor") == 0 && strcmp(res2_data, "res2") == 0) {
        handle_factor(factor_node);
    }
    else {
        //error();
    }
    if (parsing_tree_get_child(res2_node) != NULL) {
        handle_res2(child);
    }
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
    parsing_tree_st *term_node = parsing_tree_get_sibling(operator_node);
    char *left_operand = parsing_tree_get_data(operator_node);
    char *right_operand = parsing_tree_get_data(term_node);

    if (strcmp(right_operand, "term") == 0) {
        handle_term(term_node);
    }

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

    if (strcmp(operand, "expr") == 0) {
        handle_expr(operand);
    }

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
    parsing_tree_st *factor_node = parsing_tree_get_sibling(operator_node);
    char *left_operand = parsing_tree_get_data(operator_node);
    char *right_operand = parsing_tree_get_data(factor_node);

    if (strcmp(right_operand, "factor")) {
        handle_factor(factor_node);
    }
    else {
        //error();
    }

    if (strcmp(left_operand, "*") == 0) {
        //bytecode_len = strlen("ADD ") + strlen(left_operand) + strlen(" ") + strlen(right_operand);
        //bytecode = (char *)malloc(bytecode_len);
        //snprintf(bytecode, bytecode_len, "ADD %s %s", left_operand, right_operand);
    }
    else if (strcmp(left_operand, "/") == 0) {
        //bytecode_len = strlen("SUB ") + strlen(left_operand) + strlen(" ") + strlen(right_operand);
        //bytecode = (char *)malloc(bytecode_len);
        //snprintf(bytecode, bytecode_len, "SUB %s %s", left_operand, right_operand);
    }
    else if (strcmp(left_operand, "%") == 0) {
        //bytecode_len = strlen("SUB ") + strlen(left_operand) + strlen(" ") + strlen(right_operand);
        //bytecode = (char *)malloc(bytecode_len);
        //snprintf(bytecode, bytecode_len, "SUB %s %s", left_operand, right_operand);
    }
    else
    {
        //error();
    }

    new_node = link_node_new(bytecode, free);
    link_list_append(byte_code, new_node);

    return left_operand;
}


#ifdef XTEST
//tree structure
typedef struct TreeNode {  
    char *data;  
    struct TreeNode *child  
}TreeNode;  

typedef struct TreeNode* Tree;  

int i;
Tree init_tree(Tree t) {
    i = 0;
    return t = NULL;
}

void create_tree(Tree *t, char *s) {
    char *ch = s[i];
    i++;
    if(ch == '#')
        *t = NULL;
    else {
        *t = (TreeNode*)malloc(sizeof(TreeNode));
        (*t)->data = ch;
        create_tree(&(*t)->child, s);
    }
}

void test_case_one() {
    printf("Case One");
    //create tree
    Tree *t;
    char *ch_list = {"i", "is", "3"};
    create_tree(t, ch_list);

    parsing_tree_node_st *parsing_tree_node = parsing_tree_new(t, free);
    link_list_st *byte_code = link_list_init();
    char *data = handle_assign_stmt(byte_code, parsing_tree_node);

    if(strcmp(data, "i") == 0 && strcmp(byte_code, "MOV i 3") == 0) {
        printf("test_case_one success");
        parsing_tree_free(parsing_tree_node);
        link_list_free(byte_code);
    }
    else {
        prinf("test_case_one failed");
    }
}

void test_case_two() {
    printf("test case Two");
    //create tree
    Tree *t;
    char *ch_list = {"var", "i"};
    create_tree(t, ch_list);
    parsing_tree_node_st *parsing_tree_node = parsing_tree_new(t, free);
    link_list_st *byte_code = link_list_init();
    char *data = handle_assign_stmt(byte_code, parsing_tree_node);

    if(strcmp(data, "i") == 0 && strcmp(byte_code, "DEC i") == 0) {
        printf("test_case_two success");
        parsing_tree_free(parsing_tree_node);
        link_list_free(byte_code);
    }
    else {
        prinf("test_case_two failed");
    }
}

int main() {
    test_case_one();
    test_case_two();
}

#endif // XTEST
