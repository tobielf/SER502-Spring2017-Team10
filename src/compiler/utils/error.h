/**
 * @file error.h
 * @brief dealing with compiler error
 * @version 1.0
 * @date 04.21.2017
 * @author Xiangyu Guo
 */

/**
 * @brief print out the error message to stderr and exit the program
 * @param lineno line number
 * @param msg error message
 */
void error_msg(int, char *);

/**
 * @brief print out the error message to stderr and exit the program
 * @param error_number error number
 */
void error_errno(int);