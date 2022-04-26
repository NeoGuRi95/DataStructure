#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char *data;
    struct node *prev;
    struct node *next;
};

typedef struct node Node;

Node *head;
Node *tail;
int size = 0;

void add_after(Node *prev, char *item) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = item;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (prev == NULL && head == NULL) {         // empty list
        head = new_node;
        tail = new_node;
    }
    else if (prev == NULL) {            // add first
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    else if (prev == tail) {            // add last
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    else {                              // insert node
        new_node->prev = prev;
        new_node->next = prev->next;
        prev->next->prev = new_node;
        prev->next = new_node;
    }
    size++;
}

void remove(Node *p) {
    if (head == p && tail == p) {           // p is only node of list
        head = NULL;
        tail = NULL;
    }
    else if (head == p) {               // p is head
        p->next->prev = NULL;
        head = p->next;
    }
    else if (tail == p) {               // p is tail
        p->prev->next = NULL;
        tail = p->prev;
    }
    else {                              // p is middle node
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    free(p);
    size--;
}

add_ordered_list(char *item) {          // start searching at tail
    Node *p = tail;
    while (p != NULL && strcmp(item, p->data) < 0) {
        p = p->prev;
    }
    add_after(p, item);
}

int main() {
    return 0;
}