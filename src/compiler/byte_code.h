/**
 * @file byte_code.h
 * @brief Purpose: byte code operation
 * @version 1.0
 * @date 04.18.2017
 * @author Rundong Zhu
 */

#ifndef __BYTE_CODE_H__
#define __BYTE_CODE_H__

#include "utils/link_list.h"
#include "utils/symbol_table.h"
#include "utils/parsing_tree.h"

#include "utils/error.h"

/**
 * @brief generate byte code form parsing tree and symbol table.
 * @param node, a valid tree node.
 * @param table, a valid symbol table object
 * @return NULL on failed, otherwise a valid link list.
 */
link_list_st *semantic_analysis(parsing_tree_st *, symbol_table_st *);

#endif