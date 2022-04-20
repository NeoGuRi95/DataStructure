#include <stdio.h>
#include <stdlib.h>

struct node
{
    char *data;
    struct node *next;
};

typedef struct node Node;
Node *head = NULL;

void add_first(char *item) {                        // ù��° ��带 ����Ű�� ������ head�� ���������� ���
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = item;
    temp->next = head;
    head = temp;
}

void add_first2(Node **ptr_head, char *item) {      // ù��° ��带 ����Ű�� ������ head�� ���������� �ƴ� ���
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