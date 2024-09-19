#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>

/*
 * Holds any data
 */
typedef struct {
    void *value;
    size_t size;
} data_packet;

#endif