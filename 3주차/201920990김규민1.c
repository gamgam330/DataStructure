#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_DEGREE 101

typedef struct {
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_DEGREE];
int num;

polynomial inputpoly1(void);
int xsum(polynomial a, int x);
// 두개의 정수를 비교
char compare(int a, int b)
{
    if (a > b) return '>';
    else if (a == b) return '=';
    else return '<';
}

// 새로운 항을 다항식에 추가한다.
void attach(float coef, int expon)
{
    if (num > MAX_DEGREE) {
        fprintf(stderr, "항의 개수가 너무 많음\n");
        exit(1);
    }
    terms[num].coef = coef;
    terms[num].expon = expon;
    num++;
}
// C = A + B
void poly_add2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce)
{
    float tempcoef;
    *Cs = num;
    while (As <= Ae && Bs <= Be)
        switch (compare(terms[As].expon, terms[Bs].expon)) {
        case '>': // A의 차수 > B의 차수
            attach(terms[As].coef, terms[As].expon);
            As++; break;
        case '=': // A의 차수 == B의 차수
            tempcoef = terms[As].coef - terms[Bs].coef;
            if (tempcoef)
                attach(tempcoef, terms[As].expon);
            As++; Bs++; break;
        case '<': // A의 차수 < B의 차수
            attach(-1 * (terms[Bs].coef), (terms[Bs].expon));
            Bs++; break;
        }
    // A의 나머지 항들을 이동함
    for (; As <= Ae; As++)
        attach(terms[As].coef, terms[As].expon);
    // B의 나머지 항들을 이동함
    for (; Bs <= Be; Bs++)
        attach(-1 * (terms[Bs].coef), terms[Bs].expon);
    *Ce = num;
}


void print_poly(int s, int e)
{
    for (int i = s; i < e; i++)
        if (terms[i].coef > 0) {
            printf("+%3.1fx^%d ", terms[i].coef, terms[i].expon);
        }
        else {
            printf("%3.1fx^%d", terms[i].coef, terms[i].expon);
        }
    if (terms[e].coef > 0.0) {
        printf("+%3.1fx^%d \n", terms[e].coef, terms[e].expon);
    }
    else if(terms[e].coef < 0.0)
        printf("%3.1fx^%d \n", terms[e].coef, terms[e].expon);
}
//
polynomial inputpoly(int As, int Ae, int Bs, int Be) {
    polynomial p;

    for (int i = As; i <= Be; i++) {
        num++;
    }
    printf("항의 길이는 %d 입니다. \n", num);
    for (int i = As; i <= Ae; i++) {
        printf("첫 번째 다항식의 %d번째 항의 계수와 지수를 입력하시오 : ", i + 1);
        scanf("%f %d", &p.coef, &p.expon);
        terms[i] = p;
    }
    for (int i = Bs; i <= Be; i++) {
        printf("두 번째 다항식의 %d번째 항의 계수와 지수를 입력하시오 : ", i + 1);
        scanf("%f %d", &p.coef, &p.expon);
        terms[i] = p;
    }
}



int main(void) {
    while (1) {
        int n;
        printf("\n0. 프로그램종료\n1. 다항식 프로그램 3-3\n2. 다항식 계산 프로그램\n실행할 프로그램의 번호를 입력하시오. : ");
        scanf("%d", &n);
        switch (n) {
        case 0: {
            printf("프로그램을 종료합니다.");
            return 0;
        }
        case 1: {

            int As1, Bs1;
            int As = 0, Ae = 0, Bs, Be, Cs, Ce;
            printf("첫 번째 다항식의 항의 갯수를 입력하시오 : ");
            scanf("%d", &As1);
            printf("두 번째 다항식의 항의 갯수를 입력하시오 : ");
            scanf("%d", &Bs1);
            for (int i = 0; i < As1; i++) {
                Ae++;
            }
            Ae -= 1;
            Bs = (Ae + 1);
            Be = Bs;
            for (int i = 0; i < Bs1; i++) {
                Be++;
            }
            Be -= 1;
            inputpoly(As, Ae, Bs, Be);
            poly_add2(As, Ae, Bs, Be, &Cs, &Ce);
            print_poly(As, Ae);
            print_poly(Bs, Be);
            printf("-----------------------------------------------------------------------------\n");
            print_poly(Cs, Ce);

            break;
        }
        case 2: {
            polynomial a;
            int x;
            float sum;
            a = inputpoly1();
            printf("x의 값을 입력하시오 :");
            scanf("%d", &x);

            sum = xsum(a, x);
            printf("A(%d) = %3.1f\n\n", x, sum);

            break;
        }
        }
    }
}

polynomial inputpoly1(void) {
    polynomial p;

    printf("계수가 0이 아닌 항의 갯수를 입력하시오 : ");
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        printf("%d번째 항의 계수와 지수를 입력하시오 : ", i + 1);
        scanf("%f %d", &p.coef, &p.expon);
        if (p.coef == 0) {
            printf("계수가 0인항을 입력하지 마십시오.\n");
            break;
        }
        else {
            terms[i] = p;
        }
    }
    for (int i = 0; i < num; i++) {                                             //굳이 안해줘도되긴한데 그냥 해주면 좋은거임.. 버블정렬
        for (int j = 0; j < num - 1; j++) {
            if (terms[j].expon < terms[j + 1].expon) {
                polynomial tem = terms[j];
                terms[j] = terms[j + 1];
                terms[j + 1] = tem;
            }
        }
    }
    printf("A(x) = ");
    for (int i = 0; i < num - 1; i++) {
        printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);                     //이건 상수항도 숫자에 포함되는거라 그냥...... num-1까지 돌려야함
    }
    printf("%3.1fx^%d\n", terms[num - 1].coef, terms[num - 1].expon);
}

int xsum(polynomial a, int x) {
    float sum = 1.0;
    float sum2 = 0;

    for (int i = 0; i <= num; i++) {
        int y = terms[i].expon;                     //여기서 헷갈리면 안되는게 temp[i].expon은 지수를 가진 변수기 때문에 이건 전문제처럼 변수가 불규칙적일수가있어서 포문안에서 y값 다시 초기화 해야함
        for (int j = 0; j < y; j++) {
            sum *= x;
        }
        sum2 += (sum * terms[i].coef);               //여긴 전이랑 동일!
        sum = 1.0;
    }
    return sum2;
}