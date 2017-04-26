/**
 * @file byte_code.c
 * @brief Purpose: byte code operation
 * @version 4.0
 * @date 04.18.2017
 * @author Rundong Zhu
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils/link_list.h"
#include "utils/symbol_table.h"
#include "utils/parsing_tree.h"

#include "utils/error.h"

#include "byte_code.h"

static void handle_stmt_list(parsing_tree_st *parsing_tree_node, link_list_st *byte_code); 

static void handle_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code); 

static char *handle_if_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code); 

static char *handle_for_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code); 

static char *handle_expr(parsing_tree_st *parsing_tree_node, link_list_st *byte_code); 

static char *handle_term(parsing_tree_st *parsing_tree_node, link_list_st *byte_code); 

static void handle_decl_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code); 

static void handle_assign_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code); 

static void handle_print_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code); 

static char *handle_res1(parsing_tree_st *parsing_tree_node, link_list_st *byte_code, char *terms_data); 

static char *handle_factor(parsing_tree_st *parsing_tree_node, link_list_st *byte_code); 

static char *handle_res2(parsing_tree_st *parsing_tree_node, link_list_st *byte_code, char *factors_data);

static int temp_id = 0;

static int loop_id = 0;

static int if_id = 0;

/*
 * @brief get number of digits from an integer
 * @para int_num, an integer
 * @return 0 of failed, otherwise a valid integer
 */
int get_digits_num(int int_num) {
    int count = 0;
    while (int_num != 0) {
        int_num /= 10;
        ++count;
    }
    return count;
}

/**
 * @brief generate byte code from parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 * @return NULL on failed, otherwise a valid link list.
 */
link_list_st *semantic_analysis(parsing_tree_st *parsing_tree_node, symbol_table_st *symbol_table) {
    link_list_st *byte_code = NULL;

    char *program_data = NULL;

    if (parsing_tree_node == NULL)
        return NULL;

    program_data = parsing_tree_get_data(parsing_tree_node);
    if (strcmp(program_data, "program") != 0)
        return NULL;

    byte_code = link_list_init();
    parsing_tree_st *stmt_list_node = parsing_tree_get_child(parsing_tree_node);
    char *stmt_list_data = parsing_tree_get_data(stmt_list_node);
    if (strcmp(stmt_list_data, "stmt_list") == 0) {
        handle_stmt_list(stmt_list_node, byte_code);
    } else {
        printf("program error");
        return NULL;
    }

    return byte_code;
}

/**
 * @brief handle stmt_list from parsing tree.
 * @param node, a valid tree node.
 * @param byte_code, a valid link list.
 */
static void handle_stmt_list(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    parsing_tree_st *stmt_node = parsing_tree_get_child(parsing_tree_node);
    char *stmt_data = parsing_tree_get_data(stmt_node);

    while (1) {
        if (strcmp(stmt_data, "stmt") == 0) {
            handle_stmt(stmt_node, byte_code);
        } else {
            //error();
        }

        parsing_tree_st *semicolon_node = parsing_tree_get_sibling(stmt_node);
        char *semicolon_data = parsing_tree_get_data(semicolon_node);
        parsing_tree_st *stmt_list_node = parsing_tree_get_sibling(semicolon_node);

        if (strcmp(semicolon_data, ";") == 0 && stmt_list_node == NULL) {
            break;
			//error_msg()
        }
        char *stmt_list_data = parsing_tree_get_data(stmt_list_node);

        if (strcmp(stmt_list_data, "stmt_list") != 0) {
            stmt_node = parsing_tree_get_child(stmt_list_node);
            stmt_data = parsing_tree_get_data(stmt_node);
        }
    }
}

/**
 * @brief handle stmt from parsing tree.
 * @param node, a valid tree node.
 * @param byte_code, a valid link list.
 */
static void handle_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    parsing_tree_st *sub_stmt_node = parsing_tree_get_child(parsing_tree_node);
    char *sub_stmt_data = parsing_tree_get_data(sub_stmt_node);

    if (strcmp(sub_stmt_data, "decl_stmt") == 0) {
        handle_decl_stmt(sub_stmt_node, byte_code);
    } else if (strcmp(sub_stmt_data, "assign_stmt") == 0) {
        handle_assign_stmt(sub_stmt_node, byte_code);
    } else if (strcmp(sub_stmt_data, "if_stmt") == 0) {
        //handle_if_stmt(sub_stmt_node, byte_code);
    } else if (strcmp(sub_stmt_data, "for_stmt") == 0) {
        //handle_for_stmt(sub_stmt_node, byte_code);
    } else if (strcmp(sub_stmt_data, "print_stmt") == 0) {
        handle_print_stmt(sub_stmt_node, byte_code);
    } else {
        //error();
    }
}

/**
 * @brief generate decl_stmt byte code from parsing tree.
 * @param node, a valid tree node
 * @param byte_code, a valid link list.
 */
static void handle_decl_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    parsing_tree_st *var_node = parsing_tree_get_child(parsing_tree_node);
    char *var_data = parsing_tree_get_data(var_node);
	if (strcmp(var_data, "var") != 0) {
        //error
    }
    parsing_tree_st *id_node = parsing_tree_get_sibling(var_node);
    char *id_data = parsing_tree_get_data(id_node);

    bytecode_len = strlen("DEC ") + strlen(id_data) + 1;
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "DEC %s", id_data);

    new_node = link_node_new(bytecode, free);
    link_list_append(byte_code, new_node);
}

/**
 * @brief generate assign_stmt byte code from parsing tree.
 * @param node, a valid tree node.
 * @param byte_code, a valid link list.
 */
static void handle_assign_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    parsing_tree_st *id_node = parsing_tree_get_child(parsing_tree_node);
    parsing_tree_st *is_node = parsing_tree_get_sibling(id_node);
    char *id_data = parsing_tree_get_data(id_node);
    char *is_data = parsing_tree_get_data(is_node);
    if (strcmp(is_data, "is") != 0) {
        //error();
    }
    parsing_tree_st *expr_node = parsing_tree_get_sibling(is_node);

    char *expr_data = parsing_tree_get_data(expr_node);
    if (strcmp(expr_data, "expr") == 0) {
       expr_data = handle_expr(expr_node, byte_code);
    } else {
        //error();
    }

    bytecode_len = strlen("MOV ") + strlen(id_data) + strlen(" ") + strlen(expr_data) + 1;
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "MOV %s %s", id_data, expr_data);

    new_node = link_node_new(bytecode, free);
    link_list_append(byte_code, new_node);
}

static char *handle_if_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    //TODO
    return NULL;
}
static char *handle_for_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    //TODO
    return NULL;
}

/**
 * @brief generate print_stmt byte code from parsing tree.
 * @param node, a valid tree node.
 * @param byte_code, a valid link list.
 */
static void handle_print_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
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
        operand = handle_expr(operand_node, byte_code);
    } else {
        //error
    }

    bytecode_len = strlen("OUT ") + strlen(operand) + 1;
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "OUT %s", operand);

    new_node = link_node_new(bytecode, free);
    link_list_append(byte_code, new_node);
}

/**
 * @brief handle expr form parsing tree and symbol table.
 * @param byte_code, a valid link list.
 * @param node, a valid tree node.
 * @return NULL on failed, otherwise a char array.
 */
static char *handle_expr(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    parsing_tree_st *term_node = parsing_tree_get_child(parsing_tree_node);
    char *term_data = parsing_tree_get_data(term_node);
    parsing_tree_st *res1_node = parsing_tree_get_sibling(term_node);
    char *res1_data = parsing_tree_get_data(res1_node);

    char *rc;  //return code
    if (strcmp(term_data, "term") == 0) {
        term_data = handle_term(term_node, byte_code);
        rc = term_data;
    }
       
    if (parsing_tree_get_child(res1_node) != NULL) {
        rc = handle_res1(res1_node, byte_code, term_data);

        //rc = "_temp";
    }

    return rc;
}

/**
 * @brief handle term form parsing tree and symbol table.
 * @param byte_code, a valid link list.
 * @param node, a valid tree node.
 * @return NULL on failed, otherwise a char array.
 */
static char *handle_term(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    parsing_tree_st *factor_node = parsing_tree_get_child(parsing_tree_node);
    char *factor_data = parsing_tree_get_data(factor_node);
    parsing_tree_st *res2_node = parsing_tree_get_sibling(factor_node);
    char *res2_data = parsing_tree_get_data(res2_node);

    char *rc; //return code

    if (strcmp(factor_data, "factor") == 0) {
        factor_data = handle_factor(factor_node, byte_code);
        rc = factor_data;
    }

    if (parsing_tree_get_child(res2_node) != NULL) {
        res2_data = handle_res2(res2_node, byte_code, factor_data);
        rc = res2_data;
    }

    return rc;
}

/**
 * @brief generate res1 byte code form link list and parsing tree.
 * @param byte_code, a valid link list.
 * @param node, a valid tree node.
 * @return NULL on failed, otherwise a char array.
 */
static char *handle_res1(parsing_tree_st *parsing_tree_node, link_list_st *byte_code, char *terms_data) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    temp_id++;

    int temp_length;
    char *temp_string;
    temp_length = strlen("_temp") + get_digits_num(temp_id) + 1;
    temp_string = (char *)malloc(temp_length);
    snprintf(temp_string, temp_length, "_temp%d", temp_id);
	
	//char *temp_string = "ttp";

    parsing_tree_st *operator_node = parsing_tree_get_child(parsing_tree_node);
    parsing_tree_st *term_node = parsing_tree_get_sibling(operator_node);
    char *operator_data = parsing_tree_get_data(operator_node);
    char *term_data = parsing_tree_get_data(term_node);

	//char *rc; //return code

    if (strcmp(term_data, "term") == 0) {
        term_data = handle_term(term_node, byte_code);
		//rc = terms_data;
    }

    bytecode_len = strlen("DEC ") + strlen(temp_string) + 1;
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "DEC %s", temp_string);

    new_node = link_node_new(bytecode, NULL);
    link_list_append(byte_code, new_node);

    bytecode_len = strlen("MOV ") + temp_length + strlen(terms_data) + 1;
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "MOV %s %s", temp_string, terms_data);

    new_node = link_node_new(bytecode, NULL);
    link_list_append(byte_code, new_node);

    if (strcmp(operator_data, "+") == 0) {
        bytecode_len = strlen("ADD ") + temp_length + strlen(term_data) + 1;
        bytecode = (char *)malloc(bytecode_len);
        snprintf(bytecode, bytecode_len, "ADD %s %s", temp_string, term_data);
    } else if (strcmp(operator_data, "-") == 0) {
        bytecode_len = strlen("SUB ") + temp_length + strlen(term_data) + 1;
        bytecode = (char *)malloc(bytecode_len);
        snprintf(bytecode, bytecode_len, "SUB %s %s", temp_string, term_data);
    } else {
        //error
    }

    temp_id--;
    new_node = link_node_new(bytecode, NULL);
    link_list_append(byte_code, new_node);

    return temp_string;
    //return term_data;
}

/**
 * @brief generate factor byte code form link list and parsing tree.
 * @param byte_code, a valid link list.
 * @param node, a valid tree node.
 * @return NULL on failed, otherwise a char array.
 */
static char *handle_factor(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    //char *bytecode = NULL;
    //int bytecode_len = 0;
    //link_node_st *new_node = NULL;

    parsing_tree_st *operand_node = parsing_tree_get_child(parsing_tree_node);
    char *operand_data = parsing_tree_get_data(operand_node);

    if (strcmp(operand_data, "(") == 0) {
        parsing_tree_st *expr_node = parsing_tree_get_sibling(operand_node);
        char *expr_data = parsing_tree_get_data(expr_node);
        parsing_tree_st *brace_node = parsing_tree_get_sibling(expr_node);
        char *brace_data = parsing_tree_get_data(brace_node);
        if (strcmp(expr_data, "expr") == 0 && strcmp(brace_data, ")") == 0) {
            operand_data = handle_expr(expr_node, byte_code);
        }
    }
    /*
    bytecode_len = strlen(operand_data) + 1;
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "%s", operand_data);

    new_node = link_node_new(bytecode, NULL);
    link_list_append(byte_code, new_node);
    */
    return operand_data;
}

/**
* @brief generate res2 byte code form link list and parsing tree.
* @param byte_code, a valid link list.
* @param node, a valid tree node.
* @return NULL on failed, otherwise a valid link list.
*/

static char *handle_res2(parsing_tree_st *parsing_tree_node, link_list_st *byte_code, char *factors_data) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    temp_id++;

    int temp_length;
    char *temp_string;
    temp_length = strlen("_temp") + get_digits_num(temp_id) + 1;
    temp_string = (char *)malloc(temp_length);
    snprintf(temp_string, temp_length, "_temp%d", temp_id);

    parsing_tree_st *operator_node = parsing_tree_get_child(parsing_tree_node);
    parsing_tree_st *factor_node = parsing_tree_get_sibling(operator_node);
    char *operator_data = parsing_tree_get_data(operator_node);
    char *factor_data = parsing_tree_get_data(factor_node);

    if (strcmp(factor_data, "factor")) {
        handle_factor(factor_node, byte_code);
    }

    bytecode_len = strlen("DEC ") + temp_length + 1;
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "DEC %", temp_string);

    new_node = link_node_new(bytecode, NULL);
    link_list_append(byte_code, new_node);

    bytecode_len = strlen("MOV ") + temp_length + strlen(factors_data) + 1;
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "MOV %s %s", temp_string, factors_data);

    if (strcmp(operator_data, "*") == 0) {
        bytecode_len = strlen("MUL _temp") + temp_length + strlen(factor_data) + 1;
        bytecode = (char *)malloc(bytecode_len);
        snprintf(bytecode, bytecode_len, "MUL %s %s", temp_string, factor_data);
    } else if (strcmp(operator_data, "/") == 0) {
        bytecode_len = strlen("DIV _temp") + temp_length + strlen(factor_data) + 1;;
        bytecode = (char *)malloc(bytecode_len);
        snprintf(bytecode, bytecode_len, "DIV %s %s", temp_string, factor_data);
    } else if (strcmp(operator_data, "%") == 0) {
        bytecode_len = strlen("MOD _temp") + temp_length + strlen(factor_data) + 1;
        bytecode = (char *)malloc(bytecode_len);
        snprintf(bytecode, bytecode_len, "MOD %s %s", temp_string, factor_data);
    } else {
        //error();
    }

    temp_id--;
    new_node = link_node_new(bytecode, NULL);
    link_list_append(byte_code, new_node);

    return temp_string;
}


#ifdef XTEST
//tree structure
int print_byte_code(link_node_st *node, void *cb_data) {
    char *str = link_node_get_data(node);

    if (str != NULL) {
        printf("%s\n", str);
        return LINK_LIST_CONTINUE;
    }

    return LINK_LIST_STOP;
}

void test_suite_one() {
    int counter = 0;
    link_list_st *byte_code = NULL;

    printf("test suite one\n");

    // Create syntax tree for "var i;" statement;

    parsing_tree_st *root = parsing_tree_new("program", NULL);;
    parsing_tree_st *node1 = parsing_tree_new("stmt_list", NULL);
    parsing_tree_st *node2 = parsing_tree_new("stmt", NULL);
    parsing_tree_set_child(root, node1);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new(";", NULL);
    parsing_tree_set_sibling(node1, node2);
    node2 = parsing_tree_new("decl_stmt", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("var", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("i", NULL);
    parsing_tree_set_sibling(node1, node2);

    byte_code = semantic_analysis(root, NULL);
    link_list_traverse(byte_code, print_byte_code, NULL);
}

void test_suite_two() {
    int counter = 0;
    link_list_st *byte_code = NULL;

    printf("test suite two\n");

    // Create syntax tree for "print i;" statement;

    parsing_tree_st *root = parsing_tree_new("program", NULL);;
    parsing_tree_st *node1 = parsing_tree_new("stmt_list", NULL);
    parsing_tree_st *node2 = parsing_tree_new("stmt", NULL);
    parsing_tree_set_child(root, node1);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new(";", NULL);
    parsing_tree_set_sibling(node1, node2);
    node2 = parsing_tree_new("print_stmt", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("print", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("expr", NULL);
    parsing_tree_set_sibling(node1, node2);
	
    node1 = node2;
    node2 = parsing_tree_new("term", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = parsing_tree_new("res1", NULL);
    parsing_tree_set_sibling(node2, node1);

    node1 = node2;
    node2 = parsing_tree_new("factor", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = parsing_tree_new("res2", NULL);
    parsing_tree_set_sibling(node2, node1);

    node1 = node2;
    node2 = parsing_tree_new("i", NULL);
    parsing_tree_set_child(node1, node2);
	
    byte_code = semantic_analysis(root, NULL);
    link_list_traverse(byte_code, print_byte_code, NULL);
}

void test_suite_three() {
    int counter = 0;
    link_list_st *byte_code = NULL;

    printf("test suite three\n");

    // Create syntax tree for "i is 3;" statement;

    parsing_tree_st *root = parsing_tree_new("program", NULL);
    parsing_tree_st *node1 = parsing_tree_new("stmt_list", NULL);
    parsing_tree_st *node2 = parsing_tree_new("stmt", NULL);
    parsing_tree_set_child(root, node1);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new(";", NULL);
    parsing_tree_set_sibling(node1, node2);
    node2 = parsing_tree_new("assign_stmt", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("i", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = parsing_tree_new("is", NULL);
    parsing_tree_set_sibling(node2, node1);
    node2 = parsing_tree_new("expr", NULL);
    parsing_tree_set_sibling(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("term", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = parsing_tree_new("res1", NULL);
    parsing_tree_set_sibling(node2, node1);

    node1 = node2;
    node2 = parsing_tree_new("factor", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = parsing_tree_new("res2", NULL);
    parsing_tree_set_sibling(node2, node1);

    node1 = node2;
    node2 = parsing_tree_new("3", NULL);
    parsing_tree_set_child(node1, node2);

    byte_code = semantic_analysis(root, NULL);
    link_list_traverse(byte_code, print_byte_code, NULL);
}

void test_suite_four() {
    int counter = 0;
    link_list_st *byte_code = NULL;

    printf("test suite four\n");

    // Create syntax tree for "i is i + 3;" statement;

    parsing_tree_st *root = parsing_tree_new("program", NULL);
    parsing_tree_st *node1 = parsing_tree_new("stmt_list", NULL);
    parsing_tree_st *node2 = parsing_tree_new("stmt", NULL);
    parsing_tree_set_child(root, node1);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new(";", NULL);
    parsing_tree_set_sibling(node1, node2);
    node2 = parsing_tree_new("assign_stmt", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("i", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = parsing_tree_new("is", NULL);
    parsing_tree_set_sibling(node2, node1);
    node2 = parsing_tree_new("expr", NULL);
    parsing_tree_set_sibling(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("term", NULL);
    parsing_tree_set_child(node1, node2);

    parsing_tree_st *node3 = parsing_tree_new("res1", NULL);
    parsing_tree_set_sibling(node2, node3);

    node1 = node2;
    node2 = parsing_tree_new("factor", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = parsing_tree_new("res2", NULL);
    parsing_tree_set_sibling(node2, node1);
	
    node1 = node2;
    node2 = parsing_tree_new("i", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = parsing_tree_new("-", NULL);
    parsing_tree_set_child(node3, node1);
    node2 = parsing_tree_new("term", NULL);
    parsing_tree_set_sibling(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("factor", NULL);
    parsing_tree_set_child(node1, node2);
    node3 = parsing_tree_new("res2", NULL);
    parsing_tree_set_sibling(node2, node3);

    node1 = parsing_tree_new("3", NULL);
    parsing_tree_set_child(node2, node1);

    byte_code = semantic_analysis(root, NULL);
    link_list_traverse(byte_code, print_byte_code, NULL);
}

int main() {
    test_suite_one();
    test_suite_two();
    test_suite_three();
    test_suite_four();
}

#endif // XTEST
