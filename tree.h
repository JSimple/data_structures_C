#ifndef __TREE_H_
#define __TREE_H_

#include "linked_list_generic.h"

typedef struct treenode treenode;

// void * and type_indicator value - for multiple possible value types

// NULL = empty node
struct treenode {
 int val;
 treenode * left;
 treenode * right;
};

typedef struct tree tree;
struct tree {
    treenode * root;
};

// inserts a node and returns pointer to newly added node
treenode * insert_node(treenode*, int val, int side);
treenode * insert_sorted(treenode *root, int val);
int side_is_full(treenode *node, int side);
int print_node(treenode *node);
int print_tree_in_order(treenode *node);
int print_tree_hello ();
int in_order_map(treenode *node, int (*f)(treenode *));
int in_order_map_i(treenode *node, int (*f)(treenode *));
int pre_order_map(treenode *node, int (*f)(treenode *));
int post_order_map(treenode *node, int (*f)(treenode *));
#endif // __TREE_H_
