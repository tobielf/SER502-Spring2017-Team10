/**
 * @file lexical.h
 * @brief Purpose: Interface for the lexical analysis for the code
 * @version 0.1
 * @date 04.17.2017
 * @author Katie MacArthur
 */

#ifndef __LEXICAL_H__
#define __LEXICAL_H__

#include <stdio.h>

/**
 *@brief takes in symbol table and returns a linked list structure
 * @param symbol_table
 * @return A linked list, NULL is symbol table is NULL
 */
link_list_st lexical_analysis(symbol_table);


