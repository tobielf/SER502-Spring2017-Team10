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
#include "instruction.h"

typedef void (*eval)(void *, void *);               /**< function pointer of eval functions */

typedef struct operation {
    char *op_code;                                  /**< operation code */
    eval eval_func;                                 /**< evaluate funcion on this operation code */
} operation_st;

static machine_memory_st *s_machine_store;          /**< environment storage during run time */

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
 * @brief evaluate function of "CMP" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_cmp(void *, void *);

/**
 * @brief evaluate function of "JE" instruction
 * @param first label.
 * @param second unused, will ignore.
 */
static void eval_je(void *, void *);

/**
 * @brief evaluate function of "JNE" instruction
 * @param first label.
 * @param second unused, will ignore.
 */
static void eval_jne(void *, void *);

/**
 * @brief evaluate function of "JL" instruction
 * @param first label.
 * @param second unused, will ignore.
 */
static void eval_jl(void *, void *);

/**
 * @brief evaluate function of "JLE" instruction
 * @param first label.
 * @param second unused, will ignore.
 */
static void eval_jle(void *, void *);

/**
 * @brief evaluate function of "JG" instruction
 * @param first label.
 * @param second unused, will ignore.
 */
static void eval_jg(void *, void *);

/**
 * @brief evaluate function of "JGE" instruction
 * @param first label.
 * @param second unused, will ignore.
 */
static void eval_jge(void *, void *);

/**
 * @brief evaluate function of "JMP" instruction
 * @param first label.
 * @param second unused, will ignore.
 */
static void eval_jmp(void *, void *);

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
 * Type 4: compare and jump operation
 * CMP var1, var2/value        ; CMP var1 and var2/value, set $flag = var1 - var2/value.
 * JE  label                   ; Jump to label if $flag Equal to zero.
 * JNE label                   ; Jump to label if $flag Not Equal to zero.
 * JL  label                   ; Jump to label if $flag Less than zero.
 * JLE label                   ; Jump to label if $flag Less than or Equal to zero.
 * JG  label                   ; Jump to label if $flag Great than zero.
 * JGE label                   ; Jump to label if $flag Great than or Equal to zero.
 * JMP label                   ; Jump to label, always.
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
                                       {"CMP", eval_cmp},
                                       {"JE" , eval_je },
                                       {"JNE", eval_jne},
                                       {"JL" , eval_jl },
                                       {"JLE", eval_jle},
                                       {"JG" , eval_jg },
                                       {"JGE", eval_jge},
                                       {"JMP", eval_jmp},
                                       {NULL , NULL} };

/**
 * @brief evaluate the ASM program.
 * @param instruct_set [in] loaded instruction sequence.
 */
static void s_evaluate(instruction_set_st *);

/**
 * @brief print out the usage information of runtime.
 */
static void s_usage();

/**
 * @brief main entrance of runtime.
 * @param argc arguments count.
 * @param argv arguments vector.
 * @return 0 on success; otherwise errno.
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        s_usage();
        return 0;
    }

    instruction_set_st *instructions = NULL;

    s_machine_store = machine_memory_init();

    instructions = instruction_load_program(argv[1]);

    s_evaluate(instructions);

    instruction_clean_up(instructions);

    machine_memory_fini(s_machine_store);
    return 0;
}
/**
 * @brief print out the usage information of runtime.
 */
static void s_usage() {
    printf("Usage:\n");
    printf("./runtime <input file>\n");
    printf("e.g ./runtime program1.asm\n");
}

/**
 * @brief evaluate the ASM program.
 * @param instruct_set [in] loaded instruction sequence.
 */
static void s_evaluate(instruction_set_st *instructions) {
    instruction_st *next_inst = NULL;
    char *op_code = NULL;
    char *op_first = NULL;
    char *op_second = NULL;
    int i;

    if (instructions == NULL)
        exit(EINVAL);

    while ((next_inst = instruction_set_get_instruction(instructions)) != NULL) {
        op_code = instruction_get_op_code(next_inst);
        op_first = instruction_get_op_first(next_inst);
        op_second = instruction_get_op_second(next_inst);
#ifdef DEBUG
        fprintf(stderr, "code: %s, first: %s, second: %s\n", op_code, op_first, op_second );
#endif
        if (op_code == NULL) {
            fprintf(stderr, "Fetch failed\n");
            exit(EINVAL);
        }
        // find method for op_code
        i = 0;
        while (g_operations[i].op_code != NULL) {
            if (strcmp(op_code, g_operations[i].op_code) == 0) {
                g_operations[i].eval_func(op_first, op_second);
                break;
            }
            i++;
        }

        if (g_operations[i].op_code == NULL) {
            fprintf(stderr, "Error, unsupported instruction\n");
            exit(EPERM);
        }
    }
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
