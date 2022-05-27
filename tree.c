
// preprocessor macro - basically copies tree.h and puts
// the contents where the include goes
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"


int print_tree_hello() {
    printf("hello from tree.c\n");

    return 0;
}

int side_is_empty(treenode * node, int side) {
    if (node == NULL) {
        // Given invalid node to check, this is error
        return -1;
    }

    int rv = 0;

    if (side == 0) {
        if (node->left == NULL) {
            rv = 1;
        }
    } else if (side == 1) {
        if (node->right == NULL) {
            rv = 1;
        }
    } else {
        rv = -1; // error condition
    }
    return rv;
}

// treat side like a bool
//
treenode * insert_node(int val, int side, treenode * node) {
    if (node == NULL) {
        return NULL;
    }
    if (side_is_empty(node, side) == 0){
        // Dont overwrite node
        fprintf(stderr, "error (insert-node): side is not empty\n");
        return NULL;
    }

    treenode * new_node = malloc(sizeof(treenode));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->val = val;

    if (side == 0) {
        // left side
        node->left = new_node;
    } else if (side == 1) {
        // right side
        node->right = new_node;
    } else {
        // error
        free(new_node);
        return NULL;
    }
    return new_node;
}

int print_node(treenode * node){
    if (node == NULL) {
        return -1;
    }
    printf("%d\n", node->val);
    printf("  ");
    print_node(node->left);
    print_node(node->right);
    printf("\n");
    return 0;
}


int main(int argc, char ** argv) {
    //if (argc > 1) {
    //        printf("argv[1]: %s\n", argv[1]);
    //}

    print_tree_hello();
    treenode root;
    root.val = 0;
    root.left = NULL;
    root.right = NULL;
    insert_node(42, 0, &root);
    insert_node(43, 0, &root); // this should give an error
    print_node(&root);
}
