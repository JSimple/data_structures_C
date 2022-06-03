#include <stdio.h>
#include <stdlib.h>

/*
TODO:
    - iterative functions
    - `cursor` struct
*/

struct node {
    int value;
    struct node *next;
    struct node *prev;
};

void print_list(struct node*);
void print_list_i(struct node*);
void print_reverse_list(struct node*);
void print_reverse_list_i(struct node*);
struct node *insert_before(struct node*, int);
struct node *insert_after(struct node*, int);
struct node *remove_current_node(struct node*);
struct node *remove_from_end(struct node*);
struct node *remove_from_end_i(struct node*);
struct node *remove_from_beginning_i(struct node*);
struct node *add_to_end(struct node*, int);
struct node *add_to_end_i(struct node*, int);
struct node *add_to_beginning_i(struct node*, int);
struct node *make_node(int);
struct node *insert_node(struct node*, int, int);
struct node *insert_node_i(struct node*, int, int);
struct node *remove_node_i(struct node*, int);
void delete_node(struct node*);
struct node *return_head(struct node*);
struct node *return_tail(struct node*);
struct node *return_head_i(struct node*);
struct node *return_tail_i(struct node*);

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

    printf("List before removing node:\n");
    print_list_i(head);

    struct node *removed_node = remove_node_i(node5, 800);

    printf("List after removing last node (5):\n");
    print_list_i(head);

    printf("removed node");
    printf("%i, value: %i", removed_node, removed_node->value);

    // struct node *node7 = insert_node_i(head, 7, 6);

    // printf("List after adding second node (7):\n");
    // print_list_i(head);

    // struct node *node_neg_1 = insert_node_i(node5, -1, -5);

    // printf("List after adding third node (-1):\n");
    // print_list_i(node_neg_1);

    // struct node *node0 = insert_node_i(node5, 0, -5);

    // printf("List after adding third node (0):\n");
    // print_list_i(node_neg_1);



}

//TODO: safe version that stops when you reach your head pointer - safeguards against circle problems
void print_list(struct node *head) {
    if (head->next == NULL) {
        printf("%i\n", head->value);
    } else {
        printf("%i\n", head->value);
        print_list(head->next);
    }
}

void print_list_i(struct node *current_node) {
    while (current_node != NULL) {
        printf("%i\n", current_node->value);
        current_node = current_node->next;
    }
}

// have it take tail
void print_reverse_list(struct node *head) {
    if (head->next == NULL) {
        printf("%i\n", head->value);
    } else {
        print_reverse_list(head->next);
        printf("%i\n", head->value);
    }
}

void print_reverse_list_i(struct node *current_node) {
    while (current_node != NULL) {
        printf("%i\n", current_node->value);
        current_node = current_node->prev;
    }
}

struct node *make_node(int new_value){
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->value = new_value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void delete_node(struct node *garbage_node){
    free(garbage_node);
}


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

struct node *remove_current_node(struct node *current_node) {
    if (current_node->next != NULL) {
        current_node->next->prev = current_node->prev;
    }
    if (current_node->prev != NULL) {
        current_node->prev->next = current_node->next;
    }
    current_node->next = NULL;
    current_node->prev = NULL;
    return current_node;
}


struct node *remove_from_end(struct node *head){
    if (head->next == NULL) {
        //account for edge case where list is 1 node
        if (head->prev == NULL) {
            printf("List is just one node. Stop trying to remove the last node!");
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

struct node *remove_from_end_i(struct node *current_node) {
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    return remove_current_node(current_node);
}

struct node *remove_from_beginning_i(struct node *current_node) {
    while (current_node->prev != NULL) {
        current_node = current_node->prev;
    }

    return remove_current_node(current_node);
}
// re-write using insert after
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

struct node *add_to_end_i(struct node *current_node, int new_value) {
    struct node *tail = return_tail_i(current_node);
    struct node *new_node = insert_after(tail, new_value);
    return new_node;
}

struct node *add_to_beginning_i(struct node *current_node, int new_value) {
    struct node *head = return_head_i(current_node);
    struct node *new_node = insert_before(head, new_value);
    return new_node;
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
            return new_node;
        }
        return insert_node(current_node->prev, new_value, idx+1);
    } else {
        printf("Please enter a non-zero integer for the index!\n");
        return NULL;
    }
}

struct node *insert_node_i(struct node *current_node, int new_value, int idx) {
    if (idx > 0) {
        while (idx > 1 && current_node->next != NULL) {
            idx--;
            current_node = current_node->next;
        }
        struct node *new_node = insert_after(current_node, new_value);
        return new_node;
    } else if (idx < 0) {
        while (idx < -1 && current_node->prev != NULL) {
            idx++;
            current_node = current_node->prev;
        }
        struct node *new_node = insert_before(current_node, new_value);
        return new_node;
    } else {
        printf("Please enter a non-zero integer for the index!\n");
        return NULL;
    }
}

struct node *remove_node_i(struct node *current_node, int idx){
    while (idx > 0 && current_node->next != NULL) {
            idx--;
            current_node = current_node->next;
        }
    while (idx < 0 && current_node->prev != NULL) {
            idx++;
            current_node = current_node->prev;
        }
    return remove_current_node(current_node);
}

struct node *return_head(struct node *tail) {
    if (tail->prev == NULL) {
        return tail;
    } else {
        return return_head(tail->prev);
    }
}

struct node *return_head_i(struct node *current_node) {
    while (current_node->prev != NULL) {
        current_node = current_node->prev;
    }

    return current_node;
}

struct node *return_tail(struct node *head) {
    if (head->next == NULL) {
        return head;
    } else {
        return return_tail(head->next);
    }
}

struct node *return_tail_i(struct node *current_node) {
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    return current_node;
}
