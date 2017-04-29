/**
 * @file storage.c
 * @brief Purpose: implementation of the machine storage.
 * @version 1.0
 * @date 04.23.2017
 * @author Xiangyu Guo
 */
#include <stdio.h>
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
    int current_scope;                              /**< the scope of variable */
    int *scope_boundary;                            /**< indicate the scope range */
    int scope_capacity;                             /**< capacity of scope_boundary */
    memory_st *static_memory;                       /**< static memory */
};      

/**
 * @brief initialize the machine memory.
 * @return machine_store a valid machine_store.
 */
machine_memory_st *machine_memory_init() {
    machine_memory_st *machine_store;

    machine_store = (machine_memory_st *)malloc(sizeof(machine_memory_st));
    if (machine_store == NULL)
        exit(ENOMEM);

    machine_store->scope_boundary = (int *)malloc(SCOPE_BOUNDRAY_SIZE * sizeof(int));
    if (machine_store->scope_boundary == NULL)
        exit(ENOMEM);

    machine_store->scope_capacity = SCOPE_BOUNDRAY_SIZE;
    machine_store->current_scope = 0;
    machine_store->scope_boundary[0] = 0;

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
 * @param machine_store a valid machine storage object.
 */
void machine_memory_fini(machine_memory_st *machine_store) {
    int i;
    if (machine_store != NULL) {
        for (i = 0; i < machine_store->allocated_address; i++) {
            free(machine_store->static_memory[i].variable_name);
        }

        free(machine_store->static_memory);
        free(machine_store->scope_boundary);
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
    memory_st *variable_memory = NULL;
    int index = 0;
    int boundry = 0;

    if (machine_store == NULL || variable_name == NULL)
        return NULL;

    index = machine_store->allocated_address - 1;

    // check scope range
    if (scope == MEMORY_CURRENT_SCOPE) {
        boundry = machine_store->scope_boundary[machine_store->current_scope];
    }

    for ( ; index >= boundry; index--) {
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

    if (machine_store == NULL || variable_name == NULL)
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
    static_memory->scope = machine_store->current_scope;
    machine_store->allocated_address++;

    return 0;
}

/**
 * @brief open a new scope on the machine memory
 * @param machine_store a valid machine_store.
 */
void machine_memory_open_scope(machine_memory_st *machine_store) {
    if (machine_store == NULL)
        return;

    machine_store->current_scope++;
#ifdef DEBUG
    fprintf(stderr, "scope: %d\n", machine_store->current_scope);
#endif
    if (machine_store->current_scope >= machine_store->scope_capacity) {
        machine_store->scope_boundary = (int *)realloc(machine_store->scope_boundary, 
                                                machine_store->scope_capacity * 
                                                RESIZE_FACTOR * sizeof(int));

        if (machine_store->scope_boundary == NULL)
            exit(ENOMEM);

        machine_store->scope_capacity *= RESIZE_FACTOR;
    }

    machine_store->scope_boundary[machine_store->current_scope] = machine_store->allocated_address;
}

/**
 * @brief close current scope on the machine memory, will release all variables.
 * @param machine_store a valid machine_store.
 */
void machine_memory_close_scope(machine_memory_st *machine_store) {
    int index;
    int boundary = 0;
    memory_st *static_memory;

    if (machine_store == NULL)
        return;

    boundary = machine_store->scope_boundary[machine_store->current_scope];

    // release all variables on this(active) scope.
    for (index = boundary; index < machine_store->allocated_address; index++) {
        static_memory = &(machine_store->static_memory[index]);
        if (static_memory->scope != machine_store->current_scope) {
            fprintf(stderr, "Dirty data in scope %d\n", machine_store->current_scope);
            exit(EINVAL);
        }
#ifdef DEBUG
        fprintf(stderr, "Releasing: %s, value: %d\n",
                                    static_memory->variable_name,
                                    static_memory->variable_value);
#endif
        free(static_memory->variable_name);
    }

    machine_store->allocated_address = boundary;

    machine_store->scope_boundary[machine_store->current_scope] = 0;

    machine_store->current_scope--;
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