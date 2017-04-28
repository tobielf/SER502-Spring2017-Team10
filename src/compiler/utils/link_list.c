/**
 * @file link_list.c
 * @brief Purpose: implementation of link_list data structure
 * @version 1.0
 * @date 04.21.2017
 * @author Xiangyu Guo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "error.h"
#include "link_node.h"
#include "link_list.h"

struct link_list {
    link_node_st *head;                 /**< head of the linked list */
    link_node_st *tail;                 /**< tail of the linked list */
};

/**
 * @brief initialize the link list.
 * @return link_list a initialized link list.
 */
link_list_st *link_list_init() {
    link_list_st *list = (link_list_st *)malloc(sizeof(link_list_st));
    if (list == NULL)
        error_errno(ENOMEM);
    list->head = link_node_new(NULL, NULL);
    list->tail = list->head;
    return list;
}

/**
 * @brief free the link list.
 * @param list, a valid list going to release.
 */
void link_list_free(link_list_st *list) {
    if (list != NULL) {
        link_node_remove_all(&(list->head));
        list->tail = NULL;
        free(list);
    }
}

/**
 * @brief pop out one element from the head of the list.
 * @param list, a valid list head.
 * @return NULL on failed, otherwise a valid link node.
 */
link_node_st *link_list_pop(link_list_st *list) {
    link_node_st *top = NULL;
    if (list != NULL) {
        top = link_node_get_next(list->head);
        if (top != NULL) {
            link_node_append(list->head, link_node_get_next(top));
        }
    }

    return top;
}

/**
 * @brief get the top one element from the head of the list.
 * @param list, a valid list head.
 * @return NULL on failed, otherwise a valid link node.
 */
link_node_st *link_list_top(link_list_st *list) {
    link_node_st *top = NULL;
    if (list != NULL) {
        top = link_node_get_next(list->head);
    }

    return top;
}

/**
 * @brief append one element to the end of the list.
 * @param list, a valid list head.
 * @param node, a valid list node.
 * @return NULL on failed, otherwise a cursor point to
 *         the tail of the list.
 */
link_node_st *link_list_append(link_list_st *list, link_node_st *node) {
    if (list != NULL && node != NULL) {
        link_node_append(list->tail, node);
        list->tail = node;
        return list->tail;
    }
    return NULL;
}

/**
 * @brief iterate on the link list and perform the callback on each element
 * @param list, a valid list head.
 * @param call_back, call back function going to perform, can be NULL.
 * @return 1 on success, 0 on stoped.
 */
int link_list_traverse(link_list_st *list, cb_func callback, void *cb_data) {
    link_node_st *work = NULL;
    if (list == NULL || callback == NULL)
        return LINK_LIST_STOP;

    work = link_node_get_next(list->head);
    while (work != NULL) {
        if (callback(work, cb_data) == LINK_LIST_STOP)
            return LINK_LIST_STOP;
        work = link_node_get_next(work);
    }
    return LINK_LIST_CONTINUE;
}

#ifdef LINK_LIST_TEST

int test_print(link_node_st *node, void *data) {
    if (data != NULL) {
        (*((int *)data))++;
    }
    printf("%s\n", (char *)link_node_get_data(node));
    return LINK_LIST_CONTINUE;
}

void test_suite_three() {

    printf("test suite three\n");
    link_list_free(NULL);

    link_list_traverse(NULL, test_print, NULL);

    link_list_pop(NULL);
    printf("test suite three passed!\n");
}

void test_suite_two() {
    link_list_st *list;
    link_node_st *node;
    char *str = NULL;
    int counter = 0;

    printf("test suite two\n");
    list = link_list_init();
    node = link_node_new("hello", NULL);
    link_list_append(list, node);
    node = link_node_new("world", NULL);
    link_list_append(list, node);
    str = strdup("test");
    node = link_node_new(str, free);
    link_list_append(list, node);
    str = strdup("link");
    node = link_node_new(str, free);
    link_list_append(list, node);

    node = link_list_pop(list);
    printf("data in node:%s\n\n", (char *)link_node_get_data(node));
    link_node_free(node);

    link_list_traverse(list, test_print, &counter);
    printf("Count result: %d\n", counter);

    link_list_free(list);
    printf("test suite two passed!\n");
}

void test_suite_one() {
    link_list_st *list;
    link_node_st *node;
    char *str = NULL;
    int counter = 0;

    printf("test suite one\n");
    list = link_list_init();
    node = link_node_new("hello", NULL);
    link_list_append(list, node);
    node = link_node_new("world", NULL);
    link_list_append(list, node);
    str = strdup("test");
    node = link_node_new(str, free);
    link_list_append(list, node);
    str = strdup("link");
    node = link_node_new(str, free);
    link_list_append(list, node);

    link_list_traverse(list, test_print, &counter);
    printf("Count result: %d\n", counter);
    link_list_free(list);
    printf("test suite one passed!\n");
}

int main() {
    test_suite_one();
    test_suite_two();
    test_suite_three();
    return 0;
}

#endif