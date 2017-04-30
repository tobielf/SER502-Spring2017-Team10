/**
 * @file symboltable.c
 * @brief purpose: to initialize and edit symbol table
 * @version 1.0
 * @date 04.23.2017
 * @author Katie MacArthur
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "error.h"
#include "symbol_table.h"

#define DEFAULT_ARRAY_SIZE      (16)
#define ENLARGE_FACTOR          (2)

typedef struct symbol
{
    char* symbol;               /**< token string */
    int token_type;             /**< token type   */
} symbol_st;

struct symbol_table
{
    symbol_st* symbol_array;    /**< symbol_array struct */
    int array_size;             /**< array size          */
    int table_size;             /**< table size          */
};

/**
 * @brief initialize the symbol table.
 * @return a valid symbol table object.
 */
symbol_table_st *symbol_table_init()
{
    symbol_table_st *symbol_table = (symbol_table_st *)malloc(sizeof(symbol_table_st));
    if (symbol_table == NULL)
        error_errno(ENOMEM);

    symbol_st *symbol_array = (symbol_st *)malloc(sizeof(symbol_st) * DEFAULT_ARRAY_SIZE);
    if (symbol_array == NULL)
        error_errno(ENOMEM);

    symbol_table->symbol_array = symbol_array;

    symbol_table->array_size = DEFAULT_ARRAY_SIZE;

    symbol_table->table_size = 0;

    //delimiter
    symbol_table_insert(symbol_table, ";", DELIMITER);

    //keywords
    symbol_table_insert(symbol_table, "is", KEYWORD);
    symbol_table_insert(symbol_table, "var", KEYWORD);
    symbol_table_insert(symbol_table, "print", KEYWORD);
    symbol_table_insert(symbol_table, "if", KEYWORD);
    symbol_table_insert(symbol_table, "then", KEYWORD);
    symbol_table_insert(symbol_table, "else", KEYWORD);
    symbol_table_insert(symbol_table, "for", KEYWORD);
    symbol_table_insert(symbol_table, "from", KEYWORD);
    symbol_table_insert(symbol_table, "to", KEYWORD);
    symbol_table_insert(symbol_table, "step", KEYWORD);

    //binary operations
    symbol_table_insert(symbol_table, "+", BIN_OP);
    symbol_table_insert(symbol_table, "-", BIN_OP);
    symbol_table_insert(symbol_table, "*", BIN_OP);
    symbol_table_insert(symbol_table, "/", BIN_OP);
    symbol_table_insert(symbol_table, "%", BIN_OP);

    //boolean operations
    symbol_table_insert(symbol_table, "=", BOOLEAN_OP);
    symbol_table_insert(symbol_table, "<>", BOOLEAN_OP);
    symbol_table_insert(symbol_table, "<", BOOLEAN_OP);
    symbol_table_insert(symbol_table, ">", BOOLEAN_OP);
    symbol_table_insert(symbol_table, "<=", BOOLEAN_OP);
    symbol_table_insert(symbol_table, ">=", BOOLEAN_OP);

    //parentheses
    symbol_table_insert(symbol_table, "(", OPEN_PARENTHESES);
    symbol_table_insert(symbol_table, ")", CLOSE_PARENTHESES);

    //curly brackets
    symbol_table_insert(symbol_table, "{", OPEN_CURLY_BRACKETS);
    symbol_table_insert(symbol_table, "}", CLOSE_CURLY_BRACKETS);
    return symbol_table;

}

/**
 * @brief clean up the symbol table.
 * @param symbol_table a valid symbol table object.
 */
void symbol_table_fini(symbol_table_st *symbol_table)
{
    if (symbol_table == NULL)
        return;

    int i;
    for (i = 0; i < symbol_table->table_size; i++) {
        free(symbol_table->symbol_array[i].symbol);
    }

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

    if (symbol_table == NULL || symbol == NULL)
        return -1;

    if (symbol_table->table_size == 0)
        return -1;

    int index = 0;
    while (index < symbol_table->table_size) {
        if (strcmp(symbol,symbol_table->symbol_array[index].symbol) == 0) {
            return symbol_table->symbol_array[index].token_type;
        } else {
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
    int index = -1;
 
    if (symbol_table == NULL)
        return -1;

    if ((index = symbol_table_lookup(symbol_table,symbol)) == -1) {
        index = symbol_table->table_size;

        if (symbol_table->table_size >= symbol_table->array_size) {
            symbol_table->symbol_array = realloc(symbol_table->symbol_array,
                                                  sizeof(symbol_st) * symbol_table->array_size * ENLARGE_FACTOR);
            if (symbol_table->symbol_array == NULL)
                exit(ENOMEM);

            symbol_table->array_size *= ENLARGE_FACTOR;
        }

        symbol_table->symbol_array[index].symbol = strdup(symbol);

        symbol_table->symbol_array[index].token_type = token_type;

        symbol_table->table_size++;
    }

    return index;
}

#ifdef SYMBOL_TABLE_TEST

void test_case_one();
void test_case_two();
void test_case_three();

int main() {

    test_case_one();
    test_case_two();
    test_case_three();

    return 0;
}

void test_case_one() {

    symbol_table_st* table = symbol_table_init();
    printf("Index of + symbol (should return 2): %d\n", symbol_table_lookup(table,"+"));
    symbol_table_fini(table);
}

void test_case_two() {

    symbol_table_st* table = symbol_table_init();
    printf("Index of 'the'(should return -1): %d\n", symbol_table_lookup(table,"the"));
    symbol_table_fini(table);
}

void test_case_three() {

    symbol_table_st* table = symbol_table_init();
    printf("Table size (should be 26): %d\n",table->table_size);
    symbol_table_insert(table, "var", KEYWORD);
    printf("Table size after attempt to put in 'var' again: %d\n",table->table_size);
    symbol_table_fini(table);
}

#endif
