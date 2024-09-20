#ifndef STACK_i
#define STACK_H

#include "types.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
	data_packet *data;
	uint64_t top;
	uint64_t size;
	uint64_t capacity;
} stack;

/*
 * Allocate a stack in memory
 * Parameters:
 *     initial_capacity: the starting capacity of the stack
 * Returns:
 *     The newly allocated stack
 */
stack *stack_init(uint64_t initial_capacity);

/*
 * Free up a stack from memory
 * Parameters:
 *     stack_to_free: pointer to a stack
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int stack_free(stack *stack_to_free);

/*
 * Pushes an element to the top of the stack
 * Parameters:
 *     stack_to_push: pointer to a stack
 *     value: the data to add
 *     size: should be sizeof(value)
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int stack_push(stack *stack_to_push, void *value, size_t size);

/*
 * Pops an element from the top of the stack
 * Parameters:
 *     stack_to_pop: pointer to a stack
 *     target: copy the top of the stack to target
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int stack_pop(stack *stack_to_pop, void *target);

/*
 * Peeks the top element of the stack
 * Parameters:
 *     stack_to_peek: pointer to a stack
 *     target: copy the top of the stack to target
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int stack_peek(stack *stack_to_peek, void *target);

#endif
