#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
/* 
 XOR_LL.c
 Purpose: XOR Linked List implementation that allows for both forward and backward traversal similar to a doubly linked list
          but only uses a single memory space for the XOR'ed value of the addresses of the previous Node and the next Node
          this allows traversal in both directions without the need for two pointers
*/



// struct for int-holding Node
struct Node {
    int data;
    struct Node* xor;
};
// XOR function to generate the XOR'ed addresses of previous node and next node
struct Node* XOR (struct Node* prev, struct Node* next) {
    return (struct Node*) ((uintptr_t) (prev) ^ (uintptr_t) (next));
}
// creates a new Node from data and inserts in front of given Node* pointer
void insert(struct Node** head, int data) {
    struct Node* new_node = (struct Node*) malloc (sizeof (struct Node));
    new_node->data = data;
    new_node->xor = XOR (NULL, *head);

    if(*head != NULL) {
        struct Node* next = XOR(NULL, (*head)->xor);
        (*head)->xor = XOR(next, new_node);
    }
    *head = new_node;
}
// traverses the LL and prints data for each followed by a space
void print_list (struct Node* head) {
    struct Node* curr = head;
    struct Node* prev = NULL;
    struct Node* next;

    while (curr != NULL) {
        printf("%d ", curr->data);
        next = XOR(prev, curr->xor); // need to calculate next by XOR'ing between the previous and our current XOR'ed value
        prev = curr;
        curr = next;
    }
}

int main() {
    struct Node* head = NULL;
    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30);
    insert(&head, 40);
    print_list(head);
    return (0);
}