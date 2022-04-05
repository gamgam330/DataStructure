/*괄호 검사 프로그램*/

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

void initStack(stackType* s) {         //스택 초기화
    s->top = -1;
}

int is_empty(stackType* s) {         //스택 공백상태 검출
    return (s->top == -1);
}


int is_full(stackType* s) {            //스택 포화상태 검출
    return(s->top == (MAX_STACK_SIZE - 1));
}

void push(stackType* s, element item) {   //스택 삽입
    if (is_full(s)) {
        fprintf(stderr, "스택이 포화상태 입니다.");
        return;
    }
    else {
        s->data[++(s->top)] = item;
    }
}

element pop(stackType* s) {            //스택 삭제
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return;
    }
    else return s->data[(s->top)--];
}

element peek(stackType* s) {            //스택 찾기
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[s->top];
}

void check_matching(const char* a) {
    stackType s, count;
    int len = strlen(a);
    char ch, open_ch;
    int i = 0;  	// n= 문자열의 길이
    int count1 = 0, open_num;
    initStack(&s);
    initStack(&count);               //초기화

    for (int i = 0; i < len; i++) {
        ch = a[i];	// ch = 다음 문자
        switch (ch) {
        case '(':  case '[':    case '{':       //열린 괄호가 나오면 push
            push(&s, ch);                       //괄호와 괄호의 숫자를 다른 구조체에 저장
            push(&count, count1 + 1);
            printf("%d ", count1 + 1);
            count1++;                           //카운트는 계속해서 유지중이기때문에 새로운 괄호가 갑자기 나타나도 번호계산 가능
            break;
        case ')':  case ']':    case '}':       //닫힌 괄호가 나오면 pop
            if (is_empty(&s)) {
                return 0;
            }
            else {
                open_ch = pop(&s);              //괄호와 괄호의 번호를 다른 구조체에 저장했으므로 다르게 pop하며 진행
                open_num = pop(&count);
                if ((open_ch == '(' && ch != ')') || (open_ch == '[' && ch != ']') || (open_ch == '{' && ch != '}')) {      //만약 다른 짝이 맞지 않은 괄호가 나오면 오류
                    printf("\n괄호의 종류가 맞지 않습니다.\n");
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
            strcpy(a, a + 1);                                                       //알파벳이 아닌 모든 특수문자와 공백을 덮어 씌움
            (*len)--;                                                               //한칸 줄었으니 len도 한칸 줄어야함.
        }
        else {
            if (a[i] >= 'A' && a[i] <= 'Z') {
                a[i] = a[i] + 32;
            }
            i++;
            a++;                                                                    //알파벳이라면 포인터의 주솟값을 그냥 넘어감.
        }
    }
}

void Return_1(stackType* s, char a[]) {
    int len = strlen(a);
    for (int i = 0; i < len; i++) {
        if ((!(a[i] >= 'a' && a[i] <= 'z')) && (!(a[i] >= 'A' && *a <= 'Z'))) {     //알파벳 외에 특수문자가 있으면 지우기.
            change(a, &len);
        }
        if (is_full(s)) {
            printf("포화상태입니다.");
            return 0;
        }
        else {
            push(s, a[i]);                                        //소문자 변환 / 공백and특수문자 지우기를 모두 수행했으면 push
        }
    }
    char openCh;
    for (int i = 0; i < len / 2; i++) {                         //사용자가 입력한 a배열의 앞과 스택에 저장한 뒷부분만 비교하면 됨
        openCh = pop(s);
        if (openCh != a[i]) {                                   //만약 다르다면 회문이 아님.
            printf("입력하신 단어는 회문이 아닙니다.");         //짝수와 홀수길이는 상관없음 어차피 홀수길이 문자는 가운데를 제외하고 양옆으로 회문인지만 보면됨.
            return 0;
        }
    }
    printf("입력하신 단어는 회문입니다.");
}

void evaluate(char* str) {
    stackType s;
    int op1, op2;
    int len = strlen(str), value;
    char ch;
    initStack(&s);
    for (int i = 0; i < len; i++) {								//포문을 이용해 내가 친 수식의 길이만큼 돔
        ch = str[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '^' && ch != '>' && ch != '<' && ch != '&' && ch != '|') {
            value = ch - 48;											//아스키코드 뺄셈으로 숫자는 int형으로 변환시킴
            push(&s, value);
            printf("push : %d\n", value);
        }
        else if (ch == '^') {
            int sum = 0;
            if (is_empty(&s)) {											//공백확인
                printf("\n연산자 오류입니다.\n\n");
                return;
            }
            else {														//만약 공백이 아니라면 pop으로 정수 가져오기
                op2 = pop(&s);
                printf("pop : %d\n", op2);
            }
            if (is_empty(&s)) {
                printf("\n연산자 오류입니다.\n\n");
                return;
            }
            else {														//그 전에있는 정수 한번 더 pop으로 가져오기
                op1 = pop(&s);
                printf("pop : %d\n", op1);
            }
            sum = pow(op1, op2);										//power함수를 통해 연산
            push(&s, sum);
            printf("%d^%d 계산결과 push : %d\n", op1, op2, sum);
        }
        else {
            if (is_empty(&s)) {
                printf("\n연산자 오류입니다.\n\n");
                return;
            }
            else {
                op2 = pop(&s);
                printf("pop : %d\n", op2);
            }
            if (is_empty(&s)) {
                printf("\n연산자 오류 입니다.\n\n");
                return;
            }
            else {
                op1 = pop(&s);
                printf("pop : %d\n", op1);
            }
            switch (ch) {															//여기서부턴 컴퓨터가 알아서 연산할수 있는 기호들이기 때문에 case로 연산
            case'+':
                push(&s, op1 + op2);
                printf("%d+%d 계산결과 push : %d\n", op1, op2, op1 + op2);
                break;
            case'-': {
                push(&s, op1 - op2);
                printf("%d-%d 계산결과 push %d\n", op1, op2, op1 - op2);
                break;
            }
            case'*': {
                push(&s, op1 * op2);
                printf("%d*%d 계산결과 push %d\n", op1, op2, op1 * op2);
                break;
            }
            case'/': {
                push(&s, op1 / op2);
                printf("%d/%d 계산결과 push %d\n", op1, op2, op1 / op2);
                break;
            }
            case'%': {
                push(&s, op1 % op2);
                printf("%d%%d 계산결과 push %d\n", op1, op2, op1 % op2);
                break;
            }
            case'&': {
                push(&s, op1 && op2);
                printf("%d&%d 계산결과 push %d\n", op1, op2, op1 && op2);
                break;
            }
            case'|': {
                push(&s, op1 || op2);
                printf("%d|%d 계산결과 push %d\n", op1, op2, op1 || op2);
                break;
            }
            case '<': {
                push(&s, op1 < op2);
                printf("%d<%d 계산결과 push %d\n", op1, op2, op1 < op2);
            }
            case '>': {
                push(&s, op1 < op2);
                printf("%d>%d 계산결과 push %d\n", op1, op2, op1 > op2);
            }
            }
        }
    }
    int result = pop(&s);
    printf("\n결과값 : %d\n", result);
    return;
}

int main(void) {
    char a[100];
    while (1) {
        int q;
        printf("\n\n실행할 프로램을 입력하시오 :\n0.프로그램종료.\n1.괄호순서 프로그램\n2.런길이압축 프로그램\n3.회문판별 프로그램\n4.후위표현계산기 : ");
        scanf("%d", &q);
        switch (q)
        {
        case 0: {
            printf("프로그램을 종료합니다.");
            return 0;
        }
        case 1: {
            printf("괄호가 포함된 수식을 입력하시오 : ");
            scanf("%s", a);
            printf("괄호번호 : ");
            check_matching(a);
            break;
        }
        case 2: {
            char a[100];
            printf("압축할 알파벳을 작성하시오 : ");
            scanf("%s", a);
            printf("압축 : ");
            stackType s;
            initStack(&s);
            countChar(&s, a);
            break;
        }
        case 3: {
            char a[100];
            printf("단어를 입력하시오 : ");
            getchar();
            scanf("%[^\n]", a);                             //공백을 받아오기 위한 scan
            stackType s;
            initStack(&s);
            Return_1(&s, a);
            return 0;
            break;
        }
        case 4: {
            char str[MAX_STACK_SIZE];
            printf("후위표기식을 입력하시오 : ");
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