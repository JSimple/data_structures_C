// node has:
// value
// pointer to next node (where it's stored?)

#include <stdio.h>

#define FALSE 0
#define TRUE 1

void print_list();
void append_node();

struct node {
    int value;
    struct node *next;
};

// struct node printValue(struct node *self){
//     printf(self.value);
// }

int main() {
    struct node node1;
    node1.value = 5;

    struct node node2;
    node2.value = 6;

    node1.next = &node2;

    struct node node3;
    node3.value = 7;
    node3.next = NULL;

    node2.next = &node3;

    printf("before appending:\n");
    print_list(node1);
    putchar('\n');
    append_node(node1, 8);
    printf("after appending:\n");
    print_list(node1);
}

// for next time:
// figure out how to print next val directly
// implement LL methods

void print_list(struct node head) {
    if (head.next == NULL) {
        printf("%i\n", head.value);
    } else {
        printf("%i\n", head.value);
        print_list(*head.next);
    }
}

// LEFT OFF HERE.
// this function doesn't seem to be appending our new node to the actual list
void append_node(struct node head, int new_value) {
    if (head.next == NULL) {
        printf("found the end!\n");
        struct node new_node;
        new_node.value = new_value;
        new_node.next = NULL;

        printf("new node value to be inserted: %i\n", new_node.value);

        head.next = &new_node;
    } else {
        printf("not there yet...");
        append_node(*head.next, new_value);
    }
}

// TODO: set next node function
