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
// �ΰ��� ������ ��
char compare(int a, int b)
{
    if (a > b) return '>';
    else if (a == b) return '=';
    else return '<';
}

// ���ο� ���� ���׽Ŀ� �߰��Ѵ�.
void attach(float coef, int expon)
{
    if (num > MAX_DEGREE) {
        fprintf(stderr, "���� ������ �ʹ� ����\n");
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
        case '>': // A�� ���� > B�� ����
            attach(terms[As].coef, terms[As].expon);
            As++; break;
        case '=': // A�� ���� == B�� ����
            tempcoef = terms[As].coef - terms[Bs].coef;
            if (tempcoef)
                attach(tempcoef, terms[As].expon);
            As++; Bs++; break;
        case '<': // A�� ���� < B�� ����
            attach(-1 * (terms[Bs].coef), (terms[Bs].expon));
            Bs++; break;
        }
    // A�� ������ �׵��� �̵���
    for (; As <= Ae; As++)
        attach(terms[As].coef, terms[As].expon);
    // B�� ������ �׵��� �̵���
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
    printf("���� ���̴� %d �Դϴ�. \n", num);
    for (int i = As; i <= Ae; i++) {
        printf("ù ��° ���׽��� %d��° ���� ����� ������ �Է��Ͻÿ� : ", i + 1);
        scanf("%f %d", &p.coef, &p.expon);
        terms[i] = p;
    }
    for (int i = Bs; i <= Be; i++) {
        printf("�� ��° ���׽��� %d��° ���� ����� ������ �Է��Ͻÿ� : ", i + 1);
        scanf("%f %d", &p.coef, &p.expon);
        terms[i] = p;
    }
}



int main(void) {
    while (1) {
        int n;
        printf("\n0. ���α׷�����\n1. ���׽� ���α׷� 3-3\n2. ���׽� ��� ���α׷�\n������ ���α׷��� ��ȣ�� �Է��Ͻÿ�. : ");
        scanf("%d", &n);
        switch (n) {
        case 0: {
            printf("���α׷��� �����մϴ�.");
            return 0;
        }
        case 1: {

            int As1, Bs1;
            int As = 0, Ae = 0, Bs, Be, Cs, Ce;
            printf("ù ��° ���׽��� ���� ������ �Է��Ͻÿ� : ");
            scanf("%d", &As1);
            printf("�� ��° ���׽��� ���� ������ �Է��Ͻÿ� : ");
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
            printf("x�� ���� �Է��Ͻÿ� :");
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

    printf("����� 0�� �ƴ� ���� ������ �Է��Ͻÿ� : ");
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        printf("%d��° ���� ����� ������ �Է��Ͻÿ� : ", i + 1);
        scanf("%f %d", &p.coef, &p.expon);
        if (p.coef == 0) {
            printf("����� 0������ �Է����� ���ʽÿ�.\n");
            break;
        }
        else {
            terms[i] = p;
        }
    }
    for (int i = 0; i < num; i++) {                                             //���� �����൵�Ǳ��ѵ� �׳� ���ָ� ��������.. ��������
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
        printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);                     //�̰� ����׵� ���ڿ� ���ԵǴ°Ŷ� �׳�...... num-1���� ��������
    }
    printf("%3.1fx^%d\n", terms[num - 1].coef, terms[num - 1].expon);
}

int xsum(polynomial a, int x) {
    float sum = 1.0;
    float sum2 = 0;

    for (int i = 0; i <= num; i++) {
        int y = terms[i].expon;                     //���⼭ �򰥸��� �ȵǴ°� temp[i].expon�� ������ ���� ������ ������ �̰� ������ó�� ������ �ұ�Ģ���ϼ����־ �����ȿ��� y�� �ٽ� �ʱ�ȭ �ؾ���
        for (int j = 0; j < y; j++) {
            sum *= x;
        }
        sum2 += (sum * terms[i].coef);               //���� ���̶� ����!
        sum = 1.0;
    }
    return sum2;
}