/*��ȣ �˻� ���α׷�*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
}stackType;

void initStack(stackType* s) {         //���� �ʱ�ȭ
    s->top = -1;
}

int is_empty(stackType* s) {         //���� ������� ����
    return (s->top == -1);
}


int is_full(stackType* s) {            //���� ��ȭ���� ����
    return(s->top == (MAX_STACK_SIZE - 1));
}

void push(stackType* s, element item) {   //���� ����
    if (is_full(s)) {
        fprintf(stderr, "������ ��ȭ���� �Դϴ�.");
        return;
    }
    else {
        s->data[++(s->top)] = item;
    }
}

element pop(stackType* s) {            //���� ����
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        return;
    }
    else return s->data[(s->top)--];
}

element peek(stackType* s) {            //���� ã��
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else return s->data[s->top];
}

void check_matching(const char* a) {
    stackType s, count;
    int len = strlen(a);
    char ch, open_ch;
    int i = 0;  	// n= ���ڿ��� ����
    int count1 = 0, open_num;
    initStack(&s);
    initStack(&count);               //�ʱ�ȭ

    for (int i = 0; i < len; i++) {
        ch = a[i];	// ch = ���� ����
        switch (ch) {
        case '(':  case '[':    case '{':       //���� ��ȣ�� ������ push
            push(&s, ch);                       //��ȣ�� ��ȣ�� ���ڸ� �ٸ� ����ü�� ����
            push(&count, count1 + 1);
            printf("%d ", count1 + 1);
            count1++;                           //ī��Ʈ�� ����ؼ� �������̱⶧���� ���ο� ��ȣ�� ���ڱ� ��Ÿ���� ��ȣ��� ����
            break;
        case ')':  case ']':    case '}':       //���� ��ȣ�� ������ pop
            if (is_empty(&s)) {
                return 0;
            }
            else {
                open_ch = pop(&s);              //��ȣ�� ��ȣ�� ��ȣ�� �ٸ� ����ü�� ���������Ƿ� �ٸ��� pop�ϸ� ����
                open_num = pop(&count);
                if ((open_ch == '(' && ch != ')') || (open_ch == '[' && ch != ']') || (open_ch == '{' && ch != '}')) {      //���� �ٸ� ¦�� ���� ���� ��ȣ�� ������ ����
                    printf("\n��ȣ�� ������ ���� �ʽ��ϴ�.\n");
                    return 0;
                }
                printf("%d ", open_num);
                break;
            }
        }
    }
    if (!is_empty(&s)) {
        return 0;
    }
}

void countChar(stackType* s, char a[]) {
    char ch;
    int len = strlen(a);
    int count = 0;
    for (int i = 0; i <= len; i++) {
        ch = tolower(a[i]);
        if (is_empty(s) || ch == peek(s)) {
            count++;
            push(s, ch);
        }
        else if (ch != peek(s)) {
            printf("%d%c", count, peek(s));
            count = 0;
            push(s, ch);
            count++;
        }
    }
}

void change(char* a, int* len) {
    int i = 0;
    while (*a != '\0') {
        if ((!(*a >= 'a' && *a <= 'z')) && (!(*a >= 'A' && *a <= 'Z'))) {
            strcpy(a, a + 1);                                                       //���ĺ��� �ƴ� ��� Ư�����ڿ� ������ ���� ����
            (*len)--;                                                               //��ĭ �پ����� len�� ��ĭ �پ����.
        }
        else {
            if (a[i] >= 'A' && a[i] <= 'Z') {
                a[i] = a[i] + 32;
            }
            i++;
            a++;                                                                    //���ĺ��̶�� �������� �ּڰ��� �׳� �Ѿ.
        }
    }
}

void Return_1(stackType* s, char a[]) {
    int len = strlen(a);
    for (int i = 0; i < len; i++) {
        if ((!(a[i] >= 'a' && a[i] <= 'z')) && (!(a[i] >= 'A' && *a <= 'Z'))) {     //���ĺ� �ܿ� Ư�����ڰ� ������ �����.
            change(a, &len);
        }
        if (is_full(s)) {
            printf("��ȭ�����Դϴ�.");
            return 0;
        }
        else {
            push(s, a[i]);                                        //�ҹ��� ��ȯ / ����andƯ������ ����⸦ ��� ���������� push
        }
    }
    char openCh;
    for (int i = 0; i < len / 2; i++) {                         //����ڰ� �Է��� a�迭�� �հ� ���ÿ� ������ �޺κи� ���ϸ� ��
        openCh = pop(s);
        if (openCh != a[i]) {                                   //���� �ٸ��ٸ� ȸ���� �ƴ�.
            printf("�Է��Ͻ� �ܾ�� ȸ���� �ƴմϴ�.");         //¦���� Ȧ�����̴� ������� ������ Ȧ������ ���ڴ� ����� �����ϰ� �翷���� ȸ�������� �����.
            return 0;
        }
    }
    printf("�Է��Ͻ� �ܾ�� ȸ���Դϴ�.");
}

void evaluate(char* str) {
    stackType s;
    int op1, op2;
    int len = strlen(str), value;
    char ch;
    initStack(&s);
    for (int i = 0; i < len; i++) {								//������ �̿��� ���� ģ ������ ���̸�ŭ ��
        ch = str[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '^' && ch != '>' && ch != '<' && ch != '&' && ch != '|') {
            value = ch - 48;											//�ƽ�Ű�ڵ� �������� ���ڴ� int������ ��ȯ��Ŵ
            push(&s, value);
            printf("push : %d\n", value);
        }
        else if (ch == '^') {
            int sum = 0;
            if (is_empty(&s)) {											//����Ȯ��
                printf("\n������ �����Դϴ�.\n\n");
                return;
            }
            else {														//���� ������ �ƴ϶�� pop���� ���� ��������
                op2 = pop(&s);
                printf("pop : %d\n", op2);
            }
            if (is_empty(&s)) {
                printf("\n������ �����Դϴ�.\n\n");
                return;
            }
            else {														//�� �����ִ� ���� �ѹ� �� pop���� ��������
                op1 = pop(&s);
                printf("pop : %d\n", op1);
            }
            sum = pow(op1, op2);										//power�Լ��� ���� ����
            push(&s, sum);
            printf("%d^%d ����� push : %d\n", op1, op2, sum);
        }
        else {
            if (is_empty(&s)) {
                printf("\n������ �����Դϴ�.\n\n");
                return;
            }
            else {
                op2 = pop(&s);
                printf("pop : %d\n", op2);
            }
            if (is_empty(&s)) {
                printf("\n������ ���� �Դϴ�.\n\n");
                return;
            }
            else {
                op1 = pop(&s);
                printf("pop : %d\n", op1);
            }
            switch (ch) {															//���⼭���� ��ǻ�Ͱ� �˾Ƽ� �����Ҽ� �ִ� ��ȣ���̱� ������ case�� ����
            case'+':
                push(&s, op1 + op2);
                printf("%d+%d ����� push : %d\n", op1, op2, op1 + op2);
                break;
            case'-': {
                push(&s, op1 - op2);
                printf("%d-%d ����� push %d\n", op1, op2, op1 - op2);
                break;
            }
            case'*': {
                push(&s, op1 * op2);
                printf("%d*%d ����� push %d\n", op1, op2, op1 * op2);
                break;
            }
            case'/': {
                push(&s, op1 / op2);
                printf("%d/%d ����� push %d\n", op1, op2, op1 / op2);
                break;
            }
            case'%': {
                push(&s, op1 % op2);
                printf("%d%%d ����� push %d\n", op1, op2, op1 % op2);
                break;
            }
            case'&': {
                push(&s, op1 && op2);
                printf("%d&%d ����� push %d\n", op1, op2, op1 && op2);
                break;
            }
            case'|': {
                push(&s, op1 || op2);
                printf("%d|%d ����� push %d\n", op1, op2, op1 || op2);
                break;
            }
            case '<': {
                push(&s, op1 < op2);
                printf("%d<%d ����� push %d\n", op1, op2, op1 < op2);
            }
            case '>': {
                push(&s, op1 < op2);
                printf("%d>%d ����� push %d\n", op1, op2, op1 > op2);
            }
            }
        }
    }
    int result = pop(&s);
    printf("\n����� : %d\n", result);
    return;
}

int main(void) {
    char a[100];
    while (1) {
        int q;
        printf("\n\n������ ���η��� �Է��Ͻÿ� :\n0.���α׷�����.\n1.��ȣ���� ���α׷�\n2.�����̾��� ���α׷�\n3.ȸ���Ǻ� ���α׷�\n4.����ǥ������ : ");
        scanf("%d", &q);
        switch (q)
        {
        case 0: {
            printf("���α׷��� �����մϴ�.");
            return 0;
        }
        case 1: {
            printf("��ȣ�� ���Ե� ������ �Է��Ͻÿ� : ");
            scanf("%s", a);
            printf("��ȣ��ȣ : ");
            check_matching(a);
            break;
        }
        case 2: {
            char a[100];
            printf("������ ���ĺ��� �ۼ��Ͻÿ� : ");
            scanf("%s", a);
            printf("���� : ");
            stackType s;
            initStack(&s);
            countChar(&s, a);
            break;
        }
        case 3: {
            char a[100];
            printf("�ܾ �Է��Ͻÿ� : ");
            getchar();
            scanf("%[^\n]", a);                             //������ �޾ƿ��� ���� scan
            stackType s;
            initStack(&s);
            Return_1(&s, a);
            return 0;
            break;
        }
        case 4: {
            char str[MAX_STACK_SIZE];
            printf("����ǥ����� �Է��Ͻÿ� : ");
            scanf("%s", str);
            evaluate(str);
            break;
        }
        default:
            break;
        }
        
    }
    return 0;
}