#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct Node {
    int data;
    struct Node* xor;
};

struct Node* XOR (struct Node* prev, struct Node* next) {
    return (struct Node*) ((uintptr_t) (prev) ^ (uintptr_t) (next));
}

void insert(struct Node** head_ref, int data) {
    struct Node *new_node = (struct Node*) malloc (sizeof (struct Node));
    new_node->data = data;
    new_node->xor = XOR (*head_ref, NULL);
}

void print_list (struct Node* head) {
    struct Node* curr = head;
    struct Node* prev = NULL;
    struct Node* next;

    while (curr != NULL) {
        printf("%d ", curr->data);
        next = XOR(prev, curr->xor);
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