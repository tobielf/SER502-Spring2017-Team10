/**
 * @file runtime.c
 * @brief Purpose: main entrance of the runtime
 * @version 0.5
 * @date 04.16.2017
 * @author Xiangyu Guo
 */
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "storage.h"

typedef struct label_table
{
    char *label_name;                               /**< label name without ":" */
    unsigned int address;                           /**< the address of the label */
} label_table_st;

typedef struct instruction
{
    char *op_code;                                  /**< operation code */
    char *op_first;                                 /**< first operands */
    char *op_second;                                /**< second operands */
} instruction;

typedef struct instruction_set
{
    instruction *instructs;                         /**< all instructions */
    int count;                                      /**< total of instructions */
    int program_counter;                            /**< program counter(PC) */

} instruction_set_st;

typedef void (*eval)(void *, void *);               /**< function pointer of eval functions */

typedef struct operation {
    char *op_code;                                  /**< operation code */
    eval eval_func;                                 /**< evaluate funcion on this operation code */
} operation_st;

static machine_memory_st *s_machine_store;

/**
 * @brief evaluate function of all binary operations
 * @param first_operand, first operand.
 * @param second_operand, second operand.
 * @param op_type operation type.(+ - * / % =)
 */
static void eval_bin_op_helper(void *, void *, char);

/**
 * @brief evaluate function of "DEC" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_dec(void *, void *);

/**
 * @brief evaluate function of "MOV" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_mov(void *, void *);

/**
 * @brief evaluate function of "OUT" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_out(void *, void *);

/**
 * @brief evaluate function of "ADD" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_add(void *, void *);

/**
 * @brief evaluate function of "SUB" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_sub(void *, void *);

/**
 * @brief evaluate function of "MUL" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_mul(void *, void *);

/**
 * @brief evaluate function of "DIV" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_div(void *, void *);

/**
 * @brief evaluate function of "MOD" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_mod(void *, void *);
/**
 * @brief all operations provided by runtime.
 * Type 1: declare
 * DEC var1            ; declare a variable
 *
 * Type 2: assignment
 * MOV var1, var2/value        ; assign var2/value to var1 
 *
 * Type 3: arithmetic operation
 * ADD var1, var2/value        ; add var2/value to var1
 * SUB var1, var2/value        ; sub var2/value from var1
 * MUL var1, var2/value        ; mul var2/value to var1
 * DIV var1, var2/value        ; div var2/value from var1
 * MOD var1, var2/value        ; mod var1 with var2/value
 *
 *
 * Type 5: output result
 * OUT var1/value          ; Output var1/value. 
 */
static operation_st g_operations[] = { {"DEC", eval_dec}, 
                                       {"MOV", eval_mov},
                                       {"OUT", eval_out},
                                       {"ADD", eval_add},
                                       {"SUB", eval_sub},
                                       {"MUL", eval_mul},
                                       {"DIV", eval_div},
                                       {"MOD", eval_mod},
                                       {NULL , NULL} };

/**
 * @brief load an ASM program into the runtime.
 * @param instruct_set [out] loaded instruction sequence.
 * @param labels [out] loaded labels.
 */
static void s_load_program(instruction_set_st *, label_table_st *);

/**
 * @brief replace label in ASM program into real address.
 * @param instruct_set [in/out] instructions going to replace.
 * @param labels [in] label table with real address.
 */
static void s_replace_label(instruction_set_st *, label_table_st *);

/**
 * @brief evaluate the ASM program.
 * @param instruct_set [in] loaded instruction sequence.
 * @param machine_store [in/out] the storage of the virtual machine.
 */
static void s_evaluate(instruction_set_st *);

int main()
{
    instruction_set_st *instructions = NULL;
    label_table_st *labels = NULL;

    s_machine_store = machine_memory_init();

    s_load_program(instructions, labels);

    s_replace_label(instructions, labels);

    s_evaluate(instructions);
    return 0;
}

/**
 * @brief load an ASM program into the runtime.
 * @param instruct_set [out] loaded instruction sequence.
 * @param labels [out] loaded labels.
 */
static void s_load_program(instruction_set_st *instructions, label_table_st *lables) {

}

/**
 * @brief replace label in ASM program into real address.
 * @param instruct_set [in/out] instructions going to replace.
 * @param labels [in] label table with real address.
 */
static void s_replace_label(instruction_set_st *instructions, label_table_st *lables) {

}

/**
 * @brief evaluate the ASM program.
 * @param instruct_set [in] loaded instruction sequence.
 * @param machine_store [in/out] the storage of the virtual machine.
 */
static void s_evaluate(instruction_set_st *instructions) {

}

/**
 * @brief evaluate function of "DEC" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_dec(void *first_operand, void *second_operand) {
    memory_st *variable_memory;
    char *variable_name = NULL;

    if (first_operand == NULL)
        return;

    variable_name = (char *)first_operand;
    // check on this scope, if exist warning redefine and exit.
    variable_memory = machine_memory_get_variable(s_machine_store, 
                                                    variable_name,
                                                    MEMORY_CURRENT_SCOPE);
    if (variable_memory != NULL) {
        fprintf(stderr, "Redeclare variable: %s exit\n", variable_name);
        exit(EINVAL);
    }

    // doesn't exist, create a new one.
    if (machine_memory_set_variable(s_machine_store, variable_name, 
                                    0, MEMORY_CURRENT_SCOPE) != 0) {
        fprintf(stderr, "Can't not create new variable.\n");
        exit(ENOMEM);
    }

}

/**
 * @brief evaluate function of "OUT" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_out(void *first_operand, void *second_operand) {
    memory_st *variable_memory;
    char *var_one = NULL;
    int value = 0;

    if (first_operand == NULL)
        return;

    var_one = (char *)first_operand;

    if (isalpha(var_one[0])) {
        // check var_one on ALL scope, if doesn't exist, warning and exit.
        variable_memory = machine_memory_get_variable(s_machine_store, 
                                                      var_one, 
                                                      MEMORY_ALL_SCOPE);
        if (variable_memory == NULL) {
            fprintf(stderr, "Using undeclared variables! Exit\n");
            exit(EINVAL);
        }
        // value 
        value = memory_get_value(variable_memory);
    } else {
        value = atoi(var_one);
    }

    printf("%d\n", value);
}

/**
 * @brief evaluate function of "MOV" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_mov(void *first_operand, void *second_operand) {
    eval_bin_op_helper(first_operand, second_operand, '=');
}

/**
 * @brief evaluate function of "ADD" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_add(void *first_operand, void *second_operand) {
    eval_bin_op_helper(first_operand, second_operand, '+');
}

/**
 * @brief evaluate function of "SUB" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_sub(void *first_operand, void *second_operand) {
    eval_bin_op_helper(first_operand, second_operand, '-');
}

/**
 * @brief evaluate function of "MUL" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_mul(void *first_operand, void *second_operand) {
    eval_bin_op_helper(first_operand, second_operand, '*');
}

/**
 * @brief evaluate function of "DIV" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_div(void *first_operand, void *second_operand) {
    eval_bin_op_helper(first_operand, second_operand, '/');
}

/**
 * @brief evaluate function of "MOD" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_mod(void *first_operand, void *second_operand) {
    eval_bin_op_helper(first_operand, second_operand, '%');
}

/**
 * @brief evaluate function of all binary operations
 * @param first_operand, first operand.
 * @param second_operand, second operand.
 * @param op_type operation type.(+ - * / % =)
 */
static void eval_bin_op_helper(void *first_operand, 
                               void *second_operand, 
                               char op_type) {
    memory_st *var_mem_one;
    memory_st *var_mem_two;
    char *var_one = NULL;
    char *var_two = NULL;
    int value_one = 0;
    int value_two = 0;

    if (first_operand == NULL || second_operand == NULL)
        return;

    var_one = (char *)first_operand;
    var_two = (char *)second_operand;

    // check var_one on ALL scope, if doesn't exist, warning and exit.
    var_mem_one = machine_memory_get_variable(s_machine_store, 
                                              var_one, 
                                              MEMORY_ALL_SCOPE);
    if (var_mem_one == NULL) {
        fprintf(stderr, "Using undeclared variables %s! Exit\n", var_one);
        exit(EINVAL);
    }
    // value_one = from var_one on the storage.
    value_one = memory_get_value(var_mem_one);

    if (isalpha(var_two[0])) {
        // check var_two on ALL scope, if doesn't exist, warning and exit.
        var_mem_two = machine_memory_get_variable(s_machine_store, 
                                                  var_two, 
                                                  MEMORY_ALL_SCOPE);
        if (var_mem_two == NULL) {
            fprintf(stderr, "Using undeclared variables %s! Exit\n", var_one);
            exit(EINVAL);
        }
        // value_two = from var_two on the storage.
        value_two = memory_get_value(var_mem_two);
    } else {
        value_two = atoi(second_operand);
    }
 
    switch (op_type) {
        case '+':
            value_one += value_two;
            break;
        case '-':
            value_one -= value_two;
            break;
        case '*':
            value_one *= value_two;
            break;
        case '/':
            value_one /= value_two;
            break;
        case '%':
            value_one %= value_two;
            break;
        case '=':
            value_one = value_two;
            break;
        default:
            exit(EPERM);
            break;
    }
    
    // put value into the var_one.
    memory_set_value(var_mem_one, value_one);
}
