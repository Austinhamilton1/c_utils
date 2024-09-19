#include "list.h"

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

    for(int i = 0; i < 4; i++) {
        int *data = (int *)malloc(sizeof(i));
        memcpy(data, &i, sizeof(i));
        list_prepend(new_list, data, sizeof(i));
        free(data);
    }

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
}