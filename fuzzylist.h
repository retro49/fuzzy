#include <stdio.h>
#include <stdlib.h>
#include "fuzzytypes.h"

#ifndef FUZZYLIST
#define FUZZYLIST
typedef struct {
    void* n_data;
    void* n_next;
}Node;

void fuzzy_list_node_new(Node*); // done
void fuzzy_list_node_add(Node*, void*); // done

void* fuzzy_list_node_get(Node*, u64); // done
void fuzzy_list_node_clear(Node*); // done

u64 fuzzy_list_node_length(Node*); // done
#endif

