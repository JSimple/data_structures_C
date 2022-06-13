
// preprocessor macro - basically copies tree.h and puts
// the contents where the include goes
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"
#include "linked_list.h"


int print_tree_hello() {
    printf("hello from tree.c\n");

    return 0;
}

int side_is_full(treenode * node, int side) {
    // right = 1; left = 0
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



int print_node(treenode * node) {
    printf("%i\n", node->val);
    return 0;
}

int print_tree_in_order(treenode * node){
    // if (node == NULL) {
    //     return -1;
    // }
    // print_tree(node->left);
    // printf("%d\n", node->val);
    // print_tree(node->right);
    // //printf("\n");
    // return 0;

    return in_order_map(node, print_node);
}

int in_order_map(treenode * node, int (*f)(treenode * subnode)) {
    if (node == NULL) {
        return -1;
    }
    in_order_map(node->left, f);
    f(node);
    in_order_map(node->right, f);

    return 0;
}

int in_order_map_i(treenode * root, int(*f)(treenode * subnode)) {
    // assert that the size of a pointer to a treenode will not
    // exceed the max size of `int` type
    assert(sizeof(int) == sizeof(void *));
    assert(root != NULL);

    struct treenode *current = root;
    struct node *list = make_node(root);

    while (!is_empty(list)) {
        if (current->right != NULL) {
            (void)add_to_end(list, current->right);
        }

        if (current->left != NULL) {
            current = current->left;
            (void)add_to_end(list, current);
        } else {
            struct node *popped_node = remove_from_end(list);
            f(popped_node);
            // backtracking
        }
    }

    return 0;
}

int pre_order_map(treenode * node, int (*f)(treenode * subnode)) {
    if (node == NULL) {
        return -1;
    }

    f(node);
    pre_order_map(node->left, f);
    pre_order_map(node->right, f);

    return 0;
}

int post_order_map(treenode * node, int (*f)(treenode * subnode)) {
    if (node == NULL) {
        return -1;
    }

    post_order_map(node->left, f);
    post_order_map(node->right, f);
    f(node);

    return 0;
}

int main(int argc, char ** argv) {
    //if (argc > 1) {
    //        printf("argv[1]: %s\n", argv[1]);
    //}

    print_tree_hello();
    treenode root;
    root.val = 4;
    root.left = NULL;
    root.right = NULL;

    insert_sorted(&root, 8);
    insert_sorted(&root, 1);
    insert_sorted(&root, 3);
    insert_sorted(&root, 2);
    insert_sorted(&root, 5);
    insert_sorted(&root, 0);

    // print_tree_in_order(&root);

    printf("testing iterative in order traversal:\n");

    in_order_map_i(&root, print_node);
}

