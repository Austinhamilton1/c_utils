#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdint.h>

/*
 * Holds any data
 */
typedef struct {
    void *value;
    size_t size;
} data_packet;

/*
 * Doubly linked list node
 */
typedef struct list_node {
    struct list_node *next;
    struct list_node *prev;
    data_packet *data;
} list_node;

/*
 * Doubly linked list
 */
typedef struct {
    list_node *head;
    list_node *tail;
} list;

/*
 * Allocate an empty list
 * Returns: 
 *     a pointer to the allocated list
 */
list *list_init();

/*
 * Free a list from memory
 * Parameters:
 *     list_to_free: pointer to a list
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int list_free(list *list_to_free);

/*
 * Allocate a list node with data
 * Parameters:
 *     data: the data to be stored in the list node (can be anything)
 *     size: should be sizeof(data)
 * Returns:
 *     a pointer to the allocated node
 */
list_node *list_node_init(void *data, size_t size);

/*
 * Free a list node from memory
 * Parameters:
 *     list_node_to_free: pointer to a list node
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int list_node_free(list_node *list_node_to_free);

/*
 * Calculate the length of a list
 * Parameters:
 *     list: pointer to a list
 * Returns:
 *     The length of the list
 *     -1 if the list is null
 */
int64_t list_length(list *list);

/*
 * Append a list node to the end of a list
 * Parameters:
 *     list_to_append_to: pointer to a list
 *     data: the data to put in the node
 *     size: should be sizeof(data)
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int list_append(list *list_to_append_to, void *data, size_t size);

/*
 * Prepend a list node to the beginning of a list
 * Parameters:
 *     list_to_prepend_to: pointer to a list
 *     data: the data to put in the node
 *     size: should be sizeof(data)
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int list_prepend(list *list_to_prepend_to, void *data, size_t size);

/*
 * Insert a list node into a certain index of a list
 * Parameters:
 *     list_to_insert_to: pointer to a list
 *     index: the index to insert into (0 based, negative indexing supported)
 *     data: the data to put in the node
 *     size: should be sizeof(data)
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int list_insert(list *list_to_insert_to, int64_t index, void *data, size_t size);

/*
 * Remove a list node at a certain index of a list
 * Parameters:
 *     list_to_remove_from: pointer to a list
 *     index: the index to remove from (0 based, negative indexing supported)
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int list_remove(list *list_to_remove_from, int64_t index);

/*
 * Get the data stored in the list node at a certain index
 * Parameters:
 *     list_to_get_from: pointer to a list
 *     index: the index to get (0 based, negative indexing supported)
 *     target: pointer to copy the data to
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int list_get(list *list_to_get_from, int64_t index, void *target);

/*
 * Slice a list from a start index (inclusive) to an end index (exclusive)
 * Parameters:
 *     list_to_slice: pointer to a list
 *     start_index: index to start from (0 based, negative indexing supported)
 *     end_index: index to end at (0 based, negative indexing supported)
 * Returns:
 *     A pointer to a copy of the sliced list
 */
list *list_slice(list *list_to_slice, int64_t start_index, int64_t end_endex);

/*
 * Swaps two items in a list
 * Parameters:
 *     list_to_swap_in: pointer to a list
 *     a: pointer to first list node
 *     b: pointer to second list node
 * Returns:
 *     0 on success
 *     -1 on failure
 */
int swap(list *list_to_swap_in, list_node *a, list_node *b);

/*
 * Sorts a list in place based on the compare function
 * Parameters:
 *     list_to_sort: pointer to a list
 *     compare: a function that returns negative values if a < b, positive values if a > b and 0
 *              if they are equal
 * Returns:
 *     0 on success
 *     -1 on failure
 */
list *list_sort(list *list_to_sort, int compare(void *, void *));

/*
 * Apply a function to every item in the list
 * Paramters:
 *     list_to_apply: pointer to list
 *     function: function to apply to list, should take in a void * and return nothing
 */
void list_apply(list *list_to_apply, void function(void *));

/*
 * Map every item in a list to a new item in a new list after applying some function to it
 * Parameters:
 *     list_to_map: pointer to list
 *     function: function to map to new list, should take in a void * and return a mapped data packet
 *               value
 * Returns:
 *     The new list
 */
list *list_map(list *list_to_map, data_packet function(void *));

/*
 * Filter a map down based on a function
 * Parameters:
 *     list_to_filter: a pointer to a list
 *     function: function to filter based on, should take in a void * and return >0 for membership
 *               and <=0 for non-membership
 * Returns:
 *     The filtered list
 */
list *list_filter(list *list_to_filter, int function(void *));

/*
 * Reduce a list down to a single value based on a function
 * Parameters:
 *     list_to_reduce: a pointer to a list
 *     target: a void * that will be the first input to the function and the final output of the 
 *             function
 *     function: function to reduce based on, should take in two void * and return a new data packet
 *               that represents those two values reduced into one value
 * Returns:
 *     A single reduced value
 */
void list_reduce(list *list_to_reduce, void *target, data_packet function(void *, void *));

#endif