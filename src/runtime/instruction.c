/**
 * @file instruction.c
 * @brief Purpose: implemetation of the machine instruction.
 * @version 0.5
 * @date 04.23.2017
 * @author Xiangyu Guo
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "instruction.h"

#define BUFFER_SIZE         (255)                   /**< input buffer size */
#define DEFAULT_ARRAY_SIZE  (64)                    /**< dynamic array default size */
#define RESIZE_FACTOR       (2)                     /**< resize factor when dynamic array is too small */

struct label_table {
    char *label_name;                               /**< label name without ":" */
    unsigned int address;                           /**< the address of the label */
};

struct instruction {
    char *op_code;                                  /**< operation code */
    char *op_first;                                 /**< first operands */
    char *op_second;                                /**< second operands */
};

struct instruction_set {
    instruction_st *instructs;                      /**< all instructions */
    label_table_st *labels;                         /**< labels in instructions */
    int count;                                      /**< total of instructions */
    int program_counter;                            /**< program counter(PC) */
    int flag_register;                              /**< flag register for cmp result */
};

/**
 * @brief load an ASM program into the runtime.
 * @param file_path ASM file path. 
 * @param instruct_set [out] loaded instruction sequence.
 * @return total count of instructions.
 */
static int s_load_program(const char *, instruction_set_st *);

/**
 * @brief replace label in ASM program into real address.
 * @param instruct_set [in/out] instructions going to replace.
 * @param labels [in] label table with real address.
 */
static void s_replace_label(instruction_st *, label_table_st *);

/**
 * @brief load an ASM program into the runtime.
 * @param file_path path of asm file.
 * @return instruct_set loaded instruction sequence.
 */
instruction_set_st *instruction_load_program(const char *file_path) {
    instruction_set_st *instructions = NULL;

    if (file_path == NULL)
        return NULL;

    instructions = (instruction_set_st *)malloc(sizeof(instruction_set_st));
    if (instructions == NULL)
        exit(ENOMEM);

    instructions->instructs = (instruction_st *)malloc(DEFAULT_ARRAY_SIZE *
                                                       sizeof(instruction_st));
    if (instructions->instructs == NULL)
        exit(ENOMEM);

    instructions->labels = (label_table_st *)malloc(DEFAULT_ARRAY_SIZE *
                                                    sizeof(label_table_st));
    if (instructions->labels == NULL)
        exit(ENOMEM);

    instructions->count = DEFAULT_ARRAY_SIZE;

    instructions->count = s_load_program(file_path, instructions);

    instructions->program_counter = 0;

    instructions->flag_register = 0;

    return instructions;
}

/**
 * @brief clean up the instruction set.
 * @param instructions, a valid instruction set object.
 */
void instruction_clean_up(instruction_set_st *instructions) {
    int i;
    if (instructions == NULL)
        return;

    for (i = 0; i < instructions->count; i++) {
        free(instructions->instructs[i].op_code);
        free(instructions->instructs[i].op_first);
        free(instructions->instructs[i].op_second);
    }

    free(instructions->instructs);

    // todo: clean up label table

    free(instructions->labels);

    free(instructions);
}

/**
 * @brief get next instruction from instruction set
 * @param instruction_set a valid instruction_set object.
 * @return NULL, failed or no more instructions; otherwise a pointer to the instruction.
 */
instruction_st *instruction_set_get_instruction(instruction_set_st *instructions) {
    int old_pc = 0;
    if (instructions == NULL)
        return NULL;

    if (instructions->program_counter >= instructions->count)
        return NULL;

    old_pc = instructions->program_counter;
    instructions->program_counter++;
#ifdef DEBUG
    fprintf(stderr, "pc: %d\n", old_pc);
#endif
    return &(instructions->instructs[old_pc]);
}

/**
 * @brief set a new program counter
 * @param instruction_set a valid instruction_set object.
 * @param new_pc new program counter address.
 */
void instruction_set_set_pc(instruction_set_st *instructions, int new_pc) {
    if (instructions == NULL)
        return;

    instructions->program_counter = new_pc;
}

/**
 * @brief get the comparision result
 * @param instruction_set a valid instruction_set object.
 * @return flag value.
 */
int instruction_set_get_flag(instruction_set_st *instructions) {
    if (instructions == NULL)
        return 0;
    return instructions->flag_register;
}

/**
 * @brief set a new comparision result
 * @param instruction_set a valid instruction_set object.
 * @param new_flag new flag value.
 */
void instruction_set_set_flag(instruction_set_st *instructions, int new_flag) {
    if (instructions == NULL)
        return;

    instructions->flag_register = new_flag;
}

/**
 * @brief get operation code from an instruction.
 * @param instruction, a valid instruction object.
 * @return op_code, operation code
 */
char *instruction_get_op_code(instruction_st *instruction) {
    if (instruction == NULL)
        return NULL;
    return instruction->op_code;
}

/**
 * @brief get operation code from an instruction.
 * @param instruction, a valid instruction object.
 * @return operand, first operand
 */
char *instruction_get_op_first(instruction_st *instruction) {
    if (instruction == NULL)
        return NULL;
    return instruction->op_first;

}

/**
 * @brief get operation code from an instruction.
 * @param instruction, a valid instruction object.
 * @return operand, second operand
 */
char *instruction_get_op_second(instruction_st *instruction) {
    if (instruction == NULL)
        return NULL;
    return instruction->op_second;
}

/**
 * @brief load an ASM program into the runtime.
 * @param file_path ASM file path.
 * @param instruct_set [out] loaded instruction sequence.
 * @return total count of instructions.
 */
static int s_load_program(const char *file_path, instruction_set_st *instructions) {
    FILE *fin = NULL;
    char input_buff[BUFFER_SIZE];
    char *op_code;
    char *op_first;
    char *op_second;
    int count = 0;

    fin = fopen(file_path, "r");
    if (!fin) {
        printf("load %s failed!\n", file_path);
        exit(ENOENT);
    }
    while (fgets(input_buff, BUFFER_SIZE, fin)) {
#ifdef DEBUG
        fprintf(stderr, "line: %d, content: %s\n", count, input_buff);
#endif
        if (count >= instructions->count) {
            instructions->instructs = realloc(instructions->instructs,
                                              instructions->count * RESIZE_FACTOR);

            if (instructions->instructs == NULL)
                exit(ENOMEM);

            instructions->count *= RESIZE_FACTOR;
        }

        // spilit by ' ', get first op code or label.
        op_code = strtok(input_buff, " \n");
        // todo: check op_code is label and put into label table with count(address).

        // spilit by ' ', get first oprand and second oprand.
        op_first = strtok(NULL, " \n");
        op_second = strtok(NULL, " \n");

#ifdef DEBUG
        fprintf(stderr, "code: %s, first %s, second %s\n", op_code, op_first, op_second );
#endif
        instructions->instructs[count].op_code = strdup(op_code);
        if (op_first != NULL)
            instructions->instructs[count].op_first = strdup(op_first);
        else
            instructions->instructs[count].op_first = NULL;
        if (op_second != NULL)
            instructions->instructs[count].op_second = strdup(op_second);
        else
            instructions->instructs[count].op_second = NULL;
        count++;
    }
    fclose(fin);
    s_replace_label(instructions->instructs, instructions->labels);
    return count;
}

/**
 * @brief replace label in ASM program into real address.
 * @param instruct_set [in/out] instructions going to replace.
 * @param labels [in] label table with real address.
 */
static void s_replace_label(instruction_st *instructions, label_table_st *lables) {
    // todo: next phase
}