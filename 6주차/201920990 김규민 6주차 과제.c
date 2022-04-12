#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
    char data[MAX_STACK_SIZE];
    int v[MAX_STACK_SIZE];
    int top;
}StackType;

void initStack(StackType* s) {         //���� �ʱ�ȭ
    s->top = -1;
}

int is_empty(StackType* s) {         //���� ������� ����
    return (s->top == -1);
}


int is_full(StackType* s) {            //���� ��ȭ���� ����
    return(s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, char item) {   //���� ����
    if (is_full(s)) {
        fprintf(stderr, "������ ��ȭ���� �Դϴ�.");
        return;
    }
    else {
        printf("\n%c�� push�˴ϴ�.", item);
        s->data[++(s->top)] = item;
    }
}

void push1(StackType* s, int item) {   //���� ����
    if (is_full(s)) {
        fprintf(stderr, "������ ��ȭ���� �Դϴ�.");
        return;
    }
    else {
        s->v[++(s->top)] = item;
    }
}

element pop(StackType* s) {            //���� ����
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        return;
    }
    else
        printf("\n%c�� pop�˴ϴ�.", s->data[(s->top)]);
        return s->data[(s->top)--];
}

int pop1(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        return;
    }
    else return s->v[(s->top)--];
}

element peek(StackType* s) {            //���� ã��
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else return s->data[s->top];
}
int peek1(StackType* s) {            //���� ã��
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else return s->v[s->top];
}

int prec(char op) {
    switch (op)
    {
    case '(': case ')':
        return 0;
    case '|':
        return 1;
    case '&':
        return 2;
    case '>': case '<':
        return 3;
    case'+': case '-':
        return 4;
    case '*': case '/': case '%':
        return 5;
    case '^':
        return 6;
    }                                                       //�켱������ �����ΰ��� ���� ū ���� ������
}

void postfix(char cal[], StackType* s) {
    int i, k = 0;
    int len = strlen(cal);
    int len1 = len;
    char num[MAX_STACK_SIZE];
    char ch, op;
    for (i = 0; i < len; i++) {
        ch = cal[i];
        switch (ch)
        {
        case '*': case '/': case '%': case '+': case '-': case '>': case '<': case '&': case '^': case '|': {
            if (!is_empty(s) && ch == '^' && ch == peek(s)) {
                push(s, ch);
                break;
            }
            while (!is_empty(s) && (prec(ch) <= prec(peek(s)))) {           //��� �ҷ��°� �켱������ �� ������ �״�� push
                num[k++] = pop(s);                                          //�ٸ� �迭�� �����Ҳ��� pop���� �ҷ��ͼ� ������ �ε����� ����.
            }
            push(s, ch);                                                    //���ÿ� ���� ��ȣ�� �켱������ �� ������ pop���� ���� �Ŀ� ���� ��ȣ push
            break;
        }
        case '(': {
            push(s, ch);                                                    //��ȣ�� ����
            len1--;                                                         //��ȣ�� ����ǥ��Ŀ��� �����Ǳ⶧���� len���� ��ȣ�� ������ŭ ���̱�.
            break;
        }
        case')': {
            op = pop(s);
            len1--;                                                         //���� ��ȣ�� ���ö� ������ ���� case�� �ɷ� �켱������� ��µ�.
            while (op != '(') {                                         //���� ��ȣ�� ������ ������ȣ�� ���ö� ���� ���ÿ� ���� ������ �̱�.
                num[k++] = op;
                op = pop(s);
            }
            break;
        }
        default: {
            num[k++] = ch;
            break;
        }
        }
    }
    while (!is_empty(s)) {
        num[k++] = pop(s);
    }
    printf("\n����ǥ��� ����� : ");
    for (int j = 0; j < len1; j++)
        printf("%c", num[j]);
    printf("\n");
    printf("\n======================����ǥ��� ���=====================\n");
    evaluate(num, len1);
}

int pow1(int a, int b) {
    int s = 1;
    for (int i = 0; i < b; i++) {
        s *= a;
    }
    return s;
}


int evaluate(char* str, int len) {
    StackType s;
    int op1, op2;
    int value;
    char ch;
    initStack(&s);
    for (int i = 0; i < len; i++) {                        //������ �̿��� ���� ģ ������ ���̸�ŭ ��
        ch = str[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '^' && ch != '>' && ch != '<' && ch != '&' && ch != '|') {
            value = ch - '0';                                 //�ƽ�Ű�ڵ� �������� ���ڴ� int������ ��ȯ��Ŵ
            push1(&s, value);
            printf("%d�� push�մϴ�.\n", value);
        }
        else if (ch == '^') {
            int sum = 0;
            if (is_empty(&s)) {                                 //����Ȯ��
                printf("\n������ �����Դϴ�.\n\n");
                return;
            }
            else {                                          //���� ������ �ƴ϶�� pop���� ���� ��������
                op2 = pop1(&s);
                printf("%d�� pop�մϴ�.\n", op2);
            }
            if (is_empty(&s)) {
                printf("\n������ �����Դϴ�.\n\n");
                return;
            }
            else {                                          //�� �����ִ� ���� �ѹ� �� pop���� ��������
                op1 = pop1(&s);
                printf("%d�� pop�մϴ�.\n", op1);
            }
            push1(&s, pow1(op1, op2));                              //power�Լ��� ���� ����
            printf("%d^%d ����� : %d\n%d�� push�մϴ�.\n", op1, op2, pow1(op1, op2), pow1(op1, op2));
        }
        else {
            if (is_empty(&s)) {
                printf("\n������ �����Դϴ�.\n\n");
                return;
            }
            else {
                op2 = pop1(&s);
                printf("%d�� pop�մϴ�.\n", op2);
            }
            if (is_empty(&s)) {
                printf("\n������ ���� �Դϴ�.\n\n");
                return;
            }
            else {
                op1 = pop1(&s);
                printf("%d�� pop�մϴ�.\n", op1);
            }
            switch (ch) {                                             //���⼭���� ��ǻ�Ͱ� �˾Ƽ� �����Ҽ� �ִ� ��ȣ���̱� ������ case�� ����
            case'+':
                push1(&s, op1 + op2);
                printf("%d+%d ����� : %d \n%d�� push�մϴ�.\n", op1, op2, op1 + op2, op1 + op2);
                break;
            case'-': {
                push1(&s, op1 - op2);
                printf("%d-%d ����� : %d \n%d�� push�մϴ�.\n", op1, op2, op1 - op2, op1 - op2);
                break;
            }
            case'*': {
                push1(&s, op1 * op2);
                printf("%d*%d ����� : %d \n%d�� push�մϴ�.\n", op1, op2, op1 * op2, op1 * op2);
                break;
            }
            case'/': {
                push1(&s, op1 / op2);
                printf("%d/%d ����� : %d \n%d�� push�մϴ�.\n", op1, op2, op1 / op2, op1 / op2);
                break;
            }
            case'%': {
                push1(&s, op1 % op2);
                printf("%d%c%d ����� : %d\n%d�� push�մϴ�.\n", op1, 37, op2, op1 % op2, op1 % op2);
                break;
            }
            case'&': {
                push1(&s, op1 && op2);
                printf("%d&%d ����� : %d\n%d�� push�մϴ�.\n", op1, op2, op1 && op2, op1 && op2);
                break;
            }
            case'|': {
                push1(&s, op1 || op2);
                printf("%d|%d ����� : %d\n%d�� push�մϴ�.\n", op1, op2, op1 || op2, op1 || op2);
                break;
            }
            case '<': {
                push1(&s, op1 < op2);
                printf("%d<%d ����� : %d\n%d�� push�մϴ�.\n", op1, op2, op1 < op2, op1 < op2);
                break;
            }
            case '>': {
                push1(&s, op1 > op2);
                printf("%d>%d ����� : %d\n%d�� push�մϴ�.\n", op1, op2, op1 > op2, op1 > op2);
                break;
            }
            }
        }
    }
    int result = pop1(&s);
    printf("====================����ǥ��� ���Ϸ�===================\n");
    printf("\n����� : %d\n\n", result);
    return;
}

int main(void) {
    StackType d;
    initStack(&d);
    char cal[MAX_STACK_SIZE];
    int q = 0;
    while (1) {
        printf("0.���α׷� ����.\n1.���α׷� �����.\n���ϴ� ���α׷��� ��ȣ�� �Է��Ͻÿ� : ");
        scanf("%d", &q);
        switch (q) {
            {
        case 0:
            printf("���α׷��� �����մϴ�.");
            return 0;
            }
        case 1: {
            printf("������� �Է��Ͻÿ� : ");
            scanf("%s", cal);
            postfix(cal, &d);
            break;
        }
        }
    }
}