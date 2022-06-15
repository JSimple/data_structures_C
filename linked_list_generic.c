#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "linked_list_generic.h"

int main() {
    struct node *head = make_node(6);
    add_to_end(head, &head);
    add_to_end(head, '!');
    add_to_end(head, 9);
    add_to_end(head, 10);
    printf("LIST BEFORE REMOVE\n");
    print_list(head);
    struct node *new_head = remove_from_beginning(head);
    printf("memory loc of new head node: %i\n", new_head);
    printf("new head's value: %i\n", new_head->value);
    printf("LIST AFTER REMOVE:\n");
    print_list(new_head);
    printf("OLD HEAD AFTER REMOVE:\n");
    print_list(head);


    // printf("before inserting:\n");
    // print_list(*node1);

    // insert_at_index(node1, 8, 3);

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

// TODO: add handling of malloc failure
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
struct node *add_to_beginning(struct node *head, int new_value) {
    struct node *new_node = make_node(new_value);
    new_node->next = head;
    return new_node;
}

struct node *add_to_end(struct node *head, int new_value) {
    if (head->next == NULL) {
        struct node *new_node = make_node(new_value);
        // printf("new node value to be inserted: %i\n", new_node->value);
        head->next = new_node;
        return new_node;
    } else {
        // printf("not there yet...");
        return add_to_end(head->next, new_value);
    }
}

// Set 2nd to last node's pointer to NULL, return orphaned node
struct node *remove_from_end(struct node *head){
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
        return remove_from_end(head->next);
    }
}

//removes head and returns the new head
struct node *remove_from_beginning(struct node *head){
    struct node *new_head = head->next;
    head->next = NULL;
    return new_head;
}

struct node *insert_at_index(struct node *head, int new_value, int idx) {
    if (head->next == NULL){
       struct node *new_node = add_to_end(head->next,new_value);
       return new_node;
    }
    else if (idx <= 1){
       struct node *new_node = add_to_beginning(head->next,new_value);
       head->next = new_node;
       return new_node;
    }
    return insert_at_index(head->next, new_value, idx-1);
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
            return remove_from_end(head);
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

bool is_empty(struct node *head) {
    return head == NULL;
}