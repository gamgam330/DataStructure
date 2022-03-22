#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101

typedef struct { // 다항식 구조체 타입 선언
    int degree; // 다항식의 차수
    float coef[MAX_DEGREE]; // 다항식의 계수
} polynomial;
// C = A+B 여기서 A와 B는 다항식이다. 구조체가 반환된다.

polynomial inputploy(void);
int xsum(polynomial a, int x);


polynomial poly_add1(polynomial A, polynomial B)
{
    polynomial C; // 결과 다항식
    int Apos = 0, Bpos = 0, Cpos = 0; // 배열 인덱스 변수
    int degree_a = A.degree;
    int degree_b = B.degree;
    C.degree = MAX(A.degree, B.degree);// 결과 다항식 차수
    for (int i = 0; i < C.degree; i++) {
        if ((degree_a == degree_b) && (A.coef[i] == B.coef[i])){
            Apos++;
            Bpos++;
            degree_a--;
            degree_b--;
            C.degree--;
        }
        else {
            break;
        }
    }
    while (Apos <= A.degree && Bpos <= B.degree) {
        if (degree_a > degree_b) {  // A항 > B항
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        }
        else if (degree_a == degree_b) {  // A항 == B항
            C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
            degree_a--; degree_b--;
        }
        else { // B항 > A항
            C.coef[Cpos++] = -B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}

void print_poly(polynomial p)
{
    for (int i = p.degree; i > 0; i--)
        if (p.coef[p.degree - i] > 0) {
            printf("+%3.1fx^%d", p.coef[p.degree - i], i);
        }
        else if(p.coef[p.degree - i] < 0) {
            printf("%3.1fx^%d", p.coef[p.degree - i], i);
        }
    if (p.coef[p.degree] > 0) {
        printf("+%3.1f \n", p.coef[p.degree]);
    }
    else if (p.coef[p.degree] == 0) {
        printf("");
    }
    else
        printf("%3.1f \n", p.coef[p.degree]);
}

polynomial inputpoly1(void) {
    polynomial p;
    printf("다항식 최고차항의 차수를 입력하시오 : ");
    scanf("%d", &p.degree);
    for (int i = 0; i <= p.degree; i++) {
        printf("%d번째 항의 계수를 입력하세요 : ", i + 1);
        scanf("%f", &p.coef[i]);
    }
    return p;
}

// 주함수
int main(void)
{
    while (1) {
        int n;
        printf("\n0. 프로그램종료\n1. 다항식 프로그램 3-2\n2. 다항식 계산 프로그램\n실행할 프로그램의 번호를 입력하시오. : ");
        scanf("%d", &n);
        switch (n) {
        case 0: {
            printf("프로그램을 종료합니다.");
        }
        case 1: {
            polynomial a;
            polynomial b;
            a = inputpoly1();
            b = inputpoly1();
            polynomial c;
            print_poly(a);
            print_poly(b);
            c = poly_add1(a, b);
            printf("-----------------------------------------------------------------------------\n");
            print_poly(c);
            break;
        }
        case 2: {
            polynomial a;
            int x;
            float sum;
            a = inputpoly1();
            int dgree = a.degree;                    //나는 저장을 순서대로 해놨고, 차수는 큰수부터 쭉 써야하기 때문에 두개로 나눠준거임
            printf("X의 값을 입력하시오 :");
            scanf("%d", &x);

            for (int i = 0; i < a.degree; i++) {
                printf("%3.1fx^%d + ", a.coef[i], dgree);
                dgree--;
            }
            printf("%3.1f\n", a.coef[a.degree]);

            sum = xsum(a, x);
            printf("A(%d)=%f\n\n", x, sum);
            break;
        }
        }
    }
}

int xsum(polynomial a, int x) {
    float sum = 1.0;
    float sum2 = 0;
    int y = a.degree;
    for (int i = 0; i <= a.degree; i++) {
        for (int j = 0; j < y; j++) {
            sum *= x;
        }
        y--;                                                //y값 같은경우에는 차수인데 이거 수업할때 했던것처럼 0차항도 걍 써도되니까 --로 쭉~~~~ 0까지 내려가면됨
        sum2 += (sum * a.coef[i]);
        sum = 1.0;                                          //이거 for문중첩에서 초기화 안해주면 값 계속 늘어난다.
    }
    return sum2;
}