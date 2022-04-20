#include <stdio.h>
#include <stdlib.h>

struct node
{
    char *data;
    struct node *next;
};

typedef struct node Node;
Node *head = NULL;

void add_first(char *item) {                        // 첫번째 노드를 가리키는 포인터 head가 전역변수인 경우
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = item;
    temp->next = head;
    head = temp;
}

void add_first2(Node **ptr_head, char *item) {      // 첫번째 노드를 가리키는 포인터 head가 전역변수가 아닌 경우
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = item;
    temp->next = *ptr_head;
    *ptr_head = temp;
}

Node *add_first3(Node *head, char *item) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = item;
    temp->next = head;
    return temp;
}

int main(void) {

    Node *head = (Node *)malloc(sizeof(Node));
    head->data = "Tuesday";
    head->next = NULL;

    Node *q = (Node *)malloc(sizeof(Node));
    q->data = "Thursday";
    q->next = NULL;
    head->next = q;

    q = (Node *)malloc(sizeof(Node));
    q->data = "Monday";
    q->next = head;
    head = q;

    Node *p = head;
    while (p != NULL) {
        printf("%s\n", p->data);
        p = p->next;
    }

    return 0;
}