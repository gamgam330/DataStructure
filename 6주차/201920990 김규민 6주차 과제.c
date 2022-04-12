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

void initStack(StackType* s) {         //스택 초기화
    s->top = -1;
}

int is_empty(StackType* s) {         //스택 공백상태 검출
    return (s->top == -1);
}


int is_full(StackType* s) {            //스택 포화상태 검출
    return(s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, char item) {   //스택 삽입
    if (is_full(s)) {
        fprintf(stderr, "스택이 포화상태 입니다.");
        return;
    }
    else {
        printf("\n%c가 push됩니다.", item);
        s->data[++(s->top)] = item;
    }
}

void push1(StackType* s, int item) {   //스택 삽입
    if (is_full(s)) {
        fprintf(stderr, "스택이 포화상태 입니다.");
        return;
    }
    else {
        s->v[++(s->top)] = item;
    }
}

element pop(StackType* s) {            //스택 삭제
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return;
    }
    else
        printf("\n%c가 pop됩니다.", s->data[(s->top)]);
        return s->data[(s->top)--];
}

int pop1(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return;
    }
    else return s->v[(s->top)--];
}

element peek(StackType* s) {            //스택 찾기
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[s->top];
}
int peek1(StackType* s) {            //스택 찾기
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
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
    }                                                       //우선순위가 먼저인값이 가장 큰 값을 리턴함
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
            while (!is_empty(s) && (prec(ch) <= prec(peek(s)))) {           //방금 불러온게 우선순위가 더 먼저면 그대로 push
                num[k++] = pop(s);                                          //다른 배열에 저장할껀데 pop으로 불러와서 저장후 인덱스값 증가.
            }
            push(s, ch);                                                    //스택에 쌓인 기호의 우선순위가 더 높으면 pop으로 뺴준 후에 현재 기호 push
            break;
        }
        case '(': {
            push(s, ch);                                                    //괄호의 시작
            len1--;                                                         //괄호는 후위표기식에서 삭제되기때문에 len값을 괄호의 갯수만큼 줄이기.
            break;
        }
        case')': {
            op = pop(s);
            len1--;                                                         //닫힌 괄호가 나올때 까지는 위쪽 case에 걸려 우선순위대로 출력됨.
            while (op != '(') {                                         //닫힌 괄호가 나오면 열린괄호가 나올때 까지 스택에 남은 연산자 뽑기.
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
    printf("\n후위표기법 연산식 : ");
    for (int j = 0; j < len1; j++)
        printf("%c", num[j]);
    printf("\n");
    printf("\n======================후위표기식 계산=====================\n");
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
    for (int i = 0; i < len; i++) {                        //포문을 이용해 내가 친 수식의 길이만큼 돔
        ch = str[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '^' && ch != '>' && ch != '<' && ch != '&' && ch != '|') {
            value = ch - '0';                                 //아스키코드 뺄셈으로 숫자는 int형으로 변환시킴
            push1(&s, value);
            printf("%d를 push합니다.\n", value);
        }
        else if (ch == '^') {
            int sum = 0;
            if (is_empty(&s)) {                                 //공백확인
                printf("\n연산자 오류입니다.\n\n");
                return;
            }
            else {                                          //만약 공백이 아니라면 pop으로 정수 가져오기
                op2 = pop1(&s);
                printf("%d를 pop합니다.\n", op2);
            }
            if (is_empty(&s)) {
                printf("\n연산자 오류입니다.\n\n");
                return;
            }
            else {                                          //그 전에있는 정수 한번 더 pop으로 가져오기
                op1 = pop1(&s);
                printf("%d를 pop합니다.\n", op1);
            }
            push1(&s, pow1(op1, op2));                              //power함수를 통해 연산
            printf("%d^%d 계산결과 : %d\n%d를 push합니다.\n", op1, op2, pow1(op1, op2), pow1(op1, op2));
        }
        else {
            if (is_empty(&s)) {
                printf("\n연산자 오류입니다.\n\n");
                return;
            }
            else {
                op2 = pop1(&s);
                printf("%d를 pop합니다.\n", op2);
            }
            if (is_empty(&s)) {
                printf("\n연산자 오류 입니다.\n\n");
                return;
            }
            else {
                op1 = pop1(&s);
                printf("%d를 pop합니다.\n", op1);
            }
            switch (ch) {                                             //여기서부턴 컴퓨터가 알아서 연산할수 있는 기호들이기 때문에 case로 연산
            case'+':
                push1(&s, op1 + op2);
                printf("%d+%d 계산결과 : %d \n%d를 push합니다.\n", op1, op2, op1 + op2, op1 + op2);
                break;
            case'-': {
                push1(&s, op1 - op2);
                printf("%d-%d 계산결과 : %d \n%d를 push합니다.\n", op1, op2, op1 - op2, op1 - op2);
                break;
            }
            case'*': {
                push1(&s, op1 * op2);
                printf("%d*%d 계산결과 : %d \n%d를 push합니다.\n", op1, op2, op1 * op2, op1 * op2);
                break;
            }
            case'/': {
                push1(&s, op1 / op2);
                printf("%d/%d 계산결과 : %d \n%d를 push합니다.\n", op1, op2, op1 / op2, op1 / op2);
                break;
            }
            case'%': {
                push1(&s, op1 % op2);
                printf("%d%c%d 계산결과 : %d\n%d를 push합니다.\n", op1, 37, op2, op1 % op2, op1 % op2);
                break;
            }
            case'&': {
                push1(&s, op1 && op2);
                printf("%d&%d 계산결과 : %d\n%d를 push합니다.\n", op1, op2, op1 && op2, op1 && op2);
                break;
            }
            case'|': {
                push1(&s, op1 || op2);
                printf("%d|%d 계산결과 : %d\n%d를 push합니다.\n", op1, op2, op1 || op2, op1 || op2);
                break;
            }
            case '<': {
                push1(&s, op1 < op2);
                printf("%d<%d 계산결과 : %d\n%d를 push합니다.\n", op1, op2, op1 < op2, op1 < op2);
                break;
            }
            case '>': {
                push1(&s, op1 > op2);
                printf("%d>%d 계산결과 : %d\n%d를 push합니다.\n", op1, op2, op1 > op2, op1 > op2);
                break;
            }
            }
        }
    }
    int result = pop1(&s);
    printf("====================후위표기식 계산완료===================\n");
    printf("\n결과값 : %d\n\n", result);
    return;
}

int main(void) {
    StackType d;
    initStack(&d);
    char cal[MAX_STACK_SIZE];
    int q = 0;
    while (1) {
        printf("0.프로그램 종료.\n1.프로그램 재시작.\n원하는 프로그램의 번호를 입력하시오 : ");
        scanf("%d", &q);
        switch (q) {
            {
        case 0:
            printf("프로그램을 종료합니다.");
            return 0;
            }
        case 1: {
            printf("연산식을 입력하시오 : ");
            scanf("%s", cal);
            postfix(cal, &d);
            break;
        }
        }
    }
}