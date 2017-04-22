/**
 * @file symboltable.c
 * @brief purpose: to initialize and edit symbol table
 * @version 0.1
 * @date 04.21.2017
 * @author Katie MacArthur
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "symbol_table.h"

#define DEFAULT_ARRAY_SIZE     (16)
#define ENLARGE_FACTOR           (2)

enum type {
    KEYWORD = 0,
    IDENTIFIER = 1,
    BIN_OP = 2,
    NUMBER = 3,
};

typedef struct symbol
{
    char* symbol;
    int token_type;
} symbol_st;

struct symbol_table
{
    symbol_st* symbol_array;
    int array_size;
    int table_size;
};

/**
 * @brief initialize the symbol table.
 * @return a valid symbol table object.
 */
symbol_table_st *symbol_table_init()
{
    symbol_table_st *symbol_table = (symbol_table_st *)malloc(sizeof(symbol_table_st));

    symbol_st *symbol_array = (symbol_st *)malloc(sizeof(symbol_st) * DEFAULT_ARRAY_SIZE);

    symbol_table->symbol_array = symbol_array;

    symbol_table->array_size = DEFAULT_ARRAY_SIZE;

    symbol_table->table_size = 0;

    symbol_table_insert(symbol_table, "is", KEYWORD);
    symbol_table_insert(symbol_table, "var", KEYWORD);
    symbol_table_insert(symbol_table, "print", KEYWORD);
    symbol_table_insert(symbol_table, "+", BIN_OP);
    symbol_table_insert(symbol_table, "-", BIN_OP);
    symbol_table_insert(symbol_table, "*", BIN_OP);
    symbol_table_insert(symbol_table, "/", BIN_OP);

    return symbol_table;

}

/**
 * @brief clean up the symbol table.
 * @param symbol_table a valid symbol table object.
 */
void symbol_table_fini(symbol_table_st *symbol_table)
{
    free(symbol_table->symbol_array);
    free(symbol_table);
}

/**
 * @brief look up the symbol on symbol table
 * @param table a valid symbol table object.
 * @param symbol a symbol going to look up.
 * @return -1, not found; otherwise the index in symbol table.
 */
int symbol_table_lookup(symbol_table_st *symbol_table, char *symbol) {

    int index = 0;
    bool found = false;

    if (symbol_table->table_size == 0)
    {return -1;}

    while ((found == false) & (index < symbol_table->table_size)){
        if (strcmp(symbol,symbol_table->symbol_array[index].symbol) == 0) {
            found = true;
            return index;
        } else{
                index++;
            }
    }

    return -1;


}

/**
 * @brief insert the symbol to symbol table
 * @param table a valid symbol table object.
 * @param symbol a symbol going to insert.
 * @param token_val the value of the token.
 * @return -1, failed; otherwise the index inserted in symbol table.
 */
int symbol_table_insert(symbol_table_st *symbol_table, char *symbol, int token_type) {
    if (symbol_table == NULL)
        return -1;

    if (symbol_table_lookup(symbol_table,symbol) == -1) {
        int index = symbol_table->table_size;

        if (symbol_table->table_size >= symbol_table->array_size) {
            symbol_st *new_symbol_array = realloc(symbol_table->symbol_array,
                                                  symbol_table->array_size * ENLARGE_FACTOR);
            if (new_symbol_array == NULL)
                exit(ENOMEM);
            symbol_table->symbol_array = new_symbol_array;
        }

        symbol_table->symbol_array[index].symbol = strdup(symbol);

        symbol_table->symbol_array[index].token_type = token_type;

        symbol_table->table_size++;

        return index;
    }
}

#ifdef XTEST
int main() {

   test_case_one();
    test_case_two();
    test_case_three();

    return 0;
}

int test_case_one() {

    symbol_table_st* table = symbol_table_init();
    printf("Index of + symbol (should return 3): %d\n", symbol_table_lookup(table,"+"));
}

int test_case_two() {

    symbol_table_st* table = symbol_table_init();
    printf("Index of 'for'(should return 1): %d\n", symbol_table_lookup(table,"for"));
}

int test_case_three() {

    symbol_table_st* table = symbol_table_init();
    printf("Table size (should be 7): %d\n",table->table_size);
    symbol_table_insert(table, "var", KEYWORD);
    printf("Table size after attempt to put in 'var' again: %d",table->table_size);
}

#endif
