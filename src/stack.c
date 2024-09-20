#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

stack *stack_init(uint64_t initial_capacity) {
	//allocate the stack
	stack *new_stack = (stack *)malloc(sizeof(stack));
	
	//initialize the stack
	new_stack->top = -1;
	new_stack->size = 0;
	new_stack->capacity = initial_capacity;
	new_stack->data = (data_packet *)malloc(initial_capacity * sizeof(data_packet));

	return new_stack;
}

int stack_free(stack *stack_to_free) {
	//if the stack is null, indicate a failure
	if(stack_to_free == NULL)
		return -1;

	//if the stack has data in it, free all the data
	if(stack_to_free->data != NULL) {
		for(uint64_t i = 0; i < stack_to_free->capacity; i++) {
			if(stack_to_free->data[i].value != NULL)
				free(stack_to_free->data[i].value);
		}
		free(stack_to_free->data);
	}

	free(stack_to_free);

	return 0;
}

int stack_push(stack *stack_to_push, void *value, size_t size) {
	//if the stack is null, indicate a failure
	if(stack_to_push == NULL)
		return -1;
	
	//if the stack has reached capacity, we need to reallocate
	if(stack_to_push->size == stack_to_push->capacity) {
		uint64_t new_capacity = 2 * stack_to_push->capacity;
		stack_to_push->data = (data_packet *)realloc(stack_to_push->data, new_capacity * sizeof(data_packet));
		stack_to_push->capacity = new_capacity;
	}

	stack_to_push->top += 1;
	uint64_t top = stack_to_push->top;
	stack_to_push->data[top].value = malloc(size);
	stack_to_push->data[top].size = size;
	memcpy(stack_to_push->data[top].value, value, size);
	stack_to_push->size += 1;

	return 0;
}

int stack_pop(stack *stack_to_pop, void *target) {
	//if the stack is null or empty, indicate failure
	if(stack_to_pop == NULL || stack_to_pop->size == 0)
		return -1;

	//copy the data from the top of the stack to target 
	uint64_t top = stack_to_pop->top;
	void *value = stack_to_pop->data[top].value;
	size_t size = stack_to_pop->data[top].size;
	memcpy(target, value, size);

	//decrement the top of the stack
	stack_to_pop->top -= 1;
	stack_to_pop->size -= 1;

	return 0;
}

int stack_peek(stack *stack_to_peek, void *target) {
	//if the stack is null or empty, indicate failure
	if(stack_to_peek == NULL || stack_to_peek->size == 0)
		return -1;

	//copy the data from the top of the stack to target
	uint64_t top = stack_to_peek->top;
	void *value = stack_to_peek->data[top].value;
	size_t size = stack_to_peek->data[top].size;
	memcpy(target, value, size);

	return 0;
}
