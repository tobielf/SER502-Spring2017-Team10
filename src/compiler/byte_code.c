/**
 * @file byte_code.c
 * @brief Purpose: byte code operation
 * @version 1.0
 * @date 04.18.2017
 * @author Rundong Zhu
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "utils/link_list.h"
#include "utils/symbol_table.h"
#include "utils/parsing_tree.h"

#include "utils/error.h"

#include "byte_code.h"

static int handle_if_stmt_helper(parsing_tree_st *then_node);

static void byte_code_new(link_list_st *, char *, char *, char *);

static void handle_stmt_list(parsing_tree_st *, link_list_st *); 

static void handle_stmt(parsing_tree_st *, link_list_st *); 

static char *handle_boolean_value(parsing_tree_st *, link_list_st *);

static char *handle_boolean_expr(parsing_tree_st *, link_list_st *);

static void handle_if_stmt(parsing_tree_st *, link_list_st *); 

static void handle_for_stmt(parsing_tree_st *, link_list_st *); 

static char *handle_expr(parsing_tree_st *, link_list_st *); 

static char *handle_term(parsing_tree_st *, link_list_st *); 

static void handle_decl_stmt(parsing_tree_st *, link_list_st *); 

static void handle_assign_stmt(parsing_tree_st *, link_list_st *); 

static void handle_print_stmt(parsing_tree_st *, link_list_st *); 

static char *handle_res1(parsing_tree_st *, link_list_st *, char *); 

static char *handle_factor(parsing_tree_st *, link_list_st *); 

static char *handle_res2(parsing_tree_st *, link_list_st *, char *);

static int temp_id = 0;

static int loop_id = 0;

static int if_id = 0;

static int else_id = 0;

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
            error_msg(__LINE__, "stmt_list error");
        }

        parsing_tree_st *semicolon_node = parsing_tree_get_sibling(stmt_node);
        char *semicolon_data = parsing_tree_get_data(semicolon_node);
        parsing_tree_st *stmt_list_node = parsing_tree_get_sibling(semicolon_node);

        if (strcmp(semicolon_data, ";") == 0 && stmt_list_node == NULL) {
            break;
        }
        char *stmt_list_data = parsing_tree_get_data(stmt_list_node);

        if (strcmp(stmt_list_data, "stmt_list") == 0) {
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
        handle_if_stmt(sub_stmt_node, byte_code);
    } else if (strcmp(sub_stmt_data, "for_stmt") == 0) {
        handle_for_stmt(sub_stmt_node, byte_code);
    } else if (strcmp(sub_stmt_data, "print_stmt") == 0) {
        handle_print_stmt(sub_stmt_node, byte_code);
    } else {
        error_msg(__LINE__, "stmt error");
    }
}

/**
 * @brief generate decl_stmt byte code from parsing tree.
 * @param node, a valid tree node
 * @param byte_code, a valid link list.
 */
static void handle_decl_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    parsing_tree_st *var_node = parsing_tree_get_child(parsing_tree_node);
    char *var_data = parsing_tree_get_data(var_node);
    if (strcmp(var_data, "var") != 0) {
        error_msg(__LINE__, "decl_stmt error");
    }
    parsing_tree_st *id_node = parsing_tree_get_sibling(var_node);
    char *id_data = parsing_tree_get_data(id_node);

    byte_code_new(byte_code, "DEC", id_data, "");
}

/**
 * @brief generate assign_stmt byte code from parsing tree.
 * @param node, a valid tree node.
 * @param byte_code, a valid link list.
 */
static void handle_assign_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    parsing_tree_st *id_node = parsing_tree_get_child(parsing_tree_node);
    parsing_tree_st *is_node = parsing_tree_get_sibling(id_node);
    char *id_data = parsing_tree_get_data(id_node);
    char *is_data = parsing_tree_get_data(is_node);
    if (strcmp(is_data, "is") != 0) {
        error_msg(__LINE__, "assign_stmt error");
    }
    parsing_tree_st *expr_node = parsing_tree_get_sibling(is_node);

    char *expr_data = parsing_tree_get_data(expr_node);
    if (strcmp(expr_data, "expr") == 0) {
        expr_data = handle_expr(expr_node, byte_code);
    } else {
        error_msg(__LINE__, "assign_stmt error");
    }

    byte_code_new(byte_code, "MOV", id_data, expr_data);
    free(expr_data);
}

/**
 * @brief generate if_stmt byte code from parsing tree.
 * @param node, a valid tree node.
 * @param byte_code, a valid link list.
 */
static void handle_if_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    if_id++;
    else_id++;

    int if_length;
    char *if_label;
    if_length = strlen("if") + get_digits_num(if_id) + strlen(":") + 1;
    if_label = (char *)malloc(if_length);
    snprintf(if_label, if_length, "if%d:", if_id);

    int if_end_target_len;
    char *if_end_target;
    if_end_target_len = strlen("if_end") + get_digits_num(if_id) + 1;
    if_end_target = (char *)malloc(if_end_target_len);
    snprintf(if_end_target, if_end_target_len, "if%d_end", if_id);

    int if_end_length;
    char *if_end_label;
    if_end_length = strlen("if_end:") + get_digits_num(if_id) + 1;
    if_end_label = (char *)malloc(if_end_length);
    snprintf(if_end_label, if_end_length, "if%d_end:", if_id);

    int else_target_len;
    char *else_target;
    else_target_len = strlen("else") + get_digits_num(else_id) + 1;
    else_target = (char *)malloc(else_target_len);
    snprintf(else_target, else_target_len, "else%d", else_id);

    int else_length;
    char *else_label;
    else_length = strlen("else") + get_digits_num(else_id) + strlen(":") + 1;
    else_label = (char *)malloc(else_length);
    snprintf(else_label, else_length, "else%d", else_id);
    snprintf(else_label, else_length, "else%d:", else_id);

    parsing_tree_st *if_node = parsing_tree_get_child(parsing_tree_node);
    char *if_data = parsing_tree_get_data(if_node);

    if (strcmp(if_data, "if") != 0) {
        error_msg(__LINE__, "if_stmt error");
    }

    parsing_tree_st *brace_left_node = parsing_tree_get_sibling(if_node);
    char *brace_left_data = parsing_tree_get_data(brace_left_node);
    if (strcmp(brace_left_data, "(") != 0)
        error_msg(__LINE__, "if_stmt error");

    parsing_tree_st *boolean_node = parsing_tree_get_sibling(brace_left_node);
    char *boolean_data = parsing_tree_get_data(boolean_node);
    parsing_tree_st *brace_right_node = parsing_tree_get_sibling(boolean_node);
    char *brace_right_data = parsing_tree_get_data(brace_right_node);
    if (strcmp(boolean_data, "boolean_expr") != 0 || strcmp(brace_right_data, ")") != 0)
        error_msg(__LINE__, "if_stmt error");

    byte_code_new(byte_code, if_label, "", "");

    char *target = NULL;

    int has_else = handle_if_stmt_helper(parsing_tree_get_sibling(brace_right_node));
    if (has_else) {
        target = else_target;
    } else {
        target = if_end_target;
    }

    boolean_data = handle_boolean_expr(boolean_node, byte_code);

    if (strcmp(boolean_data, "=") == 0) {
        byte_code_new(byte_code, "JNE", target, "");
    } else if (strcmp(boolean_data, "<>") == 0) {
        byte_code_new(byte_code, "JE", target, "");
    } else if (strcmp(boolean_data, ">") == 0) {
        byte_code_new(byte_code, "JLE", target, "");
    } else if (strcmp(boolean_data, ">=") == 0) {
        byte_code_new(byte_code, "JL", target, "");
    } else if (strcmp(boolean_data, "<") == 0) {
        byte_code_new(byte_code, "JGE", target, "");
    } else if (strcmp(boolean_data, "<=") == 0) {
        byte_code_new(byte_code, "JG", target, "");
    } else {
        error_msg(__LINE__, "boolean_expr error");
    }

    parsing_tree_st *then_node = parsing_tree_get_sibling(brace_right_node);
    parsing_tree_st *curlybrace_left_node = parsing_tree_get_sibling(then_node);
    parsing_tree_st *stmt_list_node = parsing_tree_get_sibling(curlybrace_left_node);
    char *stmt_list_data = parsing_tree_get_data(stmt_list_node);
    parsing_tree_st *curlybrace_right_node = parsing_tree_get_sibling(stmt_list_node);
    char *curlybrace_right_data = parsing_tree_get_data(curlybrace_right_node);
    if (strcmp(stmt_list_data, "stmt_list") != 0 || strcmp(curlybrace_right_data, "}") != 0)
        error_msg(__LINE__, "then_stmt error");

    handle_stmt_list(stmt_list_node, byte_code);

    if (has_else) {
        byte_code_new(byte_code, "JMP", if_end_target, "");

        byte_code_new(byte_code, else_label, "", "");

        parsing_tree_st *else_node = parsing_tree_get_sibling(curlybrace_right_node);
        char *else_data = parsing_tree_get_data(else_node);
        if (strcmp(else_data, "else") != 0)
            error_msg(__LINE__, "else_stmt error");

        curlybrace_left_node = parsing_tree_get_sibling(else_node);
        stmt_list_node = parsing_tree_get_sibling(curlybrace_left_node);
        stmt_list_data = parsing_tree_get_data(stmt_list_node);
        curlybrace_right_node = parsing_tree_get_sibling(stmt_list_node);
        curlybrace_right_data = parsing_tree_get_data(curlybrace_right_node);
        if (strcmp(stmt_list_data, "stmt_list") != 0 || strcmp(curlybrace_right_data, "}") != 0)
            error_msg(__LINE__, "else_stmt error");

        handle_stmt_list(stmt_list_node, byte_code);
    }

    byte_code_new(byte_code, if_end_label, "", "");

    free(if_label);
    free(if_end_target);
    free(if_end_label);
    free(else_target);
    free(else_label);
}

/**
 * @brief generate for_stmt byte code from parsing tree.
 * @param node, a valid tree node.
 * @param byte_code, a valid link list.
 */
static void handle_for_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    loop_id++;

    int loop_length;
    char *loop_string;
    loop_length = strlen("for") + get_digits_num(loop_id) + strlen(":") + 1;
    loop_string = (char *)malloc(loop_length);
    snprintf(loop_string, loop_length, "for%d:", loop_id);

    int loop_end_target_len;
    char *loop_end_target;
    loop_end_target_len = strlen("for_end") + get_digits_num(loop_id) + strlen(":") + 1;
    loop_end_target = (char *)malloc(loop_end_target_len);
    snprintf(loop_end_target, loop_end_target_len, "for%d_end", loop_id);

    int loop_end_len;
    char *loop_end_label;
    loop_end_len = strlen("for_end") + get_digits_num(loop_id) + strlen(":") + 1;
    loop_end_label = (char *)malloc(loop_end_len);
    snprintf(loop_end_label, loop_end_len, "for%d_end:", loop_id);

    int loop_target_len;
    char *loop_target;
    loop_target_len = strlen("for") + get_digits_num(loop_id) + 1;
    loop_target = (char *)malloc(loop_length);
    snprintf(loop_target, loop_target_len, "for%d", loop_id);

    parsing_tree_st *for_node = parsing_tree_get_child(parsing_tree_node);
    char *for_data = parsing_tree_get_data(for_node);

    if (strcmp(for_data, "for") != 0)
        error_msg(__LINE__, "for_stmt error");

    parsing_tree_st *var_node = parsing_tree_get_sibling(for_node);
    if (var_node == NULL)
        error_msg(__LINE__, "var error");

    char *var_data = parsing_tree_get_data(var_node);
    parsing_tree_st *from_node = parsing_tree_get_sibling(var_node);

    char *from_data = parsing_tree_get_data(from_node);
    if (strcmp(from_data, "from") != 0)
        error_msg(__LINE__, "from error");

    parsing_tree_st *expr1_node = parsing_tree_get_sibling(from_node);
    char *expr1_data = parsing_tree_get_data(expr1_node);
    if (strcmp(expr1_data, "expr") != 0)
        error_msg(__LINE__, "expr1 error");

    expr1_data = handle_expr(expr1_node, byte_code);

    byte_code_new(byte_code, "MOV", var_data, expr1_data);

    parsing_tree_st *to_node = parsing_tree_get_sibling(expr1_node);
    char *to_data = parsing_tree_get_data(to_node);
    if (strcmp(to_data, "to") != 0)
        error_msg(__LINE__, "to error");

    parsing_tree_st *expr2_node = parsing_tree_get_sibling(to_node);
    char *expr2_data = parsing_tree_get_data(expr2_node);
    if (strcmp(expr2_data, "expr") != 0) 
        error_msg(__LINE__, "expr2 error");
    
    expr2_data = handle_expr(expr2_node, byte_code);

    byte_code_new(byte_code, loop_string, "", "");
    byte_code_new(byte_code, "CMP", var_data, expr2_data); 
    byte_code_new(byte_code, "JE", loop_end_target, "");

    parsing_tree_st *step_node = parsing_tree_get_sibling(expr2_node);
    char *step_data = parsing_tree_get_data(step_node);
    if (strcmp(step_data, "step") != 0)
        error_msg(__LINE__, "step error");


    parsing_tree_st *expr3_node = parsing_tree_get_sibling(step_node);
    char *expr3_data = parsing_tree_get_data(expr3_node);
    if (strcmp(expr3_data, "expr") != 0)
        error_msg(__LINE__, "expr3 error");

    parsing_tree_st *curlybrace_left_node = parsing_tree_get_sibling(expr3_node);
    char *curlybrace_left_data = parsing_tree_get_data(curlybrace_left_node);
    parsing_tree_st *stmt_list_node = parsing_tree_get_sibling(curlybrace_left_node);
    char *stmt_list_data = parsing_tree_get_data(stmt_list_node);
    if (strcmp(stmt_list_data, "stmt_list")!= 0 || strcmp(curlybrace_left_data, "{") != 0)
        error_msg(__LINE__, "stmt_list error");

    handle_stmt_list(stmt_list_node, byte_code);

    parsing_tree_st *curlybrace_right_node = parsing_tree_get_sibling(stmt_list_node);
    char *curlybrace_right_data = parsing_tree_get_data(curlybrace_right_node);
    if (strcmp(curlybrace_right_data, "}") != 0)
        error_msg(__LINE__, "right curlybrace error");

    expr3_data = handle_expr(expr3_node, byte_code);

    byte_code_new(byte_code, "MOV", var_data, expr3_data);
    byte_code_new(byte_code, "JMP", loop_target, "");
    byte_code_new(byte_code, loop_end_label, "", "");

    free(expr1_data);
    free(expr2_data);
    free(expr3_data);
    free(loop_string);
    free(loop_end_target);
    free(loop_end_label);
    free(loop_target);
}

/**
 * @brief generate print_stmt byte code from parsing tree.
 * @param node, a valid tree node.
 * @param byte_code, a valid link list.
 */
static void handle_print_stmt(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    parsing_tree_st *print_node = parsing_tree_get_child(parsing_tree_node);
    char *print_data = parsing_tree_get_data(print_node);

    if (strcmp(print_data, "print") != 0) {
        error_msg(__LINE__, "print error");
    }

    parsing_tree_st *operand_node = parsing_tree_get_sibling(print_node);
    char *operand = parsing_tree_get_data(operand_node);
    if (strcmp(operand, "expr") != 0)
        error_msg(__LINE__, "expr_stmt error");

    operand = handle_expr(operand_node, byte_code);

    byte_code_new(byte_code, "OUT", operand, "");
    free(operand);
}

/**
 * @brief generate boolean_value byte code from parsing tree.
 * @param node, a valid tree node.
 * @param byte_code, a valid link list.
 * @return boolean value, "1" for true, "0" for false.
 */
static char *handle_boolean_value(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    parsing_tree_st *value_node = parsing_tree_get_child(parsing_tree_node);
    char *bool_value = parsing_tree_get_data(value_node);
    if (strcmp(bool_value, "true") == 0)
        return strdup("1");
    return strdup("0");
}

/**
 * @brief generate boolean_expr byte code from parsing tree.
 * @param node, a valid tree node.
 * @param byte_code, a valid link list.
 * @return boolean operator.
 */
static char *handle_boolean_expr(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {
    parsing_tree_st *expr1_node = parsing_tree_get_child(parsing_tree_node);
    char *expr1_data = parsing_tree_get_data(expr1_node);
    char *operator_data = NULL;
    char *expr2_data = NULL;

    if (strcmp(expr1_data, "expr") != 0 && strcmp(expr1_data, "boolean_value") != 0)
        error_msg(__LINE__, "boolean_expr error");

    if (strcmp(expr1_data, "boolean_value") == 0) {
        expr1_data = handle_boolean_value(expr1_node, byte_code);
        operator_data = "=";
        expr2_data = strdup("1");
    } else {
        expr1_data = handle_expr(expr1_node, byte_code);
        parsing_tree_st *operator_node = parsing_tree_get_sibling(expr1_node);
        operator_data = parsing_tree_get_data(operator_node);
        parsing_tree_st *expr2_node = parsing_tree_get_sibling(operator_node);
        expr2_data = parsing_tree_get_data(expr2_node);
        if (strcmp(expr2_data, "expr") != 0)
            error_msg(__LINE__, "boolean_expr error");
            
        expr2_data = handle_expr(expr2_node, byte_code);
    }

    byte_code_new(byte_code, "CMP", expr1_data, expr2_data);

    free(expr1_data);
    free(expr2_data);
    return operator_data;
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

    char *rc;  //return code
    if (strcmp(term_data, "term") != 0)
        error_errno(EINVAL);

    rc = handle_term(term_node, byte_code);
       
    if (parsing_tree_get_child(res1_node) != NULL) {
        rc = handle_res1(res1_node, byte_code, rc);
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

    char *rc; //return code
    if (strcmp(factor_data, "factor") != 0)
        error_errno(EINVAL);
    
    rc = handle_factor(factor_node, byte_code);

    if (parsing_tree_get_child(res2_node) != NULL) {
        rc = handle_res2(res2_node, byte_code, rc);
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
    temp_id++;

    int temp_length;
    char *temp_string;
    temp_length = strlen("_temp") + get_digits_num(temp_id) + 1;
    temp_string = (char *)malloc(temp_length);
    snprintf(temp_string, temp_length, "_temp%d", temp_id);

    parsing_tree_st *operator_node = parsing_tree_get_child(parsing_tree_node);
    if (operator_node == NULL) {
        free(temp_string);
        temp_id--;
        return NULL;
    }

    parsing_tree_st *term_node = parsing_tree_get_sibling(operator_node);
    char *operator_data = parsing_tree_get_data(operator_node);
    char *term_data = parsing_tree_get_data(term_node);

    if (strcmp(term_data, "term") == 0) {
        term_data = handle_term(term_node, byte_code);
    }

    byte_code_new(byte_code, "DEC", temp_string, "");

    byte_code_new(byte_code, "MOV", temp_string, terms_data);

    free(terms_data);
    if (strcmp(operator_data, "+") == 0) {
        byte_code_new(byte_code, "ADD", temp_string, term_data);
    } else if (strcmp(operator_data, "-") == 0) {
        byte_code_new(byte_code, "SUB", temp_string, term_data);
    } else {
        error_msg(__LINE__, "res1 error");
    }

    free(term_data);

    parsing_tree_st *res1_node = parsing_tree_get_sibling(term_node);
    char *ret_res1 = handle_res1(res1_node, byte_code, temp_string);

    if (ret_res1 != NULL) {
        temp_string = ret_res1;
    }

    return temp_string;
}

/**
 * @brief generate factor byte code form link list and parsing tree.
 * @param byte_code, a valid link list.
 * @param node, a valid tree node.
 * @return NULL on failed, otherwise a char array.
 */
static char *handle_factor(parsing_tree_st *parsing_tree_node, link_list_st *byte_code) {

    parsing_tree_st *operand_node = parsing_tree_get_child(parsing_tree_node);
    char *operand_data = strdup(parsing_tree_get_data(operand_node));

    if (strcmp(operand_data, "(") == 0) {
        parsing_tree_st *expr_node = parsing_tree_get_sibling(operand_node);
        char *expr_data = parsing_tree_get_data(expr_node);
        parsing_tree_st *brace_node = parsing_tree_get_sibling(expr_node);
        char *brace_data = parsing_tree_get_data(brace_node);
        if (strcmp(expr_data, "expr") == 0 && strcmp(brace_data, ")") == 0) {
            free(operand_data);
            operand_data = handle_expr(expr_node, byte_code);
        }
    }

    return operand_data;
}

/**
* @brief generate res2 byte code form link list and parsing tree.
* @param byte_code, a valid link list.
* @param node, a valid tree node.
* @return NULL on failed, otherwise a valid link list.
*/

static char *handle_res2(parsing_tree_st *parsing_tree_node, link_list_st *byte_code, char *factors_data) {
    temp_id++;

    int temp_length;
    char *temp_string;
    temp_length = strlen("_temp") + get_digits_num(temp_id) + 1;
    temp_string = (char *)malloc(temp_length);
    snprintf(temp_string, temp_length, "_temp%d", temp_id);

    parsing_tree_st *operator_node = parsing_tree_get_child(parsing_tree_node);
    if (operator_node == NULL) {
        free(temp_string);
        temp_id--;
        return NULL;
    }

    parsing_tree_st *factor_node = parsing_tree_get_sibling(operator_node);
    char *operator_data = parsing_tree_get_data(operator_node);
    char *factor_data = parsing_tree_get_data(factor_node);

    if (strcmp(factor_data, "factor") == 0) {
        factor_data = handle_factor(factor_node, byte_code);
    } else {
        error_errno(EINVAL);
    }

    byte_code_new(byte_code, "DEC", temp_string, "");

    byte_code_new(byte_code, "MOV", temp_string, factors_data);

    free(factors_data);

    if (strcmp(operator_data, "*") == 0) {
        byte_code_new(byte_code, "MUL", temp_string, factor_data);
    } else if (strcmp(operator_data, "/") == 0) {
        byte_code_new(byte_code, "DIV", temp_string, factor_data);
    } else if (strcmp(operator_data, "%") == 0) {
        byte_code_new(byte_code, "MOD", temp_string, factor_data);
    } else {
        error_msg(__LINE__, "reds2 error");
    }

    free(factor_data);

    parsing_tree_st *res2_node = parsing_tree_get_sibling(factor_node);
    char *ret_res2 = handle_res2(res2_node, byte_code, temp_string);

    if (ret_res2 != NULL) {
        temp_string = ret_res2;
    }

    return temp_string;
}

static void byte_code_new(link_list_st *byte_code, char *op_code, char *first_oprand, char *second_oprand) {
    char *bytecode = NULL;
    int bytecode_len = 0;
    link_node_st *new_node = NULL;

    if (byte_code == NULL || op_code == NULL || first_oprand == NULL || second_oprand == NULL)
        return; // error();

    bytecode_len = strlen(op_code) + 1 + strlen(first_oprand) + 1 + strlen(second_oprand) + 1;
    bytecode = (char *)malloc(bytecode_len);
    snprintf(bytecode, bytecode_len, "%s %s %s", op_code, first_oprand, second_oprand);

    new_node = link_node_new(bytecode, free);
    link_list_append(byte_code, new_node);
}

static int handle_if_stmt_helper(parsing_tree_st *then_node) {
    return  parsing_tree_get_sibling(
                parsing_tree_get_sibling(
                    parsing_tree_get_sibling(
                        parsing_tree_get_sibling(
                            then_node
                        )
                    )
                )
            ) != NULL;
}


#ifdef XTEST
//tree structure

parsing_tree_st *setup_expr_tree_with_number() {
    parsing_tree_st *expr_node = parsing_tree_new("expr", NULL);
    parsing_tree_st *node1 = NULL;
    parsing_tree_st *node2 = NULL;
    node1 = node2;
    node2 = parsing_tree_new("term", NULL);
    parsing_tree_set_child(expr_node, node2);

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

    return expr_node;
}

int print_byte_code(link_node_st *node, void *cb_data) {
    char *str = link_node_get_data(node);

    if (str != NULL) {
        printf("%s\n", str);
        return LINK_LIST_CONTINUE;
    }

    return LINK_LIST_STOP;
}

int print_tree(parsing_tree_st *node, void *cb_data) {
    printf("%s\n", (char *)parsing_tree_get_data(node));
    return TREE_TRAVERSE_CONTINUE;
}

void test_suite_one() {
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
    parsing_tree_free(root);
    link_list_free(byte_code);
}

void test_suite_two() {
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

    parsing_tree_free(root);
    link_list_free(byte_code);
}

void test_suite_three() {
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
    node2 = setup_expr_tree_with_number();
    parsing_tree_set_sibling(node1, node2);

    byte_code = semantic_analysis(root, NULL);
    link_list_traverse(byte_code, print_byte_code, NULL);

    parsing_tree_free(root);
    link_list_free(byte_code);
}

void test_suite_four() {
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

    node2 = parsing_tree_new("*", NULL);
    parsing_tree_set_child(node3, node2);
    node1 = node2;
    node2 = parsing_tree_new("factor", NULL);
    parsing_tree_set_sibling(node1, node2);
    node3 = parsing_tree_new("2", NULL);
    parsing_tree_set_child(node2, node3);

    byte_code = semantic_analysis(root, NULL);
    link_list_traverse(byte_code, print_byte_code, NULL);

    parsing_tree_free(root);
    link_list_free(byte_code);
}

void test_suite_five() {
    link_list_st *byte_code = NULL;

    printf("test suite five\n");

    // Create syntax tree for "i is i + 10 % i;" statement;

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

    node1 = parsing_tree_new("+", NULL);
    parsing_tree_set_child(node3, node1);
    node2 = parsing_tree_new("term", NULL);
    parsing_tree_set_sibling(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("factor", NULL);
    parsing_tree_set_child(node1, node2);
    node3 = parsing_tree_new("res2", NULL);
    parsing_tree_set_sibling(node2, node3);

    node1 = node2;
    node2 = parsing_tree_new("10", NULL);
    parsing_tree_set_child(node1, node2);

    node2 = parsing_tree_new("%", NULL);
    parsing_tree_set_child(node3, node2);
    node3 = parsing_tree_new("factor", NULL);
    parsing_tree_set_sibling(node2, node3);

    node1 = parsing_tree_new("i", NULL);
    parsing_tree_set_child(node3, node1);

    byte_code = semantic_analysis(root, NULL);
    link_list_traverse(byte_code, print_byte_code, NULL);

    parsing_tree_free(root);
    link_list_free(byte_code);
}

void test_suite_six() {
    printf("test suite six\n");

    link_list_st *byte_code = NULL;
    parsing_tree_st *root = parsing_tree_new("program", NULL);
    parsing_tree_st *node1 = parsing_tree_new("stmt_list", NULL);
    parsing_tree_st *node2 = parsing_tree_new("stmt", NULL);
    parsing_tree_set_child(root, node1);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new(";", NULL);
    parsing_tree_set_sibling(node1, node2);
    node2 = parsing_tree_new("if_stmt", NULL);
    parsing_tree_set_child(node1, node2);

    parsing_tree_st *if_stmt = node2;
    node1 = parsing_tree_new("if", NULL);
    parsing_tree_set_child(if_stmt, node1);
    node2 = parsing_tree_new("(", NULL);
    parsing_tree_set_sibling(node1, node2);
    parsing_tree_st *bool_expr = parsing_tree_new("boolean_expr", NULL);
    parsing_tree_set_sibling(node2, bool_expr);
    node1 = setup_expr_tree_with_number();
    parsing_tree_set_child(bool_expr, node1);
    node2 = parsing_tree_new("=", NULL);
    parsing_tree_set_sibling(node1, node2);
    node1 = setup_expr_tree_with_number();
    parsing_tree_set_sibling(node2, node1);
    node2 = parsing_tree_new(")", NULL);
    parsing_tree_set_sibling(bool_expr, node2);
    node1 = parsing_tree_new("then", NULL);
    parsing_tree_set_sibling(node2, node1);
    node2 = parsing_tree_new("{", NULL);
    parsing_tree_set_sibling(node1, node2);

    parsing_tree_st *then_stmt = parsing_tree_new("stmt_list", NULL);
    parsing_tree_set_sibling(node2, then_stmt);
    node1 = parsing_tree_new("}", NULL);
    parsing_tree_set_sibling(then_stmt, node1);
    node2 = parsing_tree_new("stmt", NULL);
    parsing_tree_set_child(then_stmt, node2);

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

    node1 = parsing_tree_new("+", NULL);
    parsing_tree_set_child(node3, node1);
    node2 = parsing_tree_new("term", NULL);
    parsing_tree_set_sibling(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new("factor", NULL);
    parsing_tree_set_child(node1, node2);
    node3 = parsing_tree_new("res2", NULL);
    parsing_tree_set_sibling(node2, node3);

    node1 = node2;
    node2 = parsing_tree_new("10", NULL);
    parsing_tree_set_child(node1, node2);

    node2 = parsing_tree_new("%", NULL);
    parsing_tree_set_child(node3, node2);
    node3 = parsing_tree_new("factor", NULL);
    parsing_tree_set_sibling(node2, node3);

    node1 = parsing_tree_new("i", NULL);
    parsing_tree_set_child(node3, node1);

    parsing_tree_prefix_traverse(root, print_tree, NULL);
    byte_code = semantic_analysis(root, NULL);
    link_list_traverse(byte_code, print_byte_code, NULL);

    parsing_tree_free(root);
    link_list_free(byte_code);
}

void test_suite_seven() {
    printf("test suite seven\n");

    link_list_st *byte_code = NULL;
    parsing_tree_st *root = parsing_tree_new("program", NULL);
    parsing_tree_st *node1 = parsing_tree_new("stmt_list", NULL);
    parsing_tree_st *node2 = parsing_tree_new("stmt", NULL);
    parsing_tree_set_child(root, node1);
    parsing_tree_set_child(node1, node2);

    node1 = node2;
    node2 = parsing_tree_new(";", NULL);
    parsing_tree_set_sibling(node1, node2);
    parsing_tree_st *node3 = parsing_tree_new("stmt_list", NULL);
    parsing_tree_set_sibling(node2, node3);

    node2 = parsing_tree_new("decl_stmt", NULL);
    parsing_tree_set_child(node1, node2);

    node1 = parsing_tree_new("var", NULL);
    parsing_tree_set_child(node2, node1);
    node2 = parsing_tree_new("i", NULL);
    parsing_tree_set_sibling(node1, node2);

    node1 = parsing_tree_new("stmt", NULL);
    parsing_tree_set_child(node3, node1);
    node2 = parsing_tree_new(";", NULL);
    parsing_tree_set_sibling(node1, node2);

    node3 = parsing_tree_new("for_stmt", NULL);
    parsing_tree_set_child(node1, node3);

    node2 = parsing_tree_new("for", NULL);
    parsing_tree_set_child(node3, node2);

    node1 = parsing_tree_new("i", NULL);
    parsing_tree_set_sibling(node2, node1);
    node2 = parsing_tree_new("from", NULL);
    parsing_tree_set_sibling(node1, node2);

    parsing_tree_st *expr1_node = parsing_tree_new("expr", NULL);
    parsing_tree_set_sibling(node2, expr1_node);

    node2 = parsing_tree_new("term", NULL);
    parsing_tree_set_child(expr1_node, node2);

    node3 = parsing_tree_new("res1", NULL);
    parsing_tree_set_sibling(node2, node3);

    node3 = parsing_tree_new("factor", NULL);
    parsing_tree_set_child(node2, node3);

    node1 = parsing_tree_new("res2", NULL);
    parsing_tree_set_sibling(node3, node1);

    node2 = parsing_tree_new("1", NULL);
    parsing_tree_set_child(node3, node2);

    node1 = parsing_tree_new("to", NULL);
    parsing_tree_set_sibling(expr1_node, node1);

    parsing_tree_st *expr2_node = parsing_tree_new("expr", NULL);
    parsing_tree_set_sibling(node1, expr2_node);

    node2 = parsing_tree_new("term", NULL);
    parsing_tree_set_child(expr2_node, node2);

    node3 = parsing_tree_new("res1", NULL);
    parsing_tree_set_sibling(node2, node3);

    node3 = parsing_tree_new("factor", NULL);
    parsing_tree_set_child(node2, node3);

    node1 = parsing_tree_new("res2", NULL);
    parsing_tree_set_sibling(node3, node1);

    node2 = parsing_tree_new("10", NULL);
    parsing_tree_set_child(node3, node2);

    node2 = parsing_tree_new("step", NULL);
    parsing_tree_set_sibling(expr2_node, node2);

    parsing_tree_st *expr3_node = parsing_tree_new("expr", NULL);
    parsing_tree_set_sibling(node2, expr3_node);

    node2 = parsing_tree_new("term", NULL);
    parsing_tree_set_child(expr3_node, node2);

    node3 = parsing_tree_new("res1", NULL);
    parsing_tree_set_sibling(node2, node3);

    node3 = parsing_tree_new("factor", NULL);
    parsing_tree_set_child(node2, node3);

    node1 = parsing_tree_new("res2", NULL);
    parsing_tree_set_sibling(node3, node1);

    node2 = parsing_tree_new("i", NULL);
    parsing_tree_set_child(node3, node2);

    node2 = parsing_tree_new("*", NULL);
    parsing_tree_set_child(node1, node2);

    node3 = parsing_tree_new("factor", NULL);
    parsing_tree_set_sibling(node2, node3);

    node2 = parsing_tree_new("2", NULL);
    parsing_tree_set_child(node3, node2);

    node2 = parsing_tree_new("{", NULL);
    parsing_tree_set_sibling(expr3_node, node2);

    node3 = parsing_tree_new("stmt_list", NULL);
    parsing_tree_set_sibling(node2, node3);

    node1 = parsing_tree_new("stmt", NULL);
    parsing_tree_set_child(node3, node1);
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

    node2 = parsing_tree_new("}", NULL);
    parsing_tree_set_sibling(node3, node2);

    fprintf(stderr, "This is the mocking input parsing tree: \n");
    parsing_tree_prefix_traverse(root, print_tree, NULL);
    byte_code = semantic_analysis(root, NULL);
    fprintf(stderr, "This is the output byte code: \n");
    link_list_traverse(byte_code, print_byte_code, NULL);

    parsing_tree_free(root);
    link_list_free(byte_code);
}

int main() {
    test_suite_one();
    test_suite_two();
    test_suite_three();
    test_suite_four();
    test_suite_five();
    test_suite_six();
    test_suite_seven();
    return 0;
}

#endif // XTEST
