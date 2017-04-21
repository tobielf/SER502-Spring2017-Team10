/**
 * @file link_node.h
 * @brief Purpose: link_node data structure
 * @version 0.1
 * @date 04.15.2017
 * @author Xiangyu Guo
 */
#ifndef __LINK_NODE_H__
#define __LINK_NODE_H__

typedef struct link_node link_node_st;
struct link_node;

typedef void (*free_cb)(void *);

/**
 * @brief creating a new node
 * @param data, data of the node.
 * @param free_func, the function to free the data.
 * @return node, a valid node.
 */
link_node_st *link_node_new(void *data, free_cb free_func );

/**
 * @brief free a node
 * @param node, a valid node going to free.
 */
void link_node_free(link_node_st *);

/**
 * @brief get the data from a node.
 * @param node, a valid node.
 * @return NULL on failed; otherwise the pointer to the data.
 */
void *link_node_get_data(link_node_st *);

/**
 * @brief append one node after the other.
 * @param node_prev, the previous node.
 * @param node_next, the next node.
 * @return cursor, the latter one as cursor.
 */
link_node_st *link_node_append(link_node_st *, link_node_st *);

#endif