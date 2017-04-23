/**
 * @file parsing_tree.c
 * @brief Purpose: implementation of the parsing tree node data structure
 * @version 1.0
 * @date 04.21.2017
 * @author Xiangyu Guo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "error.h"
#include "parsing_tree.h"

struct parsing_tree
{
    void *data;
    free_treenode_cb free_func;
    parsing_tree_st *child;
    parsing_tree_st *sibling;
};

/**
 * @brief create a new parsing tree node.
 * @param data, the data of the tree node.
 * @param free_func, the function to free the data.
 * @return node a valid node.
 */
parsing_tree_st *parsing_tree_new(void *data, free_treenode_cb free_func) {
    parsing_tree_st *root = (parsing_tree_st *)malloc(sizeof(parsing_tree_st));
    if (root == NULL)
        error_errno(ENOMEM);

    root->data = data;
    root->free_func = free_func;

    root->child = NULL;
    root->sibling = NULL;

    return root;
}

/**
 * @brief free a tree from this node recursively.
 * @param node, a valid tree node.
 */
void parsing_tree_free(parsing_tree_st *tree_root) {
    parsing_tree_st *child = NULL;
    parsing_tree_st *sibling = NULL;
    if (tree_root != NULL) {
        if (tree_root->data != NULL && tree_root->free_func != NULL) {
            tree_root->free_func(tree_root->data);
        }
        child = tree_root->child;
        sibling = tree_root->sibling;
        tree_root->child = NULL;
        tree_root->sibling = NULL;
        free(tree_root);
        parsing_tree_free(child);
        parsing_tree_free(sibling);
    }
}

/**
 * @brief set a sibling to current node.
 * @param root, a valid tree node.
 * @param sibling, a valid sibling node.
 * @return NULL on failed; otherwise the pointer to the sibling.
 */
parsing_tree_st *parsing_tree_set_sibling(parsing_tree_st *tree_root,
                                          parsing_tree_st *sibling) {
    if (tree_root == NULL || sibling == NULL)
        return NULL;
    tree_root->sibling = sibling;
    return sibling;
}

/**
 * @brief set a child to current node.
 * @param root, a valid tree node.
 * @param child, a valid child node.
 * @return NULL on failed; otherwise the pointer to the child.
 */
parsing_tree_st *parsing_tree_set_child(parsing_tree_st *tree_root,
                                        parsing_tree_st *child) {
    if (tree_root == NULL || child == NULL)
        return NULL;
    tree_root->child = child;
    return child;
}

/**
 * @brief get a sibling of current node.
 * @param node, a valid node.
 * @return sibling, NULL means no sibling on this node.
 */
parsing_tree_st *parsing_tree_get_sibling(parsing_tree_st *tree_root) {
    if (tree_root == NULL)
        return NULL;
    return tree_root->sibling;
}

/**
 * @brief get a child of current node.
 * @param node, a valid node.
 * @return child, NULL means no child on this node.
 */
parsing_tree_st *parsing_tree_get_child(parsing_tree_st *tree_root) {
    if (tree_root == NULL)
        return NULL;
    return tree_root->child;
}

/**
 * @brief get the data stored inside the node
 * @param node, a valid node.
 * @return NULL on failed; otherwise the pointer to the data.
 */
void *parsing_tree_get_data(parsing_tree_st *tree_root) {
    if (tree_root == NULL)
        return NULL;
    return tree_root->data;
}

/**
 * @brief traverse the parsing tree in prefix order.
 * @param node, a valid node.
 * @param cb_func, call back function on the node.
 * @param cb_data, data of the call back function.
 * @return 1, on continue; 0, on stopped.
 */
int parsing_tree_prefix_traverse(parsing_tree_st *tree_root,
                                tree_traversal_cb cb_func, 
                                void *cb_data) {
    if (tree_root == NULL)
        return TREE_TRAVERSE_CONTINUE;

    if (cb_func != NULL) {
        if (cb_func(tree_root, cb_data) == TREE_TRAVERSE_STOP) {
            return TREE_TRAVERSE_STOP;
        }
    }

    if (parsing_tree_prefix_traverse(tree_root->child, cb_func, cb_data) == TREE_TRAVERSE_STOP)
        return TREE_TRAVERSE_STOP;

    if (parsing_tree_prefix_traverse(tree_root->sibling, cb_func, cb_data) == TREE_TRAVERSE_STOP)
        return TREE_TRAVERSE_STOP;

    return TREE_TRAVERSE_CONTINUE;
}

#ifdef PARSING_TREE_TEST

int test_print_cb(parsing_tree_st *tree_node, void *cb_data) {
    if (cb_data != NULL) {
        (*((int *)cb_data))++;
    }
    printf("%s\n", (char *)parsing_tree_get_data(tree_node));
    return TREE_TRAVERSE_CONTINUE;
}

void test_suite_two() {
    int counter = 0;
    char *str = NULL;

    printf("test suite two\n");
    parsing_tree_st *root = parsing_tree_new("program", NULL);
    parsing_tree_st *node1 = parsing_tree_new("stmt_list", NULL);
    str = strdup("stmt");
    parsing_tree_st *node2 = parsing_tree_new(str, free);
    parsing_tree_set_child(root, node1);
    parsing_tree_set_child(node1, node2);
    node1 = node2;
    node2 = parsing_tree_new(";", NULL);
    parsing_tree_set_sibling(node1, node2);
    str = strdup("decl_stmt");
    node2 = parsing_tree_new(str, free);
    parsing_tree_set_child(node1, node2);
    node1 = node2;
    node2 = parsing_tree_new("var", NULL);
    parsing_tree_set_child(node1, node2);
    node1 = node2;
    node2 = parsing_tree_new("i", NULL);
    parsing_tree_set_sibling(node1, node2);

    parsing_tree_prefix_traverse(root, test_print_cb, &counter);
    printf("Total nodes: %d\n", counter);
    parsing_tree_free(root);
    printf("test suite two passed!\n");
}

void test_suite_one() {
    int counter = 0;
    printf("test suite one\n");

    parsing_tree_st *root = parsing_tree_new("program", NULL);
    parsing_tree_st *node1 = parsing_tree_new("stmt_list", NULL);
    parsing_tree_st *node2 = parsing_tree_new("stmt", NULL);
    parsing_tree_set_child(root, node1);
    parsing_tree_set_child(node1, node2);
    node1 = node2;
    node2 = parsing_tree_new(";", NULL);
    parsing_tree_set_sibling(node1, node2);
    node2 = parsing_tree_new("decl_stmt", NULL);
    parsing_tree_set_child(node1, node2);
    node1 = node2;
    node2 = parsing_tree_new("var", NULL);
    parsing_tree_set_child(node1, node2);
    node1 = node2;
    node2 = parsing_tree_new("i", NULL);
    parsing_tree_set_sibling(node1, node2);

    parsing_tree_prefix_traverse(root, test_print_cb, &counter);
    printf("Total nodes: %d\n", counter);
    parsing_tree_free(root);
    printf("test suite one passed!\n");
}

int main() {
    test_suite_one();
    test_suite_two();
    return 0;
}
#endif
