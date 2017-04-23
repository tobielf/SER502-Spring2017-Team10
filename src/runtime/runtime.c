/**
 * @file runtime.c
 * @brief Purpose: main entrance of the runtime
 * @version 0.1
 * @date 04.16.2017
 * @author Xiangyu Guo
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define STATIC_MEMORY_SIZE      (32)                /**< memory size of the virtual machine */
#define SCOPE_BOUNDRAY_SIZE     (4)                 /**< array size of the scope boundray */
#define RESIZE_FACTOR           (2)                 /**< resize factor when memory size is too small */

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
} instruction_set_st;

typedef struct memory
{
    char *variable_name;                            /**< the name of a variable */
    int variable_value;                             /**< the value of a variable */
    int scope;                                      /**< the scope of the variable */
} memory_st;

typedef struct machine_memory
{
    int flag_register;                              /**< flag register for cmp result */
    int program_counter;                            /**< program counter(PC) */
    int allocated_address;                          /**< usage of static memory */
    memory_st *static_memory;                       /**< static memory */
} machine_memory_st;

typedef void (*eval)(void *, void *);               /**< function pointer of eval functions */

typedef struct operation {
    char *op_code;                                  /**< operation code */
    eval eval_func;                                 /**< evaluate funcion on this operation code */
} operation_st;

static int s_scope = 0;                             /**< the scope of variable */

static int *s_scope_boundary = NULL;                /**< indicate the scope range */

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
static void s_evaluate(instruction_set_st *, machine_memory_st *);

int main()
{
    machine_memory_st machine_store;
    instruction_set_st *instructions = NULL;
    label_table_st *labels = NULL;

    machine_store.flag_register = 0;
    machine_store.program_counter = 0;
    machine_store.static_memory = (memory_st *)malloc(STATIC_MEMORY_SIZE *
                                                            sizeof(memory_st));
    memset(machine_store.static_memory, 0, 
            sizeof(STATIC_MEMORY_SIZE*sizeof(memory_st)));

    s_scope_boundary = (int *)malloc(SCOPE_BOUNDRAY_SIZE);

    s_load_program(instructions, labels);

    s_replace_label(instructions, labels);

    s_evaluate(instructions, &machine_store);
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
static void s_evaluate(instruction_set_st *instructions, machine_memory_st *machine_storage) {

}

/**
 * @brief evaluate function of "DEC" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_dec(void *first_operand, void *second_operand) {
    char *variable_name = NULL;
    if (first_operand == NULL)
        return;

    variable_name = (char *)first_operand;
    // check on this scope, if exist warning redefine and exit.

    // doesn't exist, create a new one.

}

/**
 * @brief evaluate function of "OUT" instruction
 * @param first first operand.
 * @param second second operand.
 */
static void eval_out(void *first_operand, void *second_operand) {
    char *var_one = NULL;
    int value = 0;

    if (first_operand == NULL)
        return;

    var_one = (char *)first_operand;

    if (isalpha(var_one[0])) {
        // check var_one on ALL scope, if doesn't exist, warning and exit.
        // value 
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

static void eval_bin_op_helper(void *first_operand, void *second_operand, char op) {
    char *var_one = NULL;
    char *var_two = NULL;
    int value_one = 0;
    int value_two = 0;

    if (first_operand == NULL || second_operand == NULL)
        return;

    var_one = (char *)first_operand;
    var_two = (char *)second_operand;

    // check var_one on ALL scope, if doesn't exist, warning and exit.

    // value_one = from var_one on the storage.

    if (isalpha(var_two[0])) {
        // check var_two on ALL scope, if doesn't exist, warning and exit.

        // value_two = from var_two on the storage.
    } else {
        value_two = atoi(second_operand);
    }
 
    switch (op) {
        case '+':
            break;
        case '-':
            break;
        case '*':
            break;
        case '/':
            break;
        case '%':
            break;
        case '=':
            break;
        default:
            exit(-1);
            break;
    }
    
    // put value into the var_one.
}
