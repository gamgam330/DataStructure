#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101

typedef struct { // ���׽� ����ü Ÿ�� ����
    int degree; // ���׽��� ����
    float coef[MAX_DEGREE]; // ���׽��� ���
} polynomial;
// C = A+B ���⼭ A�� B�� ���׽��̴�. ����ü�� ��ȯ�ȴ�.

polynomial inputploy(void);
int xsum(polynomial a, int x);


polynomial poly_add1(polynomial A, polynomial B)
{
    polynomial C; // ��� ���׽�
    int Apos = 0, Bpos = 0, Cpos = 0; // �迭 �ε��� ����
    int degree_a = A.degree;
    int degree_b = B.degree;
    C.degree = MAX(A.degree, B.degree);// ��� ���׽� ����
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
        if (degree_a > degree_b) {  // A�� > B��
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        }
        else if (degree_a == degree_b) {  // A�� == B��
            C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
            degree_a--; degree_b--;
        }
        else { // B�� > A��
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
    printf("���׽� �ְ������� ������ �Է��Ͻÿ� : ");
    scanf("%d", &p.degree);
    for (int i = 0; i <= p.degree; i++) {
        printf("%d��° ���� ����� �Է��ϼ��� : ", i + 1);
        scanf("%f", &p.coef[i]);
    }
    return p;
}

// ���Լ�
int main(void)
{
    while (1) {
        int n;
        printf("\n0. ���α׷�����\n1. ���׽� ���α׷� 3-2\n2. ���׽� ��� ���α׷�\n������ ���α׷��� ��ȣ�� �Է��Ͻÿ�. : ");
        scanf("%d", &n);
        switch (n) {
        case 0: {
            printf("���α׷��� �����մϴ�.");
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
            int dgree = a.degree;                    //���� ������ ������� �س���, ������ ū������ �� ����ϱ� ������ �ΰ��� �����ذ���
            printf("X�� ���� �Է��Ͻÿ� :");
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
        y--;                                                //y�� ������쿡�� �����ε� �̰� �����Ҷ� �ߴ���ó�� 0���׵� �� �ᵵ�Ǵϱ� --�� ��~~~~ 0���� ���������
        sum2 += (sum * a.coef[i]);
        sum = 1.0;                                          //�̰� for����ø���� �ʱ�ȭ �����ָ� �� ��� �þ��.
    }
    return sum2;
}