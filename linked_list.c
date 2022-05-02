#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

void print_list(struct node*);
struct node *push_node(struct node*, int);
struct node *pop_node(struct node*);
struct node *push_end_node(struct node*, int);
struct node *make_node(int);
struct node *insert_node(struct node*, int, int);
struct node *remove_node(struct node*, int);
int delete_node(struct node*);

/* struct linked_list { */
/*     struct node *head; */
/* }; */

int main() {
    struct node *head = make_node(6);
    push_end_node(head, 7);
    push_end_node(head, 8);
    push_end_node(head, 9);
    push_end_node(head, 10);
    printf("LIST BEFORE REMOVE\n");
    print_list(head);
    struct node *removed = remove_node(head, 5);
    printf("memory loc of removed node: %i\n", removed);
    printf("removed's value: %i\n", removed->value);
    printf("LIST AFTER REMOVE:\n");
    print_list(head);


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

// returns pointer to new node so we are able to test it in main()
struct node *push_node(struct node *head, int new_value) {
    struct node *new_node = make_node(new_value);
    new_node->next = head;
    return new_node;
}

// pop: set 2nd to last node's pointer to NULL, return orphaned node
struct node *pop_node(struct node *head){
    //account for edge case where list is 1 node
    if (head->next == NULL){
        printf("List is just one node. Stop trying to pop!");
        return head;
    }
    if (head->next->next == NULL) {
        struct node *popped_node = head->next;
        head->next = NULL;
        return popped_node;
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
        return new_node;
    } else {
        // printf("not there yet...");
        return push_end_node(head->next, new_value);
    }
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
