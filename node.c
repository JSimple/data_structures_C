#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

void print_list();
void append_node();
struct node *make_node();

struct node {
    int value;
    struct node *next;
};


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
    append_node(&node1, 8);
    printf("after appending:\n");
    print_list(node1);
}

void print_list(struct node head) {
    if (head.next == NULL) {
        printf("%i\n", head.value);
    } else {
        printf("%i\n", head.value);
        print_list(*head.next);
    }
}

void append_node(struct node *head, int new_value) {
    if (head->next == NULL) {
        struct node *new_node = make_node(new_value);

        printf("new node value to be inserted: %i\n", new_node->value);

        head->next = new_node;
    } else {
        printf("not there yet...");
        append_node(head->next, new_value);
    }
}

struct node *make_node(int new_value){
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->value = new_value;
    new_node->next = NULL;
    return new_node;
}

// TODO: insert node, prepend node, delete node
