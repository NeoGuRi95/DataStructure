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
    Node *temp = (Node *)malloc(sizeof(Node));      // 인수 형태: add_first2(&head, item)
    temp->data = item;                              // &head: 포인터 변수의 주소값
    temp->next = *ptr_head;
    *ptr_head = temp;
}

Node *add_first3(Node *head, char *item) {          // 첫번째 노드를 가리키는 포인터 head가 전역변수가 아닌 경우
    Node *temp = (Node *)malloc(sizeof(Node));      // 첫번째 노드를 가리키는 포인터를 리턴
    temp->data = item;
    temp->next = head;
    return temp;
}

int insert_after(Node *prev, char *item) {
    if (prev == NULL)
        return 0;

    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = item;
    tmp->next = prev->next;
    prev->next = tmp;

    return 1;
}

Node *remove_first() {
    if (head == NULL)
        return NULL;
    
    Node *temp = head;
    head = head->next;
    return temp;
}

Node *remove_after (Node *prev) {
    Node *temp = prev->next;
    if (temp == NULL)
        return NULL;
    prev->next = temp->next;
    return temp;
}

Node *find(char *word) {
    Node *p = head;

    while (p != NULL) {
        if (strcmp(p->data, word) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

Node *get_node(int index) {
    if (index < 0)
        return NULL;
    Node *p = head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p;
}

int add(int index, char *item) {
    if (index < 0)
        return 0;
    if (index == 0 || head == NULL) {
        add_first(item);
        return 1;
    }
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->next = NULL;
    Node *prev = get_node(index - 1);
    if (prev != NULL) {
        insert_after(temp, item);
        return 1;
    }
    return 0;
}

Node *remove(int index) {
    if (index < 0) 
        return NULL;
    if (index == 0)
        return remove_first();

    Node *prev = get_node(index-1);

    if (prev == NULL)
        reuturn NULL;

    return remove_after(prev);
}

Node *remove2(char *item) {
    Node *q = head;
    Node *p = NULL;

    while (strcmp(p->data, item) != 0 && p != NULL) {
        q = p;
        p = p->next;
    }
    
    if (p == NULL)
        return NULL;
    else if (q == NULL)
        return remove_first();
    else
        return remove_after(q);
}

void add_to_ordered_list(char *item) {
    Node *p = head;
    Node *q = NULL;

    while (strcmp(p->data, item) < 0 && p != NULL) {
        q = p;
        p = p->next;
    }
    if (q == NULL)
        add_first(item);
    else
        insert_after(q, item);
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