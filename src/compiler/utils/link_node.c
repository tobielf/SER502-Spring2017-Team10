/**
 * @file link_node.c
 * @brief Purpose: implementation of link_node data structure
 * @version 1.0
 * @date 04.19.2017
 * @author Xiangyu Guo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "error.h"
#include "link_node.h"

struct link_node
{
    void *data;                     /**< Data inside the node */
    free_cb free_func;              /**< Call back function on free */
    link_node_st *next;             /**< Pointer to the next node */
};

/**
 * @brief creating a new node
 * @param data, data of the node.
 * @param free_func, the function to free the data.
 * @return node, a valid node.
 */
link_node_st *link_node_new(void *data, free_cb free_func ) {
    link_node_st *node = (link_node_st *)malloc(sizeof(link_node_st));
    if (node == NULL)
        error_errno(ENOMEM);

    node->data = data;
    node->free_func = free_func;
    node->next = NULL;
    return node;
}

/**
 * @brief free a node
 * @param node, a valid node going to free.
 */
void link_node_free(link_node_st *node) {
    if (node != NULL) {
        if (node->free_func != NULL && 
            node->data != NULL) {
            node->free_func(node->data);
        }
        node->next = NULL;
        free(node);
    }
}

/**
 * @brief get the data from a node.
 * @param node, a valid node.
 * @return NULL on failed; otherwise the pointer to the data.
 */
void *link_node_get_data(link_node_st *node) {
    if (node != NULL) {
        return node->data;
    }
    return NULL;
}

/**
 * @brief append one node after the other.
 * @param node_prev, the previous node.
 * @param node_next, the next node.
 * @return cursor, the latter one as cursor.
 */
link_node_st *link_node_append(link_node_st *node_prev, link_node_st *node_next) {
    if (node_prev == NULL)
        return NULL;

    node_prev->next = node_next;

    return node_next;
}

/**
 * @brief get next node after current node.
 * @param current_node, a valid node object.
 * @return next_node, next node of current node, otherwise NULL.
 */
link_node_st *link_node_get_next(link_node_st *node) {
    if (node == NULL)
        return NULL;

    return node->next;
}

/**
 * @brief remove all node start from current node.
 * @param head current node as head.
 */
void link_node_remove_all(link_node_st **head) {
    while (*head) {
        link_node_st *next = (*head)->next;
        link_node_free(*head);
        *head = next;
    }
}

#ifdef LINK_NODE_TEST

void test_suite_three() {
    link_node_st *node1 = NULL;
    link_node_st *node2 = NULL;
    char *str = NULL;

    printf("Test suite three\n");
    str = strdup("hello");
    node1 = link_node_new(str, free);

    str = strdup("world");
    node2 = link_node_new(str, free);
    link_node_append(node1, node2);
    link_node_remove_all(&node1);
    printf("Test suite three passed!\n");
}

void test_suite_two() {
    link_node_st *node1 = NULL;
    char *str = NULL;

    printf("Test suite two\n");
    str = strdup("test");
    node1 = link_node_new(str, free);

    str = link_node_get_data(node1);
    if (strcmp(str, "test") == 0) {
        printf("EQUAL\n");
    } else {
        printf("NOT EQUAL!\n");
    }
    link_node_free(node1);
    printf("Test suite two passed!\n");
}

void test_suite_one() {
    link_node_st *node1 = NULL;
    char *str = NULL;

    printf("Test suite one\n");
    str = strdup("test");
    node1 = link_node_new(str, free);
    link_node_free(node1);
    
    node1 = link_node_new("test", NULL);
    link_node_free(node1);

    node1 = link_node_new(NULL, free);
    link_node_free(node1);
    
    node1 = link_node_new(NULL, NULL);
    link_node_free(node1);
    printf("Test suite one passed!\n");
}

int main() {
    test_suite_one();
    test_suite_two();
    test_suite_three();
    return 0;
}

#endif