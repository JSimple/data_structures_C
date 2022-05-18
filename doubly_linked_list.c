#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
    struct node *prev;
};
// vocabulary:
// add_to
// remove_from
// beginning
// end
// insert_at_index
void print_list(struct node*);
void print_reverse_list(struct node*);
struct node *push_node(struct node*, int);
struct node *pop_node(struct node*);
struct node *pop_given_tail(struct node*);
struct node *pop_given_head(struct node*);
struct node *push_given_head(struct node*);
struct node *push_given_tail(struct node*);
struct node *push_end_node(struct node*, int);
struct node *make_node(int);
struct node *insert_node(struct node*, int, int);
struct node *remove_node(struct node*, int);
int delete_node(struct node*);
struct node *return_head(struct node*);
struct node *return_tail(struct node*);

/* struct linked_list { */
/*     struct node *head; */
/* }; */

int main() {
    struct node *head = make_node(1);

    struct node *node2 = make_node(2);
    head->next = node2;
    node2->prev = head;

    struct node *node3 = make_node(3);
    node2->next = node3;
    node3->prev = node2;

    struct node *node4 = make_node(4);
    node3->next = node4;
    node4->prev = node3;

    struct node *node5 = make_node(5);
    node4->next = node5;
    node5->prev = node4;

    printf("LIST BEFORE POP\n");
    print_list(head);
    struct node *popped = pop_node(head);

    printf("LIST AFTER POP\n");
    print_list(head);

    printf("POPPED NODE: %i\n", popped->value);

    // push_end_node(head, 7);
    // push_end_node(head, 8);
    // push_end_node(head, 9);
    // push_end_node(head, 10);
    // printf("LIST BEFORE REMOVE\n");
    // print_list(head);
    // struct node *removed = remove_node(head, 5);
    // printf("memory loc of removed node: %i\n", removed);
    // printf("removed's value: %i\n", removed->value);
    // printf("LIST AFTER REMOVE:\n");
    // print_list(head);


    // printf("before inserting:\n");
    // print_list(*node1);

    // insert_node(node1, 8, 3);

    // printf("after inserting:\n");
    // print_list(*node1);

}

// change so it takes a pointer
void print_list(struct node *head) {
    if (head->next == NULL) {
        printf("%i\n", head->value);
    } else {
        printf("%i\n", head->value);
        print_list(head->next);
    }
}

void print_reverse_list(struct node *head) {
    if (head->next == NULL) {
        printf("%i\n", head->value);
    } else {
        print_reverse_list(head->next);
        printf("%i\n", head->value);
    }
}

struct node *make_node(int new_value){
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->value = new_value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

int delete_node(struct node *garbage_node){
    if (garbage_node->value){
        free(garbage_node);
        return 1;
    }
    return 0;
}

// returns pointer to new node so we are able to test it in main()
struct node *push_node(struct node *head, int new_value) {
    struct node *new_node = make_node(new_value);
    new_node->next = head;
    head->prev = new_node;
    return new_node;
}

// pop: set 2nd to last node's pointer to NULL, return orphaned node
struct node *pop_node(struct node *head){
    if (head->next == NULL) {
        //account for edge case where list is 1 node
        if (head->prev == NULL) {
            printf("List is just one node. Stop trying to pop!");
            return head;
        }
        head->prev->next = NULL;
        head->prev = NULL;
        return head;
    } else {
        // printf("not there yet...");
        return pop_node(head->next);
    }
}



struct node *push_end_node(struct node *head, int new_value) {
    if (head->next == NULL) {
        struct node *new_node = make_node(new_value);
        // printf("new node value to be inserted: %i\n", new_node->value);
        head->next = new_node;
        new_node->prev = head;
        return new_node;
    } else {
        // printf("not there yet...");
        return push_end_node(head->next, new_value);
    }
}

// TO DO
struct node *insert_node(struct node *current_node, int new_value, int idx) {
    if (idx > 0) {
        if (current_node->next == NULL){
            struct node *new_node = push_end_node(current_node->next, new_value);
            return new_node;
        }
        else if (idx <= 1){
            struct node *new_node = push_node(current_node->next, new_value);
            current_node->next = new_node;
            new_node->prev = current_node;
            return new_node;
        }
        return insert_node(current_node->next, new_value, idx-1);
    } else if (idx < 0) {
        if (current_node->prev == NULL) {
            ; 
        }
    } else {
        printf("Please enter a non-zero integer for the index!\n");
        return NULL;
    }
}

struct node *remove_node(struct node *head, int idx){
    if (head->next == NULL){
        printf("List is just one node. Stop trying to remove nodes!");
        return head;
    }
    if (head->next->next == NULL){
        if (idx > 1){
            printf("Index exceeds list length!");
            return head->next;
        }
        else {
            struct node *removed_node = head->next;
            return pop_node(head);
        }
    }
    else if(idx <= 1){
        struct node *removed_node = head->next;
        head->next = removed_node->next;
        removed_node->next = NULL;
        return removed_node;
    }
    return remove_node(head->next, idx-1);
}

struct node *return_head(struct node *tail) {
    if (tail->prev == NULL) {
        return tail;
    } else {
        return return_head(tail->prev);
    }
}

struct node *return_tail(struct node *head) {
    if (head->next == NULL) {
        return head;
    } else {
        return return_tail(head->next);
    }
}

// TODO:
// return_head
// return_tail
