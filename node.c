#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

void print_list(struct node);
struct node *push_end_node(struct node*, int);
struct node *push_node(struct node*, int);
struct node *make_node(int);
struct node *insert_node(struct node*, int, int);
int delete_node(struct node*);

/* struct linked_list { */
/*     struct node *head; */
/* }; */

int main() {
    struct node *node1 = make_node(5);
    delete_node(node1);
    printf("%i", node1->value);
    struct node *node2 = make_node(6);
    append_node(node2, 7);
    append_node(node2, 8);
    append_node(node2, 9);

    // printf("before inserting:\n");
    // print_list(*node1);

    // insert_node(node1, 8, 3);

    // printf("after inserting:\n");
    // print_list(*node1);

}

void print_list(struct node head) {
    if (head.next == NULL) {
        printf("%i\n", head.value);
    } else {
        printf("%i\n", head.value);
        print_list(*head.next);
    }
}

struct node *make_node(int new_value){
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->value = new_value;
    new_node->next = NULL;
    return new_node;
}

int delete_node(struct node *garbage_node){
    if (garbage_node->value){
        free(garbage_node);
        return 1;
    }
    return 0;
}

struct node *push_end_node(struct node *head, int new_value) {
    if (head->next == NULL) {
        struct node *new_node = make_node(new_value);
        // printf("new node value to be inserted: %i\n", new_node->value);
        head->next = new_node;
        return new_node;
    } else {
        // printf("not there yet...");
        return push_end_node(head->next, new_value);
    }
}

// returns pointer to new node so we are able to test it in main()
struct node *push_node(struct node *head, int new_value) {
    struct node *new_node = make_node(new_value);
    new_node->next = head;
    return new_node;
}

struct node *insert_node(struct node *head, int new_value, int idx) {
    if (head->next == NULL){
       struct node *new_node = push_end_node(head->next,new_value);
       return new_node;
    }
    else if (idx <= 1){
       struct node *new_node = push_node(head->next,new_value);
       head->next = new_node;
       return new_node;
    }
    return insert_node(head->next, new_value, idx-1);
}



// TODO: insert node, pop

// remove node: takes head and idx, stitches list together after removing node at idx, returns &removed_node
// pop: set 2nd to last node's pointer to NULL, return orphaned node
