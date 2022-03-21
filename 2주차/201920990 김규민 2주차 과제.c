#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct Complex {
    int x;
    int y;
}complex;

int length(char* s);
int count(char* s, int len, int A, int a, int num, int ca);


int cul1(complex* arr, int i);
int cul2(complex* arr, int i);

int recursion(int* a, int size, int good, int first);


int main(void) {
    int q;
    while (1) {
        printf("1~4�� ������ ���α׷��� ���ڸ� �Է��ϼ��� (��, 0 �Է½� ���α׷� ����):");
        scanf("%d", &q);
        switch (q)
        {
        case 0: {
            printf("���α׷��� �����մϴ�.");
            return 0;
        }
        case 1: {
            char voca[100];
            int len = 0;
            int A = 0;
            int a = 0;
            int num = 0;
            int ca = 0;
            printf("�ܾ� �Է�: ");
            scanf("%s", voca);
            len = length(voca);
            if (len >= 10) {
                printf("���ڿ��� ���̰� 10�� �̻��̰�.\n");
            }
            else {
                printf("���ڿ��� ���̰� 10�� �����Դϴ�.\n");
                return 0;
            }
            count(voca, len, A, a, num, ca);
            break;
        }
        case 2: {
            complex arr[5];
            complex sum;
            sum.x = 0;
            sum.y = 0;
            int i = 5;
            for (int i = 0; i < 5; i++) {
                printf("%d��° ���Ҽ��� �Ǽ�, ��� �Է�: ", i + 1);
                scanf("%d %d", &arr[i].x, &arr[i].y);
            }
            sum.x = cul1(&arr, i);
            sum.y = cul2(&arr, i);
            printf("���Ҽ��� ���� : %d+%di \n", sum.x, sum.y);
            break;
        }
        case 3: {
            char voca[100];
            printf("���ܾ� �Է�: ");
            scanf("%s", voca);
            printf("�Է��� ���ܾ��� ���̴� %d�Դϴ�.\n", length(voca));
            break;
        }
        case 4: {
            int a[20] = { 1,5,8,10,15,20,30,45,47,50,55,57,58,59,61,63,65,67,69,71 };
            int tmp;
            int size = (sizeof(a) / sizeof(int)) - 1;
            int good;
            int first = 0;
            printf("ã���� �ϴ� ���� �Է��ϼ��� : ");
            scanf("%d", &good);
            for (int i = 0; i < 20; i++) {         //����Ž���� ���������̿�����.
                for (int j = 0; j < 19; j++) {
                    if (a[j] > a[j + 1]) {
                        tmp = a[j];
                        a[j] = a[j + 1];
                        a[j + 1] = tmp;
                    }
                }
            }
            int result = recursion(a, size, good, first);
            if (result == -1) {
                printf("ã���� �ϴ� ���� �����ϴ�.");
                return 0;
            }
            else {
                printf("ã�¼��� %d��° �ֽ��ϴ�.\n", result + 1);
            }
            break;
        }
        }
    }

}

int length(char* s) {
    if (*s == '\0')
        return 0;
    return 1 + length(s + 1);
}

int count(char* s, int len, int A, int a, int num, int ca) {
    for (int i = 0; i < len; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            A++;
        else if (s[i] >= 'a' && s[i] <= 'z')
            a++;
        else if (s[i] >= '0' && s[i] <= '9')
            num++;
        else if (s[i] == '!' || s[i] == '?' || s[i] == '*' || s[i] == '#' || s[i] == '$')
            ca++;
        else {
            printf("�ν��� �� ���� ���ڰ� ���ֽ��ϴ�.");
            return 0;
        }
    }
    if (A >= 1 && a >= 1 && num >= 1 && ca >= 1) {
        printf("�빮��, �ҹ���, ����, Ư�����ڰ� ��� ���ԵǾ��ֽ��ϴ�.\n");
    }
    else {
        printf("���ڿ��� �빮�� �ҹ��� ���� Ư������ �� �Ѱ��� ������ �Ǿ� �ֽ��ϴ�.\n");
        return 0;
    }

}

int cul1(complex* arr, int i) {
    if (i <= 0)
        return 0;
    return arr[i - 1].x + cul1(arr, i - 1);
}

int cul2(complex* arr, int i) {
    if (i <= 0)
        return 0;
    return arr[i - 1].y + cul2(arr, i - 1);
}

int recursion(int* a, int size, int good, int first) {
    int mid = (first + size) / 2;
    if (first > size)
        return -1;
    else {
        if (good == a[mid]) {
            return mid;
        }
        else {
            if (good > a[mid]) {
                printf("ã�����ϴ� �� %d�� %d���� Ů�ϴ�.\n ���ʱ����� Ž���ϰڽ��ϴ�.\n\n", good, a[mid]);
                first = mid + 1;
                recursion(a, size, good, first);
            }
            else {
                printf("ã�����ϴ� �� %d�� %d���� �۽��ϴ�.\n �����ʱ����� Ž���ϰڽ��ϴ�.\n\n", good, a[mid]);
                size = mid - 1;
                recursion(a, size, good, first);
            }
        }
    }
}