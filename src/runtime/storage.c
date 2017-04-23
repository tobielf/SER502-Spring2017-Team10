/**
 * @file storage.h
 * @brief Purpose: implementation of the machine storage.
 * @version 0.5
 * @date 04.23.2017
 * @author Xiangyu Guo
 */
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "storage.h"

#define STATIC_MEMORY_SIZE      (32)                /**< memory size of the virtual machine */
#define SCOPE_BOUNDRAY_SIZE     (4)                 /**< array size of the scope boundray */
#define RESIZE_FACTOR           (2)                 /**< resize factor when memory size is too small */

struct memory
{
    char *variable_name;                            /**< the name of a variable */
    int variable_value;                             /**< the value of a variable */
    int scope;                                      /**< the scope of the variable */
};

struct machine_memory
{
    int allocated_address;                          /**< usage of static memory */
    int memory_size;                                /**< size of static memroy */
    memory_st *static_memory;                       /**< static memory */
};

static int s_scope = 0;                             /**< the scope of variable */

static int *s_scope_boundary = NULL;                /**< indicate the scope range */

/**
 * @brief initialize the machine memory.
 * @return machine_store a valid machine_store.
 */
machine_memory_st *machine_memory_init() {
    machine_memory_st *machine_store;

    machine_store = (machine_memory_st *)malloc(sizeof(machine_memory_st));
    if (machine_store == NULL)
        exit(ENOMEM);

    s_scope_boundary = (int *)malloc(SCOPE_BOUNDRAY_SIZE);
    if (s_scope_boundary == NULL)
        exit(ENOMEM);

    machine_store->allocated_address = 0;
    machine_store->static_memory = (memory_st *)malloc(STATIC_MEMORY_SIZE *
                                                            sizeof(memory_st));

    if (machine_store->static_memory == NULL)
        exit(ENOMEM);

    machine_store->memory_size = STATIC_MEMORY_SIZE;

    memset(machine_store->static_memory, 0, 
            sizeof(STATIC_MEMORY_SIZE * sizeof(memory_st)));

    return machine_store;
}

/**
 * @brief clean up the machine memory, release all resources.
 */
void machine_memory_fini(machine_memory_st *machine_store) {
    int i;
    if (machine_store != NULL) {
        for (i = 0; i < machine_store->allocated_address; i++) {
            free(machine_store->static_memory[i].variable_name);
        }

        free(machine_store->static_memory);
        free(machine_store);
    }
}

/**
 * @brief get a variable from the storage.
 * @param machine_store a valid machine_store.
 * @param variable_name variable name.
 * @param scope 0 for current scope, -1 for all scope.
 * @return NULL on failed or doesn't exist; otherwise a pointer to variable_memory.
 */
memory_st* machine_memory_get_variable(machine_memory_st *machine_store,
                                        char *variable_name, int scope) {
    // todo: scope related work.
    memory_st *variable_memory = NULL;
    int index = 0;

    if (machine_store == NULL || variable_name == NULL)
        return NULL;

    index = machine_store->allocated_address - 1;
    for ( ; index >= 0; index--) {
        variable_memory = &(machine_store->static_memory[index]);
        if (strcmp(variable_memory->variable_name, variable_name) == 0)
            return variable_memory;
    }

    return NULL;
}

/**
 * @brief set a variable to the storage.
 * @param machine_store a valid machine_store.
 * @param variable_name variable name.
 * @param variable_value variable value.
 * @param scope 0 for current scope, -1 for all scope.
 * @return 0 on success, otherwise failed.
 */
int machine_memory_set_variable(machine_memory_st *machine_store, 
                                char *variable_name, int value, int scope) {
    memory_st *static_memory;
    int index = 0;
    // todo: scope related work.
    if (machine_store == NULL)
        return EINVAL;
    index = machine_store->allocated_address;

    if (index >= machine_store->memory_size) {
        machine_store->static_memory = realloc(machine_store->static_memory, 
                                               machine_store->memory_size * 
                                               RESIZE_FACTOR);
    
        if (machine_store->static_memory == NULL) {
            exit(ENOMEM);
        }

        machine_store->memory_size *= RESIZE_FACTOR;
    }

    static_memory = &(machine_store->static_memory[index]);
    static_memory->variable_name = strdup(variable_name);
    static_memory->variable_value = value;
    static_memory->scope = scope;
    machine_store->allocated_address++;

    return 0;
}

/**
 * @brief get a value from memory object.
 * @param variable_memory a valid memory object.
 * @return the value inside the memory object.
 */
int memory_get_value(memory_st *variable) {
    if (variable == NULL)
        exit(EINVAL);

    return variable->variable_value;
}

/**
 * @brief set a value to memory object.
 * @param variable_memory a valid memory object.
 * @param variable_value a new value.
 */
void memory_set_value(memory_st *variable, int value) {
    if (variable == NULL)
        exit(EINVAL);

    variable->variable_value = value;
}