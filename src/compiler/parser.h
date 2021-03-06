/**
 * @file parser.h
 * @brief Purpose: generate a parsing tree using token list and symbol table 
 * @version 1.0
 * @date 04.18.2017
 * @author Ximing
 */

#ifndef __PARSER_H__
#define __PARSER_H__


#include "utils/parsing_tree.h"
#include "utils/symbol_table.h"
#include "utils/link_list.h"




/**
 * @brief: get the token_list and symbol_table parse it into a parsing tree 
 * @param: pointer to token list 
 * @param: pointer to symbol table
 * @return: the pointer to generated parsing tree
 */
parsing_tree_st *syntax_analysis (link_list_st *token_list, symbol_table_st *symbol_table);

#endif
