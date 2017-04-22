/**
 * @file runtime.c
 * @brief Purpose: main entrance of the runtime
 * @version 0.1
 * @date 04.16.2017
 * @author Xiangyu Guo
 */
#include <stdio.h>
#include <stdlib.h>

#define STATIC_MEMORY_SIZE  (32)                    /**< memory size of the virtual machine */

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
} memory_st;

typedef struct machine_memory
{
    int flag_register;                              /**< flag register for cmp result */
    int program_counter;                            /**< program counter(PC) */
    memory_st static_memory[STATIC_MEMORY_SIZE];    /**< static memory */
} machine_memory_st;

typedef void (*eval)(void *, void *);               /**< function pointer of eval functions */

typedef struct operation {
    char *op_code;                                  /**< operation code */
    eval eval_func;                                 /**< evaluate funcion on this operation code */
} operation_st;

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
 * @brief all operations provided by runtime.
 */
static operation_st g_operations[] = { {"DEC", eval_dec}, 
                                       {"MOV", eval_mov},
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
    memset(machine_store.static_memory, 0, 
            sizeof(STATIC_MEMORY_SIZE*sizeof(memory_st)));

    s_load_program(instructions, labels);

    s_replace_label(instructions, labels);

    s_evaluate(instructions, &machine_store);
    return 0;
}