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
		printf("0 : 프로그램 종료 \n1 : 문자열 정수형변환 프로그램 \n2 : 가장 먼 점 구하기 \n3 : 생년월일 구하기 \n4 : 두 정수 사이 합\n0 ~ 4번 중 선택하세요 : ");
		scanf("%d", &num);
		switch (num) {

		case 0: {
			printf("프로그램 종료.");
			return 0;
		}
		case 1: {
			char voca[10];
			printf("문자열 숫자를 입력하시오 : ");
			scanf("%s", voca);
			printf("int형 값 : %d \n\n", Number(voca));
			break;
		}
		case 2: {
			Point pos[5];
			for (int i = 0; i < 5; i++) {
				printf("%d번째 X좌표와 Y좌표 입력: ", i + 1);
				scanf("%d %d", &pos[i].xpos, &pos[i].ypos);
			}
			int result = Sum(pos);
			printf("원점에서부터 제일 먼 좌표는 %d %d입니다.\n\n", pos[result].xpos, pos[result].ypos);
			break;
		}
		case 3: {

			int birth_b;
			char* birth[10] = { "990330", "000330", "981100", "990100", "970510", "001210", "000430", "010210", "020610", "030710" };
			birth_b = (Birth_A(&birth));
			printf("%d 명입니다. \n\n", birth_b);
			break;
		}
		case 4: {

			int m, n;
			printf("m과 n값을 입력하시오 (단, m < n이여야함) : ");
			scanf("%d %d", &m, &n);

			if (m > n) {
				return 0;
			}

			printf("반복문을 이용한 m~n값의 합 : %d \n", FirstSum(m, n));
			printf("순환호출을 이용한 m~n값의 합 : %d \n\n", SecondSum(m, n));
			break;
		}
		}
	}
}

int Number(char* voca) {			// 첫번째 문제 코드 
	int lenth = strlen(voca);
	int sum = 0;
	int Sum[100] = { 1 };
	int result = 1;
	int Result = 0;
	if (voca[0] == '-') {										//pow함수를 쓴 경우
		for (int i = 1; i < lenth; i++) {
			sum += ((pow(10, lenth - 1 - i) * (voca[i] - 48)));
		}
		return -1 * sum;
	}
	else {														//pow함수를 쓰지않은 경우
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

double Sum(Point* pos) {				//두 번째 문제 코드
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

int Birth_A(char* birth[10]) {			//세 번째 문제 코드
	int birth_a[10];
	int month;
	int month_a = 0;
	int count = 0;

	for (int i = 0; i < 10; i++) {
		birth_a[i] = atoi(birth[i]);
	}

	printf("원하는 월을 입력하세요 : ");
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

int FirstSum(int m, int n) {			//네 번째 문제 코드
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

/*#define _CRT_SECURE_NO_WARNINGS			//1-3번 문제 문자열 풀이(미완성)
#include <stdio.h>
#include <string.h>
#include <math.h>

int cal(char** cal, char m);
int main(void) {
	char* birth[10] = { "990330", "000330", "981100", "990100","970510","001210","000430","010210","020610","030710" };
	char m[2];
	int result = 0;

	printf("구하고자 하는 월을 입력하세요. (1~12월까지 입력) : ");
	gets(&m);

	if (m < "1" && m > "12") {
		return 0;
	}

	result = cal(&birth, m);
	printf("%s월생의 수는 : %s", m, result);
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