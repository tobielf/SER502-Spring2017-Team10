/**
 * @file symbol_table.h
 * @brief Purpose: symbol table data structure
 * @version 0.1
 * @date 04.15.2017
 * @author Xiangyu Guo
 */
#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

typedef struct symbol_table symbol_table_st;
struct symbol_table;

/**
 * @brief initialize the symbol table.
 * @return a valid symbol table object.
 */
symbol_table_st *symbol_table_init();

/**
 * @brief clean up the symbol table.
 * @param symbol_table a valid symbol table object.
 */
void symbol_table_fini(symbol_table_st *);

/**
 * @brief look up the symbol on symbol table
 * @param table a valid symbol table object.
 * @param symbol a symbol going to look up.
 * @return -1, not found; otherwise the index in symbol table.
 */
int symbol_table_lookup(symbol_table_st *, char *symbol);

/**
 * @brief insert the symbol to symbol table
 * @param table a valid symbol table object.
 * @param symbol a symbol going to insert.
 * @param token_val the value of the token.
 * @return -1, failed; otherwise the index inserted in symbol table.
 */
int symbol_table_insert(symbol_table_st *, char *symbol, int token_value);

#endif