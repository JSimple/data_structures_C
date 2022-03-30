// node has:
// value
// pointer to next node (where it's stored?)

#include <stdio.h>

struct node {
    int value;
    struct node *next;
};


// struct node printValue(struct node *self){
//     printf(self.value);
// }


int main(){

struct node node1;
node1.value = 5;

struct node node2;
node2.value = 6;

node1.next = &node2;

struct node node2pointed = *node1.next;

printf("%i", node2pointed.value);

}

// for next time:
// figure out how to print next val directly
// implement LL methods