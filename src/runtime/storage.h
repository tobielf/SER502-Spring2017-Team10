/**
 * @file storage.h
 * @brief Purpose: declaration of the machine storage.
 * @version 0.9
 * @date 04.23.2017
 * @author Xiangyu Guo
 */
#ifndef __STORAGE_H__
#define __STORAGE_H__

#define MEMORY_CURRENT_SCOPE        (0)             /**< Search on current scope */
#define MEMORY_ALL_SCOPE            (-1)            /**< Search on all scope */

typedef struct memory memory_st;
struct memory;

typedef struct machine_memory machine_memory_st;
struct machine_memory;

/**
 * @brief initialize the machine memory.
 * @return machine_store a valid machine_store.
 */
machine_memory_st *machine_memory_init();

/**
 * @brief clean up the machine memory, release all resources.
 * @param machine_store a valid machine storage object.
 */
void machine_memory_fini(machine_memory_st *);

/**
 * @brief get a variable from the storage.
 * @param machine_store a valid machine_store.
 * @param variable_name variable name.
 * @param scope 0 for current scope, -1 for all scope.
 * @return NULL on failed or doesn't exist; otherwise a pointer to variable_memory.
 */
memory_st* machine_memory_get_variable(machine_memory_st *, char *, int);

/**
 * @brief set a variable to the storage.
 * @param machine_store a valid machine_store.
 * @param variable_name variable name.
 * @param variable_value variable value.
 * @param scope 0 for current scope, -1 for all scope.
 * @return 0 on success, otherwise failed.
 */
int machine_memory_set_variable(machine_memory_st *, char *, int, int);

/**
 * @brief open a new scope on the machine memory
 * @param machine_store a valid machine_store.
 */
void machine_memory_open_scope(machine_memory_st *);

/**
 * @brief close current scope on the machine memory, will release all variables.
 * @param machine_store a valid machine_store.
 */
void machine_memory_close_scope(machine_memory_st *);

/**
 * @brief get a value from memory object.
 * @param variable_memory a valid memory object.
 * @return the value inside the memory object.
 */
int memory_get_value(memory_st *);

/**
 * @brief set a value to memory object.
 * @param variable_memory a valid memory object.
 * @param variable_value a new value.
 */
void memory_set_value(memory_st *, int);

#endif