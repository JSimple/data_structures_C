#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

void print_list();
void append_node();
struct node *prepend_node();
struct node *make_node();

struct node {
    int value;
    struct node *next;
};

/* struct linked_list { */
/*     struct node *head; */
/* }; */

int main() {
    struct node *node1 = make_node(5);

    /* struct linked_list ll; */
    /* ll.head = &node1; */

    append_node(node1, 6);
    append_node(node1, 7);
    append_node(node1, 8);



    printf("after appending:\n");
    print_list(*node1);

    printf("prepending a node...\n");

    struct node *new_head = prepend_node(node1, 4);

    printf("after prepending:\n");
    print_list(*new_head);
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

// returns pointer to new node so we are able to test it in main()
struct node *prepend_node(struct node *head, int new_value) {
    struct node *new_node = make_node(new_value);
    new_node->next = head;
    return new_node;
}

struct node *make_node(int new_value){
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->value = new_value;
    new_node->next = NULL;
    return new_node;
}

// TODO: insert node, prepend node, delete node
