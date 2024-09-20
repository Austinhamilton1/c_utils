#include "list.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(void *a, void *b) {
    return *((int *)a) - *((int *)b);
}

void print_node(void *value) {
    int int_value = *((int *)value);
    printf("%d <-> ", int_value);
}

data_packet square(void *value) {
    int int_value = (*(int *)value) * (*(int *)value);
    size_t size = sizeof(int_value);
    data_packet data = {&int_value, size};
    return data;
}

int is_even(void *value) {
    int int_value = *((int *)value);
    return int_value % 2 == 0;
}

data_packet add(void *a, void *b) {
    int a_value = (*(int *)a);
    int b_value = (*(int *)b);
    int result = a_value + b_value;
    size_t size = sizeof(a_value);
    data_packet data = {&result, size};
    return data;
}

void print_list(list *list) {
    printf("START <-> ");
    list_apply(list, print_node);
    printf("END\n");
}

int main(int argc, char *argv[]) {
    list *new_list = list_init();

    for(int i = 0; i < 4; i++) 
        list_prepend(new_list, &i, sizeof(i));

    print_list(new_list);

    list *sorted_list = list_sort(new_list, compare);
    print_list(sorted_list);

    list *squared_list = list_map(sorted_list, square);
    print_list(squared_list);

    list *even_list = list_filter(sorted_list, is_even);
    print_list(even_list);

    int sum = 0;
    list_reduce(squared_list, &sum, add);
    printf("Sum of squares: %d\n", sum);

    list_free(new_list);
    list_free(sorted_list);
    list_free(squared_list);
    list_free(even_list);

	stack *new_stack = stack_init(4);

	for(int i = 0; i < 16; i++)
		stack_push(new_stack, &i, sizeof(i));
	
	int current;
	while(new_stack->size > 0) {
		stack_pop(new_stack, &current);
		printf("%d\n", current);
	}

	char buf[7] = {'A', 'u', 's', 't', 'i', 'n', 0};
	for(char *ptr = buf; *ptr != 0; ptr++) 
		stack_push(new_stack, ptr, sizeof(char));

	char current_char;
	
	stack_peek(new_stack, &current_char);
	printf("Top of stack: ");
	putchar(current_char);

	printf("Reversed string: ");
	while(new_stack->size > 0) {
		stack_pop(new_stack, &current_char);
		putchar(current_char);
	}
	printf("\n");

	stack_free(new_stack);
}
