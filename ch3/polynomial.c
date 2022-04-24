#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POLYS 100
#define BUFFER_LENGTH 50

int read_line(FILE *fp, char str[], int limit) { // 키보드만이 아니라 파일로부터도 읽을 수 있도록 하였다.
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
    Term *p = poly->first, *q = NULL;       // p: 현재 가리키고 있는 노드, q: 전 노드

    while ((p != NULL) && (p->expo > e)) {          // 삽입하려는 노드의 차수가 현재 노드의 차수와 같거나 작은 경우(OR 더 이상 노드가 없을 경우)를 발견할 때 멈춤
        q = p;
        p = p->next;
    }

    if (e == p->expo) {         // 차수가 같을 경우
        p->coef += c;
        if (p->coef == 0) {           // 두 계수의 합이 0인 경우 -> 현재 노드 삭제
            if (q == NULL)             // 현재 노드가 첫번째인 경우
                poly->first = p->next;
            else
                q->next = p->next;
            free(p);
            poly->size--;
            return;
        }
    }

    Term *new_term = create_term_instance();        // 새로 삽입할 노드
    new_term->coef = c;
    new_term->expo = e;
    
    if (q == NULL) {          // 맨 앞에 삽입하는 경우
        new_term->next = poly->first;
        poly->first = new_term;
    }
    else {          // q 뒤에 삽입하는 경우
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

    if (coef == 0) coef = sign_coef;            // coef가 0인 경우 계수는 0이 아니라 1 혹은 -1 이다
    else coef += sign_coef;

    if (i >= end) {             // 더 이상 항을 구성하는 문자가 없다면 상수항이라는 의미이다.
        add_term(coef, 0, p_poly);
        return 1;
    }

    if (expr[i] != 'x') return 0;           // 계수 다음에 x가 아닌 다른 문자가 등장해서는 안된다.
    i++;

    if (i >= end) {         // 계수 다음에 x가 나오고 문자열이 끝난다면 1차항이라는 의미이다.
        add_term(coef, 1, p_poly);
        return 1;
    }

    if (expr[i] != '^') return 0;           // x 다음에 ^가 아닌 다른 문자가 등장해서는 안된다.
    i++;

    expo = 0;
    while (i < end && expr[i] >= '0' && expr[i] <= '9') {           // 차수 부분을 읽는다.
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
            handle_definition(copied);          // 다항식을 입력받아 정의하는 일을 한다.
        }
    }
}

int main() {
    process_command();
    return 0;
}