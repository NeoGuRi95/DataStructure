#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POLYS 100
#define BUFFER_LENGTH 50

int read_line(FILE *fp, char str[], int limit) { // Ű���常�� �ƴ϶� ���Ϸκ��͵� ���� �� �ֵ��� �Ͽ���.
    int ch, i = 0;

    while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
        if (i < limit - 1)
            str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}

struct term {
    int coef;
    int expo;
    struct term *next;
};

typedef struct term Term;

typedef struct polynomial {
    char name;
    Term *first;
    int size;
} Polynomial;

Polynomial *polys[MAX_POLYS];
int n = 0;

Term *create_term_instance() {
    Term *t = (Term *)malloc(sizeof(Term));
    t->coef = 0;
    t->expo = 0;
    t->next = NULL;
    return t;
}

Polynomial *create_polynomial_instance(char name) {
    Polynomial *ptr_poly = (Polynomial *)malloc(sizeof(Polynomial));
    ptr_poly->name = name;
    ptr_poly->first = NULL;
    ptr_poly->size = 0;
    return ptr_poly;
}

void add_term(int c, int e, Polynomial *poly) {
    if (c == 0)
        return;
    Term *p = poly->first, *q = NULL;       // p: ���� ����Ű�� �ִ� ���, q: �� ���

    while ((p != NULL) && (p->expo > e)) {          // �����Ϸ��� ����� ������ ���� ����� ������ ���ų� ���� ���(OR �� �̻� ��尡 ���� ���)�� �߰��� �� ����
        q = p;
        p = p->next;
    }

    if (e == p->expo) {         // ������ ���� ���
        p->coef += c;
        if (p->coef == 0) {           // �� ����� ���� 0�� ��� -> ���� ��� ����
            if (q == NULL)             // ���� ��尡 ù��°�� ���
                poly->first = p->next;
            else
                q->next = p->next;
            free(p);
            poly->size--;
            return;
        }
    }

    Term *new_term = create_term_instance();        // ���� ������ ���
    new_term->coef = c;
    new_term->expo = e;
    
    if (q == NULL) {          // �� �տ� �����ϴ� ���
        new_term->next = poly->first;
        poly->first = new_term;
    }
    else {          // q �ڿ� �����ϴ� ���
        new_term->next = p;
        q->next = new_term;
    }
    poly->size++;
}

int eval(Term *term, int x) {
    int result = term->coef;
    for (int i = 0; i < term->expo; i++) {
        result *= x;
    }
    return result;
}

int eval(Polynomial *poly, int x) {
    if (poly->first == NULL)
        return NULL;

    int result = 0;
    Term *term = poly->first;

    while (term != NULL) {
        result += eval(term, x);
        term = term->next;
    }
    return result;
}

void handle_calc(char name, char *x_str) {
    int x = atoi(x_str);
    int result;
    int index = 0;
    while ((polys[index]->name != name) && (polys[index] != NULL)) {
        index += 1;
    }
    if (polys[index] == NULL)
        printf("There is no function named %c\n", name);
    else {
        result = eval(polys[index], x);
        if (result == NULL)
            printf("This function is not defined.\n");
        else
            printf("The function result is %d\n", result);
    }
}

void print_term(Term *term) {
    printf("%d", term->coef);
    if (term->expo == 0)
        return;
    else if (term->expo == 1) {
        printf("x");
        return;
    }
    else {
        printf("x^%d", term->expo);
    }
}

void print_poly(Polynomial *p) {
    printf("%c = ", p->name);
    Term *term = p->first;
    while (term != NULL) {
        print_term(term);
        term = term->next;
    }
    printf("\n");
}

void handle_print(char name) {
    int index = 0;
    while ((polys[index]->name != name) && (polys[index] != NULL)) {
        index += 1;
    }
    if (polys[index] == NULL)
        printf("There is no function named %c\n", name);
    else
        print_poly(polys[index]);
}

void erase_blanks(char *expression) {
    int i, k = 0;

    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] != ' ') expression[k++] = expression[i];
    }

    expression[k] = '\0';
}

void destroy_polynomial(Polynomial *ptr_poly) {
    if (ptr_poly == NULL) return;

    Term *t = ptr_poly->first, *tmp;
    while (t != NULL) {
        tmp = t;
        t = tmp -> next;
        free(tmp); 
    }
    free(ptr_poly);
}

void insert_polynomial(Polynomial *ptr_poly) {
    for (int i = 0; i < n; i++) {
        if (polys[i]->name == ptr_poly->name) {
            destroy_polynomial(polys[i]);
            polys[i] = ptr_poly;
            return;
        }
    }
    polys[n] = ptr_poly;
    n++;
}

Polynomial *create_by_add_two_polynomias(char name, char f, char g) {
    Polynomial *poly = (Polynomial *)malloc(sizeof(Polynomial)), *f_poly, *g_poly;
    poly->name = name;

    for (int i = 0; i < n; i++) {
        if (polys[i]->name == f) f_poly = polys[i];
        else if (polys[i]->name == g) g_poly = polys[i];
    }

    Term *term = f_poly->first;
    while (term != NULL) {
        add_term(term->coef, term->expo, poly);
        term = term->next;
    }

    term = g_poly->first;
    while (term != NULL) {
        add_term(term->coef, term->expo, poly);
        term = term->next;
    }
}

int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly) {
    int i=begin;
    int sign_coef = 1, coef = 0, expo = 1;

    if (expr[i] == '+')
        i++;
    else if (expr[i] == '-') {
        sign_coef = -1;
        i++;
    }
    while (i < end && expr[i] >= '0' && expr[i] <= '9') {
        coef = coef*10 + (int)(expr[i]-'0');
        i++;
    }

    if (coef == 0) coef = sign_coef;            // coef�� 0�� ��� ����� 0�� �ƴ϶� 1 Ȥ�� -1 �̴�
    else coef += sign_coef;

    if (i >= end) {             // �� �̻� ���� �����ϴ� ���ڰ� ���ٸ� ������̶�� �ǹ��̴�.
        add_term(coef, 0, p_poly);
        return 1;
    }

    if (expr[i] != 'x') return 0;           // ��� ������ x�� �ƴ� �ٸ� ���ڰ� �����ؼ��� �ȵȴ�.
    i++;

    if (i >= end) {         // ��� ������ x�� ������ ���ڿ��� �����ٸ� 1�����̶�� �ǹ��̴�.
        add_term(coef, 1, p_poly);
        return 1;
    }

    if (expr[i] != '^') return 0;           // x ������ ^�� �ƴ� �ٸ� ���ڰ� �����ؼ��� �ȵȴ�.
    i++;

    expo = 0;
    while (i < end && expr[i] >= '0' && expr[i] <= '9') {           // ���� �κ��� �д´�.
        expo = expo*10 + (int)(expr[i]-'0');
        i++;
    }

    add_term(coef, expo, p_poly);
    return 1;
}

Polynomial *create_by_parse_polynomial(char name, char *body) {
    Polynomial *ptr_poly = create_polynomial_instance(name);

    int i=0, begin_term=0;
    while (i<strlen(body)) {
        if (body[i]=='+' || body[i]=='-')
            i++;
        while (i<strlen(body) && body[i] != '+' && body[i] != '-')
            i++;

        int result = parse_and_add_term(body, begin_term, i, ptr_poly);

        if (result == 0) {
            destroy_polynomial(ptr_poly);
            return NULL;
        }

        begin_term = i;
    }
    return ptr_poly;
}

void handle_definition(char *expression) {
    erase_blanks(expression);
    
    char *f_name = strtok(expression, "=");
    if (f_name == NULL || strlen(f_name) != 1) {
        printf("Unsupported command.");
        return;
    }

    char *exp_body = strtok(NULL, "=");
    if (exp_body == NULL || strlen(exp_body) <= 0) {
        printf("Invalid expression format.--");
        return;
    }

    if (exp_body[0] >= 'a' && exp_body[0] <= 'z' && exp_body[0] != 'x') {
        char *former = strtok(exp_body, "+");
        if (former == NULL || strlen(former) != 1){
            printf("Invalid expression format.");
            return;
        }
        char *later = strtok(exp_body, "+");
        if (former == NULL || strlen(later) != 1){
            printf("Invalid expression format.");
            return;
        }
        Polynomial *pol = create_by_add_two_polynomias(f_name[0], former[0], later[0]);
        if (pol == NULL) {
            printf("Invalid expression format.");
            return;
        }
        insert_polynomial(pol);
    }
    else {
        Polynomial *pol = create_by_parse_polynomial(f_name[0], exp_body);
        if (pol == NULL) {
            printf("Invalid expression format.");
            return;
        }
        insert_polynomial(pol);
    }
}

void process_command()
{
    char command_line[BUFFER_LENGTH];
    char copied[BUFFER_LENGTH];
    char *command, *arg1, *arg2;
    while(1) {
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
            continue;
        strcpy(copied, command_line);
        command = strtok(command_line, " ");
        if (strcmp(command, "print") == 0) {
            arg1 = strtok(NULL, " ");
            if (arg1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            handle_print(arg1[0]);
        }
        else if (strcmp(command, "calc") == 0) {
            arg1 = strtok(NULL, " ");
            if (arg1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            arg2 = strtok(NULL, " ");
            if (arg2 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            handle_calc(arg1[0], arg2);
        }
        else if (strcmp(command, "exit") == 0)
            break;
        else {
            handle_definition(copied);          // ���׽��� �Է¹޾� �����ϴ� ���� �Ѵ�.
        }
    }
}

int main() {
    process_command();
    return 0;
}