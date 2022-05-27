#ifndef TREE_H_
#define TREE_H_

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
treenode * insert_node(int val, int side, treenode * node);


int print_tree_hello ();
#endif // TREE_H_
