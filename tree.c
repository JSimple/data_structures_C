
// preprocessor macro - basically copies tree.h and puts
// the contents where the include goes
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"


int print_tree_hello() {
    printf("hello from tree.c\n");

    return 0;
}

int side_is_full(treenode * node, int side) {
    if (node == NULL) {
        // Given invalid node to check, this is error
        return -1;
    }

    int rv = 1;

    if (side == 0) {
        if (node->left == NULL) {
            rv = 0;
        }
    } else if (side == 1) {
        if (node->right == NULL) {
            rv = 0;
        }
    } else {
        rv = -1; // error condition
    }
    return rv;
}

// treat side like a bool
//
treenode * insert_node(treenode * node, int val, int side) {
    if (node == NULL) {
        return NULL;
    }
    if (side_is_full(node, side) == 1){
        // Dont overwrite node
        fprintf(stderr, "error (insert-node): side is already full\n");
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

treenode * create_node(int val){
        treenode * new_node = malloc(sizeof(treenode));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->val = val;
        return new_node;
}

treenode * insert_sorted(struct treenode * root,int val){
    //left -> smaller
    //right -> greater or equal
    if (root == NULL){
        printf("New tree created");
        return create_node(val);
    }
    if (val < root->val){
        if (root->left == NULL){
            treenode * new_node = create_node(val);
            root->left = new_node;
            return new_node;
        }
        return insert_sorted(root->left, val);
    }
    else{
        if (root->right == NULL){
            treenode * new_node = create_node(val);
            root->right = new_node;
            return new_node;
        }
        return insert_sorted(root->right, val);
    }
    return NULL;
}


int print_tree(treenode * node){
    if (node == NULL) {
        return -1;
    }
    print_tree(node->left);
    printf("%d\n", node->val);
    print_tree(node->right);
    //printf("\n");
    return 0;
}

int print_asci_tree(treenode * root){
    int l_depth = 0;
    int r_depth = 0;
    
/*

number of spaces to the left of node is proportional to left child depth
   6
  /\
 4  7
 /\ /\
3 5 6 10
       \
       12
        \
        14
*/  

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
    
    insert_sorted(&root, 8);
    insert_sorted(&root, 1);
    insert_sorted(&root, 3);
    insert_sorted(&root, 2);
    insert_sorted(&root, 5);
    insert_sorted(&root, 1);

    print_tree(&root);
}
