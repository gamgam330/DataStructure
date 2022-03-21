#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct point {
	int xpos;
	int ypos;
}Point;

int Number(char* s);
double Sum(Point* pos);
int Birth_A(char* birth[10]);
int FirstSum(int m, int n);
int SecondSum(int m, int n);
int main(void) {
	int num;
	

	while (1) {
		printf("0 : ���α׷� ���� \n1 : ���ڿ� ��������ȯ ���α׷� \n2 : ���� �� �� ���ϱ� \n3 : ������� ���ϱ� \n4 : �� ���� ���� ��\n0 ~ 4�� �� �����ϼ��� : ");
		scanf("%d", &num);
		switch (num) {

		case 0: {
			printf("���α׷� ����.");
			return 0;
		}
		case 1: {
			char voca[10];
			printf("���ڿ� ���ڸ� �Է��Ͻÿ� : ");
			scanf("%s", voca);
			printf("int�� �� : %d \n\n", Number(voca));
			break;
		}
		case 2: {
			Point pos[5];
			for (int i = 0; i < 5; i++) {
				printf("%d��° X��ǥ�� Y��ǥ �Է�: ", i + 1);
				scanf("%d %d", &pos[i].xpos, &pos[i].ypos);
			}
			int result = Sum(pos);
			printf("������������ ���� �� ��ǥ�� %d %d�Դϴ�.\n\n", pos[result].xpos, pos[result].ypos);
			break;
		}
		case 3: {

			int birth_b;
			char* birth[10] = { "990330", "000330", "981100", "990100", "970510", "001210", "000430", "010210", "020610", "030710" };
			birth_b = (Birth_A(&birth));
			printf("%d ���Դϴ�. \n\n", birth_b);
			break;
		}
		case 4: {

			int m, n;
			printf("m�� n���� �Է��Ͻÿ� (��, m < n�̿�����) : ");
			scanf("%d %d", &m, &n);

			if (m > n) {
				return 0;
			}

			printf("�ݺ����� �̿��� m~n���� �� : %d \n", FirstSum(m, n));
			printf("��ȯȣ���� �̿��� m~n���� �� : %d \n\n", SecondSum(m, n));
			break;
		}
		}
	}
}

int Number(char* voca) {			// ù��° ���� �ڵ� 
	int lenth = strlen(voca);
	int sum = 0;
	int Sum[100] = { 1 };
	int result = 1;
	int Result = 0;
	if (voca[0] == '-') {										//pow�Լ��� �� ���
		for (int i = 1; i < lenth; i++) {
			sum += ((pow(10, lenth - 1 - i) * (voca[i] - 48)));
		}
		return -1 * sum;
	}
	else {														//pow�Լ��� �������� ���
		for (int i = 0; i < lenth; i++) {
			for (int j = 0; j < (lenth-i-1); j++) {
				result *= 10;
			}
			Sum[i] = result * (voca[i] - 48);
			result = 1;
		}
		for (int i = 0; i < lenth; i++) {
			Result += Sum[i];
		}
		return Result;
	}
}

double Sum(Point* pos) {				//�� ��° ���� �ڵ�
	double result[5];
	int num = 0;
	int max = 0;
	for (int i = 0; i < 5; i++) {
		result[i] = sqrt((double)(pos[i].xpos * pos[i].xpos) + (pos[i].ypos * pos[i].ypos));
		if (num < result[i]) {
			num = result[i];
			max = i;
		}
	}
	return max;
}

int Birth_A(char* birth[10]) {			//�� ��° ���� �ڵ�
	int birth_a[10];
	int month;
	int month_a = 0;
	int count = 0;

	for (int i = 0; i < 10; i++) {
		birth_a[i] = atoi(birth[i]);
	}

	printf("���ϴ� ���� �Է��ϼ��� : ");
	scanf("%d", &month);

	if (month < 1 || month>12) {
		return 0;
	}

	for (int i = 0; i < 10; i++) {
		month_a = ((birth_a[i] / 100) % 100);
		if (month_a == month) {
			count++;
		}
	}
	return count;
}

int FirstSum(int m, int n) {			//�� ��° ���� �ڵ�
	int sum = 0;

	for (int i = m; i <= n; i++) {
		sum += i;
	}
	return sum;
}

int SecondSum(int m, int n) {
	if (m > n)
		return 0;
	else return m + SecondSum(m + 1, n);
}

/*#define _CRT_SECURE_NO_WARNINGS			//1-3�� ���� ���ڿ� Ǯ��(�̿ϼ�)
#include <stdio.h>
#include <string.h>
#include <math.h>

int cal(char** cal, char m);
int main(void) {
	char* birth[10] = { "990330", "000330", "981100", "990100","970510","001210","000430","010210","020610","030710" };
	char m[2];
	int result = 0;

	printf("���ϰ��� �ϴ� ���� �Է��ϼ���. (1~12������ �Է�) : ");
	gets(&m);

	if (m < "1" && m > "12") {
		return 0;
	}

	result = cal(&birth, m);
	printf("%s������ ���� : %s", m, result);
}

int cal(char** cal, char* m) {
	int count = 0;
	char* tmp[2];
	int ret;

	for (int i = 0; i < 10; i++) {
		for (int j = 2; j < 4; j++) {
			*tmp = cal[i][j];
		}
	}
	for (int i = 0; i < 10; i++) {
		printf("%c", tmp[i]);
		ret = strcmp(*tmp[i], *m);
		if (ret == 0) {
			count++;
		}
	}
	return count;
}*/