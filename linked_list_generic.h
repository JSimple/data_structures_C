#ifndef __LINKED_LIST_GENERIC_H
#define __LINKED_LIST_GENERIC_H

#include <stdbool.h>

struct node {
    void *value;
    struct node *next;
};

void print_list(struct node*);
struct node *make_node(int);
int delete_node(struct node*);
struct node *remove_node(struct node*, int);
struct node *add_to_beginning(struct node*, int);
struct node *add_to_end(struct node*, int);
struct node *remove_from_beginning(struct node*);
struct node *remove_from_end(struct node*);
struct node *insert_at_index(struct node*, int, int);
bool is_empty(struct node*);

#endif