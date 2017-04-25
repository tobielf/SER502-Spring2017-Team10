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

typedef struct label_info {
    char *label_name;                               /**< label name without ":" */
    unsigned int address;                           /**< the address of the label */
} label_st;

typedef struct label_table {
    int label_table_capacity;                       /**< the capacity of label table */
    int label_table_size;                           /**< the current size of label table */
    label_st *label_table;
} label_table_st;

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
static void s_replace_label(instruction_set_st *, label_table_st *);

/**
 * @brief insert a label into label table.
 * @param label_table a valid label table.
 * @param label the label string.
 * @param addr the address of the label.
 */
static void s_insert_label(label_table_st *, char *, unsigned int);

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

    instructions->labels = (label_table_st *)malloc(sizeof(label_table_st));
    if (instructions->labels == NULL)
        exit(ENOMEM);

    instructions->labels->label_table = (label_st *)malloc(DEFAULT_ARRAY_SIZE *
                                                            sizeof(label_st));

    instructions->labels->label_table_capacity = DEFAULT_ARRAY_SIZE;

    instructions->labels->label_table_size = 0;

    instructions->count = DEFAULT_ARRAY_SIZE;

    instructions->program_counter = 0;

    instructions->flag_register = 0;

    instructions->count = s_load_program(file_path, instructions);

    s_replace_label(instructions, instructions->labels);

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

    for (i = 0; i < instructions->labels->label_table_size; i++) {
        free(instructions->labels->label_table[i].label_name);
    }

    free(instructions->labels->label_table);

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
 * @brief look up a label address.
 * @param instruction_st a valid instruction_set object.
 * @param label, the label string going to lookup.
 * @return a valid address for program counter, if label doesn't exist, exit.
 */
unsigned int instruction_set_get_label(instruction_set_st *instructions, char *label) {
    int i;
    int label_len = 0;
    char *converted_label = NULL;
    label_len = strlen(label) + strlen(":") + 1;

    converted_label = (char *)malloc(label_len);
    snprintf(converted_label, label_len, "%s:", label);
    for (i = 0; i < instructions->labels->label_table_size; i++) {
        if (strcmp(converted_label, instructions->labels->label_table[i].label_name) == 0) {
            free(converted_label);
            return instructions->labels->label_table[i].address;
        }
    }
    fprintf(stderr, "Invalid label.\n");
    exit(EPERM);
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
        // check op_code is label and put into label table with count(address).
        if (strrchr(op_code, ':') != NULL) {
#ifdef DEBUG
            fprintf(stderr, "label: %s\n", op_code);
#endif
            s_insert_label(instructions->labels, op_code, count);
        }
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

    return count;
}

/**
 * @brief replace label in ASM program into real address.
 * @param instruct_set [in/out] instructions going to replace.
 * @param labels [in] label table with real address.
 */
static void s_replace_label(instruction_set_st *instructions, label_table_st *labels) {
    int i, j;
    char *label;

    for (i = 0; i < instructions->count; i++) {
        label = instructions->instructs[i].op_code;
        if (strrchr(label, ':')) {
            for (j = 0; j < labels->label_table_size; j++) {
                if (strcmp(label, labels->label_table[j].label_name) == 0)
                    labels->label_table[i].address = i;
            }
        }
    }
}

/**
 * @brief insert a label into label table.
 * @param label_table a valid label table.
 * @param label_str the label string.
 * @param addr the address of the label.
 */
static void s_insert_label(label_table_st *labels, char *label, unsigned int addr) {
    int index;
    if (labels == NULL || label == NULL)
        return;

    index = labels->label_table_size;
    if (index >= labels->label_table_capacity) {
        labels->label_table = realloc(labels->label_table, 
                                      labels->label_table_capacity * RESIZE_FACTOR);

        if (labels->label_table == NULL)
            exit(ENOMEM);

        labels->label_table_capacity *= RESIZE_FACTOR;
    }

    labels->label_table[index].label_name = strdup(label);

    labels->label_table[index].address = addr;

    labels->label_table_size++;
}