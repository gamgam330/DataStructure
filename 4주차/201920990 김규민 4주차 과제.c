#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_TERMS 100

typedef struct {
    int row;
    int col;
    int value;
} element;

typedef struct sparseMatrix {
    element data[MAX_TERMS];
    int rows;
    int cols;
    int terms;
} sparseMatrix;

void matrix_print(sparseMatrix a);
sparseMatrix matrix(int a[][10], int row, int col);
sparseMatrix change1(sparseMatrix a);
sparseMatrix matrix_add(sparseMatrix a, sparseMatrix b);

int main(void) {

    int A[8][10] = { { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
                     { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
                     { 0, 0, 0, 0, 0, 0, 0,-3, 0, 0 },
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                     { 0,-1, 0, 0, 0, 0, 0, 0, 0, 0 },
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
    int Ar = 8; int Ac = 10;

    int B[8][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0,-1, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 } };
    int Br = 8; int Bc = 10;

    int C[8][10] = { { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
                     { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                     { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                     { 0, 0, 0, 0, 0, 0, 4, 0, 0, 0 } };
    int Cr = 8; int Cc = 10;

    sparseMatrix RA, RB, RC, result;
    int cnt = 0;
    int num;
    RA = matrix(A, Ar, Ac);
    RB = matrix(B, Br, Bc);
    RC = matrix(C, Cr, Cc);

    printf("A������ : \n");
    matrix_print(RA);
    printf("B������ : \n");
    matrix_print(RB);
    printf("C������ : \n");
    matrix_print(RC);

    while (1) {
        printf("0. ���α׷� ����\n1. A+B ��� ���\n2. A+C��� ���\n3. B+C��� ���\n����� ���α׷��� ��ȣ�� �Է��Ͻÿ� : ");
        scanf("%d", &num);

        switch (num) {
        case 0: {
            printf("���α׷��� �����մϴ�.");
            return 0;
        }
        case 1: {
            printf("A+B ��� ��� : \n");
            result = matrix_add(RA, RB);
            matrix_print(result);
            break;
        }
        case 2: {
            printf("A+C ��� ��� : \n");
            result = matrix_add(RA, RC);
            matrix_print(result);
            break;
        }
        case 3: {
            printf("B+C ��� ��� : \n");
            result = matrix_add(RB, RC);
            matrix_print(result);
            break;
        }
            /*sparseMatrix change;
            change = change1(RA);
            printf("A ��ġ��� ��� : \n");
            matrix_print(change);*/
        }
    }
    return 0;
}

void matrix_print(sparseMatrix a) {
    int num = 0;
    int n = 0;

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if ((i == a.data[num].row) && (j == a.data[num].col)) {            //�̰� ���࿡ ������ ���̶� ���������� ��������� value�� ����̰�
                printf("%3d ", a.data[num].value);
                num++;
            }
            else
                printf("%3d ", n);                                       //�ƴϸ� 0����ϴ°Ű�
        }
        printf("\n");
    }
    printf("\n");
}

sparseMatrix matrix(int a[][10], int row, int col) {         //������ ����� �Լ�
    sparseMatrix b;

    b.rows = row;
    b.cols = col;

    int cnt = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (a[i][j] != 0) {
                b.data[cnt].row = i;            //n�� row��... j�� col��... �򰥸��� ����
                b.data[cnt].col = j;
                b.data[cnt].value = a[i][j];
                cnt++;                              //����ɶ����� cnt++�ؼ� �ε����� �Ѱ��ֱ�
            }
        }
    }

    b.terms = cnt;                           //cnt�Ѱ��� ��ŭ�� �������� terms���̶� �������ִ°Ű�
    return b;
}

sparseMatrix change1(sparseMatrix a) {         //�̰� ��ġ���!! ���� ����Ѱ�
    sparseMatrix tem;
    int zero = 0, one = 0, two = 0, three = 0;
    int zero1 = 0, one1 = 0, two1 = 0, three1 = 0;

    for (int i = 0; i < a.terms; i++) {
        if (a.data[i].col == 0) {
            zero++;
        }
        else if (a.data[i].col == 1) {
            one++;
        }
        else if (a.data[i].col == 2) {
            two++;
        }
        else if (a.data[i].col == 3) {
            three++;
        }
    }
    int qwer = 0;
    int j = 0;
    one1 = one + zero;
    two1 = two + one + zero;
    three1 = three + two + one + zero;      //�̰� �������Ѿ��� ���� �Ƚ�Ű�� �ߺ���....
    while (qwer <= a.terms) {
        if (a.data[qwer].col == 0) {
            tem.data[j].col = a.data[qwer].row;
            tem.data[j].row = a.data[qwer].col;
            tem.data[j].value = a.data[qwer].value;
            qwer++; j++;
        }
        else if (a.data[qwer].col == 1) {
            tem.data[zero1].col = a.data[qwer].row;
            tem.data[zero1].row = a.data[qwer].col;
            tem.data[zero1++].value = a.data[qwer].value;
            qwer++;
        }
        else if (a.data[qwer].col == 2) {
            tem.data[one1].col = a.data[qwer].row;
            tem.data[one1].row = a.data[qwer].col;
            tem.data[one1++].value = a.data[qwer].value;
            qwer++;
        }
        else if (a.data[qwer].col == 3) {
            tem.data[two1].col = a.data[qwer].row;
            tem.data[two1].row = a.data[qwer].col;
            tem.data[two1++].value = a.data[qwer].value;
            qwer++;
        }
        else {
            tem.data[three1].col = a.data[qwer].row;
            tem.data[three1].row = a.data[qwer].col;
            tem.data[three1++].value = a.data[qwer].value;      //�̷��� �� ���� ���ö����� �ѹ� ������ ������ �� �������.
            qwer++;
        }
    }
    tem.cols = a.rows;
    tem.rows = a.cols;
    tem.terms = a.terms;
    return tem;
}


sparseMatrix matrix_add(sparseMatrix a, sparseMatrix b) {
    sparseMatrix c;
    int ca = 0, cb = 0, cc = 0;

    c.rows = a.rows;
    c.cols = a.cols;

    while (ca < a.terms && cb < b.terms) {
        int matrix_a, matrix_b;;
        matrix_a = (a.data[ca].row * a.cols) + a.data[ca].col;      //�̾ȿ� ������ ������.
        matrix_b = (b.data[cb].row * b.cols) + b.data[cb].col;      //�� ���ϱ� ������ ��~~�࿡ 1,0�̶� 0,1�־��.. �ߺ��̶� ���� ���ϰ� ������.....

        if (matrix_a < matrix_b) {                                        //cols�� �����ִ� ���� = �ε�����
            c.data[cc++] = a.data[ca++];                     //�׷��� ��� b����� ù��° �������� �ڸ����� Ŭ���� ���� a�� ��ĺ��� ��������� ��~
        }
        else if (matrix_a == matrix_b) {                           //���࿡ �ڸ��� ������ ���ؾ� �ϴµ� ���࿡ ���� ���ؼ� 0�̸� ������ print���� 0���� ����ϴϱ�... �� ����
            if (a.data[ca].value + b.data[cb].value == 0) {
                ca++; cb++;
            }
            else {                                       //�̰� ���ϴ°�
                c.data[cc].row = a.data[ca].row;
                c.data[cc].col = a.data[ca].col;
                c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
            }
        }
        else                                          //�̰� ��if�� ������ ���°Ŵϱ� ����� �ʿ����
            c.data[cc++] = b.data[cb++];
    }
    while (ca < a.terms) {                                 //�̰� ������ ��� �ڿ� ���̴°�
        c.data[cc++] = a.data[ca++];
    }
    while (cb < b.terms) {
        c.data[cc++] = b.data[cb++];
    }
    c.terms = cc;
    return c;
}