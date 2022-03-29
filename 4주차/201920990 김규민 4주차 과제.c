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

    printf("A행렬출력 : \n");
    matrix_print(RA);
    printf("B행렬출력 : \n");
    matrix_print(RB);
    printf("C행렬출력 : \n");
    matrix_print(RC);

    while (1) {
        printf("0. 프로그램 종료\n1. A+B 행렬 출력\n2. A+C행렬 출력\n3. B+C행렬 출력\n사용할 프로그램의 번호를 입력하시오 : ");
        scanf("%d", &num);

        switch (num) {
        case 0: {
            printf("프로그램을 종료합니다.");
            return 0;
        }
        case 1: {
            printf("A+B 행렬 출력 : \n");
            result = matrix_add(RA, RB);
            matrix_print(result);
            break;
        }
        case 2: {
            printf("A+C 행렬 출력 : \n");
            result = matrix_add(RA, RC);
            matrix_print(result);
            break;
        }
        case 3: {
            printf("B+C 행렬 출력 : \n");
            result = matrix_add(RB, RC);
            matrix_print(result);
            break;
        }
            /*sparseMatrix change;
            change = change1(RA);
            printf("A 전치행렬 출력 : \n");
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
            if ((i == a.data[num].row) && (j == a.data[num].col)) {            //이거 만약에 희소행렬 행이랑 열값같은게 들어있으면 value값 출력이고
                printf("%3d ", a.data[num].value);
                num++;
            }
            else
                printf("%3d ", n);                                       //아니면 0출력하는거고
        }
        printf("\n");
    }
    printf("\n");
}

sparseMatrix matrix(int a[][10], int row, int col) {         //희소행렬 만드는 함수
    sparseMatrix b;

    b.rows = row;
    b.cols = col;

    int cnt = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (a[i][j] != 0) {
                b.data[cnt].row = i;            //n이 row값... j이 col값... 헷갈리지 말자
                b.data[cnt].col = j;
                b.data[cnt].value = a[i][j];
                cnt++;                              //저장될때마다 cnt++해서 인덱스값 넘겨주기
            }
        }
    }

    b.terms = cnt;                           //cnt넘겨준 만큼이 희소행렬의 terms값이라 저장해주는거고
    return b;
}

sparseMatrix change1(sparseMatrix a) {         //이거 전치행렬!! 제일 고생한거
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
    three1 = three + two + one + zero;      //이거 누적시켜야함 누적 안시키면 중복됨....
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
            tem.data[three1++].value = a.data[qwer].value;      //이렇게 각 숫자 나올때마다 한번 훑은거 가지고 걍 넣으면됨.
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
        matrix_a = (a.data[ca].row * a.cols) + a.data[ca].col;      //이안에 희소행렬 들어가있음.
        matrix_b = (b.data[cb].row * b.cols) + b.data[cb].col;      //얘 곱하기 없으면 만~~약에 1,0이랑 0,1있어봐.. 중복이라 둘이 더하고 난리남.....

        if (matrix_a < matrix_b) {                                        //cols를 곱해주는 이유 = 인덱스값
            c.data[cc++] = a.data[ca++];                     //그래서 얘는 b행렬의 첫번째 희소행렬의 자릿수가 클때는 작은 a의 행렬부터 집어넣으면 됨~
        }
        else if (matrix_a == matrix_b) {                           //만약에 자릿수 같으면 더해야 하는데 만약에 둘이 더해서 0이면 어차피 print에서 0으로 출력하니까... 걍 ㄱㄱ
            if (a.data[ca].value + b.data[cb].value == 0) {
                ca++; cb++;
            }
            else {                                       //이건 더하는거
                c.data[cc].row = a.data[ca].row;
                c.data[cc].col = a.data[ca].col;
                c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
            }
        }
        else                                          //이건 걍if문 떨어져 나온거니까 적어둘 필요없고
            c.data[cc++] = b.data[cb++];
    }
    while (ca < a.terms) {                                 //이거 나머지 행렬 뒤에 붙이는거
        c.data[cc++] = a.data[ca++];
    }
    while (cb < b.terms) {
        c.data[cc++] = b.data[cb++];
    }
    c.terms = cc;
    return c;
}