/**
 * @file instruction.h
 * @brief Purpose: declaration of the machine instruction.
 * @version 0.5
 * @date 04.23.2017
 * @author Xiangyu Guo
 */
#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

typedef struct label_table label_table_st;
struct label_table;

typedef struct instruction instruction_st;
struct instruction;

typedef struct instruction_set instruction_set_st;
struct instruction_set;

/**
 * @brief load an ASM program into the runtime.
 * @param file_path path of asm file.
 * @return instruct_set loaded instruction sequence.
 */
instruction_set_st *instruction_load_program(const char *);

#endif