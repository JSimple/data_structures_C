#include <stdio.h>
#include <stdlib.h>

/*
TODO:
    change remove_node so that it works like insert_node
    create remove_before and remove_after to use in remove_node
    make sure we've implemented all singly linked list methods on DLL

    .....then, work on trees
*/

struct node {
    int value;
    struct node *next;
    struct node *prev;
};

void print_list(struct node*);
void print_reverse_list(struct node*);
struct node *insert_before(struct node*, int);
struct node *insert_after(struct node*, int);
struct node *remove_from_end(struct node*);
struct node *add_to_end(struct node*, int);
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

    struct node *node4 = make_node(5);
    node3->next = node4;
    node4->prev = node3;

    struct node *node5 = make_node(6);
    node4->next = node5;
    node5->prev = node4;

    /* INSERT NODE TESTS
        index too big
        index too small
        index is 0
        insert into different places in the middle
        add to end
        add to beginning
    */


    printf("Initial list:\n");
    print_list(head);

    head = insert_node(node3, 0, -100);

    printf("List after adding node to beginning:\n");
    print_list(head);

    struct node *new_middle_node = insert_node(node5, 4, -2);

    printf("List after adding node to middle:\n");
    print_list(head);

    struct node *new_end_node = insert_node(node5, 7, 1);

    printf("List after adding node to end:\n");
    print_list(head);

    printf("Trying to insert a node at 'index 0':\n");

    struct node *bad_node = insert_node(head, 100, 0);
    print_list(head);

    printf("Bad node: %i\n", bad_node);



    // add_to_end(head, 7);
    // add_to_end(head, 8);
    // add_to_end(head, 9);
    // add_to_end(head, 10);
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
struct node *insert_before(struct node *current_node, int new_value) {
    struct node *new_node = make_node(new_value);
    new_node->next = current_node;

    if (current_node->prev != NULL) {
        new_node->prev = current_node->prev;
        current_node->prev->next = new_node;
    }

    current_node->prev = new_node;
    return new_node;
}

struct node *insert_after(struct node *current_node, int new_value) {
    struct node *new_node = make_node(new_value);
    new_node->prev = current_node;

    if (current_node->next != NULL) {
        new_node->next = current_node->next;
        current_node->next->prev = new_node;
    }

    current_node->next = new_node;
    return new_node;
}

// pop: set 2nd to last node's pointer to NULL, return orphaned node
struct node *remove_from_end(struct node *head){
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
        return remove_from_end(head->next);
    }
}

struct node *add_to_end(struct node *head, int new_value) {
    if (head->next == NULL) {
        struct node *new_node = make_node(new_value);
        // printf("new node value to be inserted: %i\n", new_node->value);
        head->next = new_node;
        new_node->prev = head;
        return new_node;
    } else {
        // printf("not there yet...");
        return add_to_end(head->next, new_value);
    }
}

struct node *insert_node(struct node *current_node, int new_value, int idx) {
    if (idx > 0) {
        if (current_node->next == NULL){
            struct node *new_node = insert_after(current_node, new_value);
            return new_node;
        } else if (idx == 1){
            struct node *new_node = insert_after(current_node, new_value);
            return new_node;
        }
        return insert_node(current_node->next, new_value, idx-1);
    } else if (idx < 0) {
        if (current_node->prev == NULL) {
           struct node *new_node = insert_before(current_node, new_value);
           return new_node;
        } else if (idx == -1) {
            struct node *new_node = insert_before(current_node, new_value);
        }
        return insert_node(current_node->prev, new_value, idx+1);
    } else {
        printf("Please enter a non-zero integer for the index!\n");
        return NULL;
    }
}


struct node *remove_node(struct node *current_node, int idx) {
    if (idx == 0){
        if (current_node->next != NULL && current_node->prev != NULL){
            current_node->prev->next = current_node->next;
            current_node->next->prev = current_node->prev;
            current_node->next, current_node->prev = NULL;
            return current_node;
        }
        else if (current_node->next != NULL){
            current_node->next->prev, current_node->next = NULL;
            return current_node;
        }
        else if (current_node->prev != NULL){
            current_node->prev->next, current_node->prev = NULL;
            return current_node;
        }
        else{
            return current_node;
        }
    }
    if (idx > 0){
        if (current_node->next == NULL){
            return (remove_node(current_node, 0));
        }
        return(remove_node(current_node->next, idx-1));
    }
    else{
        if (current_node->prev == NULL){
            return (remove_node(current_node, 0));
        }
        return(remove_node(current_node->prev, idx+1));
    }

    if (idx > 0) {
        if (current_node->next == NULL){

            //struct node *new_node = remove_after(current_node);
            return new_node;
        } else if (idx == 1){
            //struct node *new_node = remove_after(current_node);
            return new_node;
        }
        return remove_node(current_node->next, idx-1);
    } else if (idx < 0) {
        if (current_node->prev == NULL) {
           //struct node *new_node = remove_before(current_node);
           return new_node;
        } else if (idx == -1) {
            //struct node *new_node = remove_before(current_node);
        }
        return remove_node(current_node->prev, idx+1);
    } else {
        //printf("Please enter a non-zero integer for the index!\n"); remove current node
        return NULL;
    }
}


// struct node *remove_node(struct node *current_node, int idx){
//     if (current_node->next == NULL){
//         printf("List is just one node. Stop trying to remove nodes!");
//         return current_node;
//     }
//     if (current_node->next->next == NULL){
//         if (idx > 1){
//             printf("Index exceeds list length!");
//             return current_node->next;
//         }
//         else {
//             struct node *removed_node = current_node->next;
//             return remove_from_end(current_node);
//         }
//     }
//     else if(idx <= 1){
//         struct node *removed_node = current_node->next;
//         current_node->next = removed_node->next;
//         removed_node->next = NULL;
//         return removed_node;
//     }
//     return remove_node(current_node->next, idx-1);
// }

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
