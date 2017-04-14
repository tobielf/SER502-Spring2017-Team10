/**
 * @file coding-style.c
 * @brief Purpose: demonstrate the coding style
 * @version 0.1
 * @date 04.08.2017
 * @author Your Name
 */
#include <stdio.h>
#include <stdlib.h>

#include "foo.h"
#include "symbol.h"
#include "coding-style.h"

    /* Indent using 4 spaces */

#define     MAGIC_NUMBER    (4)         /**< magic! */
#define     MAGIC_SIZE      (3)         /**< size!  */

struct details
{
    int data;
    int you;
    int are;
    int trying_to_hide;
};

const char *g_fruits_table[MAGIC_SIZE] = 
                                    {NULL, "banana", "apple"};    /**< fruits */

int g_for_global_variables = 0;          /**< global variable is dangerous! */

static hiding_details_st *g_instance = NULL;

/**
 * @brief foo a fruits
 * @param bar which one?
 * @return fruit_name the name of fruit.
 */
static char *s_foo(int bar);

/**
 * @brief get an instance(object) of coding-style.
 * @return a valid object
 */
hiding_details_st *coding_style_get_instance() {
    if (g_instance == NULL) {
        g_instance = (hiding_details_st *)malloc(sizeof(hiding_details_st));
    }
    return g_instance;
}

/**
 * @brief clean up the instance.
 */
void coding_style_clean_up() {
    if (g_instance != NULL) {
        /* release other resources */
        /* then free, in free function it will set g_instance = NULL */
        free(g_instance);
    }
}

/**
 * @brief fruits API for outter programs.
 * @param fruits_shop a valid object.
 * @param bar the fruits id.
 * @return NULL on invalid param, otherwise the fruit name
 */
char *get_a_fruit(hiding_details_st *fruits_shop, int bar)
{
    if (fruits_shop == NULL)
        return NULL;

    // coding style of "if" statement.
    if (bar < 0 || bar >= MAGIC_SIZE)
        bar = 0;

    return s_foo(bar);
}

static char *s_foo(int bar)
{
    int unix_style_identifier = 0;
    int i = 0;

    // coding style of "for" loop.
    for (i = 0; i < MAGIC_NUMBER; i++) {
        unix_style_identifier++;
    }

    // coding style of "switch" statement.
    switch (bar) {
        case 0:
            g_started_for_global_variables = -1;
            break;
        case 1:  // fall through
        case 2:
            g_started_for_global_variables = bar;
            break;
        default:
            g_started_for_global_variables = 0;
            break;
    }

    // coding style of "while" loop.
    while (g_started_for_global_variables >= 0) {
        unix_style_identifier++;
        g_started_for_global_variables--;
    }

    return g_fruits_table[bar];
}
