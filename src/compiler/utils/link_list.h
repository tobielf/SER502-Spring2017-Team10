/**
 * @file link_list.h
 * @brief Purpose: link_list data structure
 * @version 1.0
 * @date 04.15.2017
 * @author Xiangyu Guo
 */
#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#include "link_node.h"

#define LINK_LIST_CONTINUE  (1)     /**< keep traverse */
#define LINK_LIST_STOP      (0)     /**< stop traverse */

typedef struct link_list link_list_st;
struct link_list;

typedef int (*cb_func)(link_node_st *); /**< call back function */

/**
 * @brief initialize the link list.
 * @return link_list a initialized link list.
 */
link_list_st *link_list_init();

/**
 * @brief free the link list.
 * @param list, a valid list going to release.
 */
void link_list_free(link_list_st *list);

/**
 * @brief pop out one element from the head of the list.
 * @param list, a valid list head.
 * @return NULL on failed, otherwise a valid link node.
 */
link_node_st *link_list_pop(link_list_st *);

/**
 * @brief append one element to the end of the list.
 * @param list, a valid list head.
 * @param node, a valid list node.
 * @return NULL on failed, otherwise a cursor point to
 *         the tail of the list.
 */
link_node_st *link_list_append(link_list_st *, link_node_st *);

/**
 * @brief iterate on the link list and perform the callback on each element
 * @param list, a valid list head.
 * @param call_back, call back function going to perform, can be NULL.
 * @return 1 on success, 0 on stoped.
 */
int link_list_traverse(link_list_st *, cb_func callback);

#endif