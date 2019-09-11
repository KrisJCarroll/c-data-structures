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

void delete(struct Node** head, int data) {
    struct Node* curr = *head;
    struct Node* prev = NULL;
    struct Node* temp = NULL;

    while (curr != NULL && curr->data != data) {
        temp = curr;
        curr = XOR(prev, curr->xor);
        prev = temp;
    }

    if(!curr) {
        printf("Element not found.");
        return;
    }

    if(prev) {
        prev->xor = XOR(XOR(prev->xor, curr), XOR(prev, curr->xor));
        temp = XOR(curr->xor, prev);
    }

    if(temp) {
        temp->xor = XOR( XOR(temp->xor, curr), prev);
    }

    if(!prev) {
        *head = curr->xor;
    }
    free(curr);

}

void append(struct Node** tail, int data) {
    struct Node* new_node = (struct Node*) malloc (sizeof (struct Node));
    new_node->data = data;
    new_node->xor = XOR(*tail, NULL);

    if (*tail != NULL) {
        struct Node* prev = XOR((*tail)->xor, NULL);
        (*tail)->xor = XOR(new_node, prev);
    }
}
// traverses the LL and prints data for each followed by a space
void print_list (struct Node* head) {
    struct Node* curr = head;
    struct Node* prev = NULL;
    struct Node* next;

    while (curr) {
        printf("%d ", curr->data);
        next = XOR(prev, curr->xor); // need to calculate next by XOR'ing between the previous and our current XOR'ed value
        prev = curr;
        curr = next;
    }
    printf("\n");
}


int main() {
    struct Node* head = NULL;
    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30);
    insert(&head, 40);
    print_list(head);
    delete(&head, 30);
    print_list(head);
    
    struct Node* tail = NULL;
    insert(&tail, 40);
    insert(&tail, 30);
    insert(&tail, 20);
    insert(&tail, 10);
    // Will always print in the direction leading away from the Node you provide if that node is NULL
    print_list(tail);

    append(&tail, 40);
    append(&tail, 30);
    append(&tail, 20);
    append(&tail, 10);
    print_list(tail);

    return (0);
}