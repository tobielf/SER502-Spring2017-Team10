/**
 * @file parsing_tree.h
 * @brief Purpose: the node of parsing tree data structure
 * @version 1.0
 * @date 04.15.2017
 * @author Xiangyu Guo
 */
#ifndef __PARSING_TREE_H__
#define __PARSING_TREE_H__

#define TREE_TRAVERSE_CONTINUE  (1)     /**< keep traverse */
#define TREE_TRAVERSE_STOP      (0)     /**< stop traverse */

typedef struct parsing_tree parsing_tree_st;
struct parsing_tree;

typedef void (*free_treenode_cb)(void *);

typedef int (*tree_traversal_cb)(parsing_tree_st *, void *); /**< call back function */

/**
 * @brief create a new parsing tree node.
 * @param data, the data of the tree node.
 * @param free_func, the function to free the data.
 * @return node a valid node.
 */
parsing_tree_st *parsing_tree_new(void *data, free_treenode_cb free_func);

/**
 * @brief free a tree from this node recursively.
 * @param node, a valid tree node.
 */
void parsing_tree_free(parsing_tree_st *);

/**
 * @brief set a sibling to current node.
 * @param root, a valid tree node.
 * @param sibling, a valid sibling node.
 * @return NULL on failed; otherwise the pointer to the sibling.
 */
parsing_tree_st *parsing_tree_set_sibling(parsing_tree_st *, parsing_tree_st *);

/**
 * @brief set a child to current node.
 * @param root, a valid tree node.
 * @param child, a valid child node.
 * @return NULL on failed; otherwise the pointer to the child.
 */
parsing_tree_st *parsing_tree_set_child(parsing_tree_st *, parsing_tree_st *);

/**
 * @brief get a sibling of current node.
 * @param node, a valid node.
 * @return sibling, NULL means no sibling on this node.
 */
parsing_tree_st *parsing_tree_get_sibling(parsing_tree_st *);

/**
 * @brief get a child of current node.
 * @param node, a valid node.
 * @return child, NULL means no child on this node.
 */
parsing_tree_st *parsing_tree_get_child(parsing_tree_st *);

/**
 * @brief get the data stored inside the node
 * @param node, a valid node.
 * @return NULL on failed; otherwise the pointer to the data.
 */
void *parsing_tree_get_data(parsing_tree_st *);

/**
 * @brief traverse the parsing tree in prefix order.
 * @param node, a valid node.
 * @param cb_func, call back function on the node.
 * @param cb_data, data of the call back function.
 * @return 1, on continue; 0, on stopped.
 */
int parsing_tree_prefix_traverse(parsing_tree_st *, tree_traversal_cb, void *);

#endif