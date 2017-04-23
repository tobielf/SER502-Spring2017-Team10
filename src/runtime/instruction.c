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
#define DEFAULT_ARRAY_SIZE  (64)                    /**<  */
#define RESIZE_FACTOR       (2)                     /**<  */

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
};

/**
 * @brief load an ASM program into the runtime.
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

    return instructions;
}

/**
 * @brief load an ASM program into the runtime.
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
    printf("load %s\n", file_path);
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
        if (op_second != NULL)
            instructions->instructs[count].op_second = strdup(op_second);
        count++;
    }

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