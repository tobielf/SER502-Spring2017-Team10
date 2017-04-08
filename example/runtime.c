/**
 * @file runtime.c
 * @brief a simple runtime environment based on stack machine model
 * @author Xiangyu Guo
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE  (999)       /**< Default size of the machine */

int operands_stack[STACK_SIZE]; /**< The stack of the machine */
int operands_index = 0;         /**< The position of the stack */

/**
 * @brief A simple implementation of stack machine.
 */
int main() {
    char input[255];
    int i;
    while (fgets(input, 255, stdin) != NULL) {
        if (isdigit(input[0])) {
            operands_stack[operands_index++] = atoi(input);
        } else {
            int right = 0;
            int left = 0;
            int result = 0;
            right = operands_stack[--operands_index];
            left = operands_stack[--operands_index];
            switch (input[0]) {
                case '+':
                    result = left + right;
                    operands_stack[operands_index++] = result;
                break;
                case '-':
                    result = left - right;
                    operands_stack[operands_index++] = result;
                break;
                case '*':
                    result = left * right;
                    operands_stack[operands_index++] = result;
                break;
                case 'D':
                case '/':
                    result = left / right;
                    operands_stack[operands_index++] = result;
                break;
                case 'M':
                    result = left % right;
                    operands_stack[operands_index++] = result;
                break;
            }
        }
    }
    for (i = 0; i < operands_index; i++) {
        printf("%d\n", operands_stack[i]);
    }
    return 0;
}