/**
 * @file coding-style.c
 * @brief Purpose: declearation of APIs
 * @version 0.1
 * @date 04.15.2017
 * @author Your Name
 */
#ifndef __CODING_STYLE_H__
#define __CODING_STYLE_H__

typedef struct details hiding_details_st;
struct details;

/**
 * @brief get an instance(object) of coding-style.
 * @return a valid object
 */
hiding_details_st *coding_style_get_instance();

/**
 * @brief clean up the instance.
 */
void coding_style_clean_up();

/**
 * @brief fruits API for outter programs.
 * @param fruits_shop a valid object.
 * @param bar the fruits id.
 * @return NULL on invalid param, otherwise the fruit name
 */
char *get_a_fruit(hiding_details_st *fruits_shop, int bar);

#endif