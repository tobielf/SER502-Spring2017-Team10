/**
 * @file parser.h
 * @brief Purpose: generate a parsing tree using token list and symbol table 
 * @version 0.1
 * @date 04.18.2017
 * @author Ximing
 */

#ifndef __PARSER_H__
#define __PARSER_H__

#include "parser.c"
#include "/utils/parsing_tree.h"
#include "/utils/symbol_table.h"
#include "/utils/link_list.h"



/**
* @brief: get the token_list and symbol_table parse it into a parsing tree 
* @arg: pointers to token_list and symbol table
* @return: the pointer to generated parsing tree
*/
parsing_tree_st *parse_tree = syntax_analysis(token_list, symbol_table);

#endif