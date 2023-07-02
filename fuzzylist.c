#include <stdio.h>
#include <stdlib.h>
#include "fuzzylist.h"
#include "fuzzytypes.h"

Node* __head_node; // head node
Node* __pointer_node; 
boolean node_created;

void fuzzy_list_node_new(Node* node){
    if(!node){
        printf("error: unable to create a new node\n");
        return;
    }
    __head_node = node;
    node_created = true;
}

void fuzzy_list_node_add(Node* head, void* data){
    if(data == NULL){
        printf("error: a null value cannot be provided\n");
        return;
    }

    if(node_created){
        __head_node->n_data = data;
        __pointer_node = __head_node;
        __pointer_node->n_next = NULL;
        node_created = false;
        return;
    }
    // allocate a new space for the new node
    Node* newNode = fuzzy_node_malloc(sizeof(Node));
    if(!newNode){
        printf("error: unable to create a new node\n");
        return;
    }

    /*
    Node* tmp = head;
    while(tmp){
        if(tmp->n_next == NULL)
            break;

        tmp = tmp->n_next;
    }
    */

    newNode->n_data = data;
    //__pointer_node = tmp;
    __pointer_node->n_next = newNode;
    __pointer_node = newNode;
}

u64 fuzzy_list_node_length(Node* head){
    if(!head)
        return 0;

    u64 len = 0;
    while(head->n_next!=NULL){
        len++;
        head = head->n_next;
    }

    return len;
}

void* fuzzy_list_node_get(Node* head, u64 i){
    Node* channel;
    u64 iter;

    if(head == NULL){
        printf("given head is null\n");
        return NULL;
    }

    if(i < 0){
        printf("index is not supported\n");
        return NULL;
    }

    iter = 0;
    channel = head;
    while(iter < i && channel->n_next != NULL){
        iter++;
        channel = channel->n_next;
    }

    if(iter != i)
        return NULL;

    return channel->n_data;
}

void fuzzy_list_node_clear(Node* head){
    if(!head){
        printf("given head is null cannot clean data\n");
        return;
    }

    // because first node is on the stack
    // i am interested in the next node
    // and its because its allocated by malloc function
    // so that free function can be applied on it
    Node* first_node = head;
    Node* tmp = first_node;
    while(first_node != NULL){
        tmp = first_node->n_next;
        fuzzy_node_free(first_node);
        first_node = tmp;
    }
    head = NULL;
}


