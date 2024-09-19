#include "list.h"

#include <stdlib.h>
#include <string.h>

list *list_init() {
    //allocate list
    list *new_list = (list *) malloc(sizeof(list));
    
    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
}

list_node *list_node_init(void *data, size_t size) {
    //allocate list node
    list_node *new_list_node = (list_node *) malloc(sizeof(list_node));
    
    //initialize list node
    new_list_node->next = NULL;
    new_list_node->prev = NULL;
    new_list_node->data = (data_packet *)malloc(sizeof(data_packet));
    new_list_node->data->size = size;
    new_list_node->data->value = malloc(size);
    memcpy(new_list_node->data->value, data, size);

    return new_list_node;
}

int list_node_free(list_node *list_node_to_free) {
    //if the list node is null, indicate failure to free
    if(list_node_to_free == NULL)
        return -1;

    //free the list node and its data
    if(list_node_to_free->data != NULL) {
        if(list_node_to_free->data->value != NULL)
            free(list_node_to_free->data->value);
        free(list_node_to_free->data);
    }
    free(list_node_to_free);

    return 0;
}

int list_free(list *list_to_free) {
    //if the list is null, indicate failure to free
    if(list_to_free == NULL)
        return -1;

    //if one of the list nodes can't be freed, this will signify there was an error
    int result = 0;

    //if the list has data in it, free all the data
    if(list_to_free->head != NULL) {
        list_node *list_node_to_free = list_to_free->head;
        while(list_node_to_free != NULL) {
            list_node *tmp = list_node_to_free->next;
            result = list_node_free(list_node_to_free);
            if(result < 0)
                break;
            list_node_to_free = tmp;
        }
    }

    //free the list
    free(list_to_free);

    return result;
}

int64_t list_length(list *list) {
    //if the list is null, indicate failure
    if(list == NULL)
        return -1;

    //empty list
    if(list->head == NULL)
        return 0;

    //count how many items are in the list
    int64_t loop_counter = 0;
    list_node *ptr = list->head;
    while(ptr != NULL) {
        loop_counter++;
        ptr = ptr->next;
    }

    return loop_counter;
}

int list_append(list *list_to_append_to, void *data, size_t size) {
    //if the list is null, indicate a failure
    if(list_to_append_to == NULL)
        return -1;

    //allocate new list node
    list_node *list_node_to_append = list_node_init(data, size);

    //if the new list node is null, indicate failure
    if(list_node_to_append == NULL)
        return -1;

    if(list_to_append_to->tail == NULL) {
        //empty list
        list_to_append_to->head = list_node_to_append;
        list_to_append_to->tail = list_node_to_append;
    }
    else {
        //add the node to the end of the list
        list_node *tail = list_to_append_to->tail;
        tail->next = list_node_to_append;
        list_node_to_append->prev = tail;
        list_to_append_to->tail = list_node_to_append;
    }

    return 0;
}

int list_prepend(list *list_to_prepend_to, void *data, size_t size) {
    //if the list is null, indicate a failure
    if(list_to_prepend_to == NULL)
        return -1;

    //allocate new list node
    list_node *list_node_to_prepend = list_node_init(data, size);

    //if the new list node is null, indicate failure
    if(list_node_to_prepend == NULL)
        return -1;

    if(list_to_prepend_to->head == NULL) {
        //empty list
        list_to_prepend_to->head = list_node_to_prepend;
        list_to_prepend_to->tail = list_node_to_prepend;
    }
    else {
        //add the new list node to the beginning of the list
        list_node *head = list_to_prepend_to->head;
        head->prev = list_node_to_prepend;
        list_node_to_prepend->next = head;
        list_to_prepend_to->head = list_node_to_prepend;
    }

    return 0;
}

int list_insert(list *list_to_insert_to, int64_t index, void *data, size_t size) {
    //if the list is null, indicate a failure
    if(list_to_insert_to == NULL)
        return -1;

    //indicate index out of bounds error
    int64_t length = list_length(list_to_insert_to);
    if(index >= length || index < -length)
        return -1;

    //allocate new list node
    list_node *list_node_to_insert = list_node_init(data, size);

    //if the new list node is null, indicate failure
    if(list_node_to_insert == NULL)
        return -1;

    int64_t loop_counter;
    list_node *ptr;
    if(index < 0) {
        loop_counter = -1;
        ptr = list_to_insert_to->tail;

        //traverse to insertion point
        while(loop_counter > index) {
            ptr = ptr->prev;
            loop_counter--;
        }

        if(ptr->next == NULL) {
            //if inserting at tail, update list
            list_to_insert_to->tail = list_node_to_insert;
            ptr->next = list_node_to_insert;
            list_node_to_insert->prev = ptr;
        }
        else {
            //insert list node into list
            list_node *next = ptr->next;
            next->prev = list_node_to_insert;
            ptr->next = list_node_to_insert;
            list_node_to_insert->prev = ptr;
            list_node_to_insert->next = next;
        }
    }
    else {
        loop_counter = 0;
        ptr = list_to_insert_to->head;

        //traverse to insertion point
        while(loop_counter < index) {
            ptr = ptr->next;
            loop_counter++;
        }

        if(ptr->prev == NULL) {
            //if inserting at head, update list
            list_to_insert_to->head = list_node_to_insert;
            ptr->prev = list_node_to_insert;
            list_node_to_insert->next = ptr;
        }
        else {
            //insert list node into list
            list_node *prev = ptr->prev;
            prev->next = list_node_to_insert;
            ptr->prev = list_node_to_insert;
            list_node_to_insert->prev = prev;
            list_node_to_insert->next = ptr;
        }
    }

    return 0;
}

int list_remove(list* list_to_remove_from, int64_t index) {
    //if the list is null, indicate failure
    if(list_to_remove_from == NULL)
        return -1;
    
    //check for index out of bounds error
    int64_t length = list_length(list_to_remove_from);
    if(index >= length || index < -length)
        return -1;

    int64_t loop_counter;
    list_node *ptr;
    if(index < 0) {
        loop_counter = -1;
        ptr = list_to_remove_from->tail;

        //traverse to deletion point
        while(loop_counter > index) {
            ptr = ptr->prev;
            loop_counter--;
        }
    }
    else {
        loop_counter = 0;
        ptr = list_to_remove_from->head;

        //traverse to deletion point
        while(loop_counter < index) {
            ptr = ptr->next;
            loop_counter++;
        }        
    }
    if(ptr->prev == NULL) {
        //if deleting the first item, update head
        list_node *next = ptr->next;
        next->prev = NULL;
        list_to_remove_from->head = next;
        list_node_free(ptr);
    }
    else if(ptr->next == NULL) {
        //if deleting the last item, update tail
        list_node *prev = ptr->prev;
        prev->next = NULL;
        list_to_remove_from->tail = prev;
        list_node_free(ptr);
    }
    else {
        //remove the list node
        list_node *prev = ptr->prev;
        list_node *next = ptr->next;
        prev->next = next;
        next->prev = prev;
        list_node_free(ptr);
    }

    return 0;
}

int list_get(list *list_to_get_from, int64_t index, void *target) {
    //if the list is null, indicate failure
    if(list_to_get_from == NULL)
        return -1;
    
    //check for index out of bounds error
    int64_t length = list_length(list_to_get_from);
    if(index >= length || index < -length)
        return -1;

    int64_t loop_counter;
    list_node *ptr;
    if(index < 0) {
        loop_counter = -1;
        ptr = list_to_get_from->tail;

        //traverse to selection point
        while(loop_counter > index) {
            ptr = ptr->prev;
            loop_counter--;
        }
    }
    else {
        loop_counter = 0;
        ptr = list_to_get_from->head;

        //traverse to selection point
        while(loop_counter < index) {
            ptr = ptr->next;
            loop_counter++;
        }
    }

    //copy over data
    memcpy(target, ptr->data->value, ptr->data->size);

    return 0;
}

int swap(list *list, list_node *a, list_node *b) {
    //if the list or either node is null, exit the function
    if(list == NULL || a == NULL || b == NULL)
        return -1;

    list_node *a_prev = a->prev;
    list_node *a_next = a->next;
    list_node *b_prev = b->prev;
    list_node *b_next = b->next;

    if(a_prev == NULL && b_next == NULL) {
        //a is original head, b is original tail
        list->tail = a;
        list->head = b;
        a->prev = b_prev;
        b_prev->next = a;
        a->next = NULL;
        b->next = a_next;
        a_next->prev = b;
        b->prev = NULL;
    }
    else if(a_next == NULL && b_prev == NULL) {
        //a is original tail, b is original head
        list->head = a;
        list->tail = b;
        a->next = b_next;
        b_next->prev = a;
        a->prev = NULL;
        b->prev = a_prev;
        a_prev->next = b;
        b->next = NULL;
    }
    else if(a_prev == NULL) {
        //a is original head, b is generic
        list->head = b;
        a->prev = b_prev;
        b_prev->next = a;
        a->next = b_next;
        b_next->prev = a;
        b->next = a_next;
        a_next->prev = b;
        b->prev = NULL;
    }
    else if(a_next == NULL) {
        //a is original tail, b is generic
        list->tail = b;
        a->next = b_next;
        b_next->prev = a;
        a->prev = b_prev;
        b_prev->next = a;
        b->prev = a_prev;
        a_prev->next = b;
        b->next = NULL;
    }
    else if(b_prev == NULL) {
        //a is generic, b is original head
        list->head = a;
        b->prev = a_prev;
        a_prev->next = b;
        b->next = a_next;
        a_next->prev = b;
        a->next = b_next;
        b_next->prev = a;
        a->prev = NULL;
    }
    else if(b_next == NULL) {
        //a is generic, b is original tail
        list->tail = a;
        b->next = a_next;
        a_next->prev = b;
        b->prev = a_prev;
        a_prev->next = b;
        a->prev = b_prev;
        b_prev->next = a;
        a->next = NULL;
    }
    else {
        //generic case
        a->prev = b_prev;
        b_prev->next = a;
        a->next = b_next;
        b_next->prev = a;
        b->prev = a_prev;
        a_prev->next = b;
        b->next = a_next;
        a_next->prev = b;
    }

    return 0;
}

list *list_slice(list *list_to_slice, int64_t start_index, int64_t end_index) {
    //if list is null, or slice would be null, return null
    if(list_to_slice == NULL || end_index == 0)
        return NULL;

    int64_t length = list_length(list_to_slice);
    //check for index out of bounds error
    if(start_index >= length || start_index < -length || end_index > length || end_index < -length)
        return NULL;
    
    int64_t slice_length;
    if((start_index * end_index) > 0) {
        //same sign indexing
        if(start_index >= end_index)
            return NULL;
        slice_length = end_index - start_index;
    }
    else if((start_index * end_index) < 0) {
        //different sign indexing
        if(start_index <= length + end_index)
            return NULL;
        slice_length = length + end_index - start_index;
    }
    else if(end_index < 0) 
        //slice from 0 to negative
        slice_length = length + end_index - start_index;
    else
        //slice from 0 to positive
        slice_length = end_index - start_index;
    
    int64_t loop_counter;
    list_node *ptr;
    if(start_index < 0) {
        loop_counter = -1;
        ptr = list_to_slice->tail;

        //traverse to starting slice point
        while(loop_counter > start_index) {
            ptr = ptr->prev;
            loop_counter--;
        }
    }
    else {
        loop_counter = 0;
        ptr = list_to_slice->head;

        //traverse to starting slice point
        while(loop_counter < start_index) {
            ptr = ptr->next;
            loop_counter++;
        }
    }

    loop_counter = 0;
    list *slice_list = list_init();
    while(loop_counter < slice_length) {
        list_append(slice_list, ptr->data->value, ptr->data->size);
        ptr = ptr->next;
        loop_counter++;
    }

    return slice_list;
}

static list *merge(list *a, list *b, int compare(void *, void *)) {
    //initialize merged list
    list *new_list = list_init();

    list_node *a_ptr = a->head;
    list_node *b_ptr = b->head;

    //merge lists
    while(a_ptr != NULL && b_ptr != NULL) {
        int comparison = compare(a_ptr->data->value, b_ptr->data->value);
        if(comparison < 0) {
            //a_ptr should come first
            list_append(new_list, a_ptr->data->value, a_ptr->data->size);
            a_ptr = a_ptr->next;
        }
        else {
            //b_ptr should come first
            list_append(new_list, b_ptr->data->value, b_ptr->data->size);
            b_ptr = b_ptr->next;
        }
    }

    //add the rest of a if needed
    while(a_ptr != NULL) {
        list_append(new_list, a_ptr->data->value, a_ptr->data->size);
        a_ptr = a_ptr->next;
    }

    //add the rest of b if needed
    while(b_ptr != NULL) {
        list_append(new_list, b_ptr->data->value, b_ptr->data->size);
        b_ptr = b_ptr->next;
    }

    return new_list;
}

list *list_sort(list *list_to_sort, int compare(void *, void *)) {
    //get length for recursive step
    int64_t length = list_length(list_to_sort);
    if(length <= 1)
        return list_to_sort;

    int64_t middle = length / 2;

    //split list in half
    list *a = list_slice(list_to_sort, 0, middle);
    list *b = list_slice(list_to_sort, middle, length);

    //sort halves
    list *a_sorted = list_sort(a, compare);
    list *b_sorted = list_sort(b, compare);

    //merge sorted halves
    list *sorted_list = merge(a_sorted, b_sorted, compare);
    
    //clean up allocated lists
    list_free(a);
    list_free(b);

    return sorted_list;
}

void list_apply(list *list_to_apply, void function(void *)) {
    //if the list is null or empty, do nothing
    if(list_to_apply == NULL || list_to_apply->head == NULL) 
        return;

    //apply function to each data point
    list_node *ptr = list_to_apply->head;
    while(ptr != NULL) {
        function(ptr->data->value);
        ptr = ptr->next;
    }
}

list *list_map(list *list_to_map, data_packet function(void *)) {
    //if the list is null or empty, do nothing
    if(list_to_map == NULL || list_to_map->head == NULL)
        return NULL;

    list *mapped_list = list_init();

    //apply function to each data point and put the result in 
    //the new list
    list_node *ptr = list_to_map->head;
    while(ptr != NULL) {
        data_packet data = function(ptr->data->value);
        list_append(mapped_list, data.value, data.size);
        ptr = ptr->next;
    }

    return mapped_list;
}

list *list_filter(list *list_to_filter, int function(void *)) {
    //if the list is null or empty, do nothing
    if(list_to_filter == NULL || list_to_filter->head == NULL)
        return NULL;

    list *filtered_list = list_init();

    //apply function to each data point and if the result is >0
    //copy the data point over
    list_node *ptr = list_to_filter->head;
    while(ptr != NULL) {
        int result = function(ptr->data->value);
        if(result > 0)
            list_append(filtered_list, ptr->data->value, ptr->data->size);
        ptr = ptr->next;
    }

    return filtered_list;
}

void list_reduce(list *list_to_reduce, void *target, data_packet function(void *, void *)) {
    //if the list is null or empty, do nothing
    if(list_to_reduce == NULL || list_to_reduce->head == NULL)
        return;

    //apply the function to target and each data point in turn
    //store the results in target
    list_node *ptr = list_to_reduce->head;
    while(ptr != NULL) {
        data_packet data = function(target, ptr->data->value);
        memcpy(target, data.value, data.size);
        ptr = ptr->next;
    }    
}