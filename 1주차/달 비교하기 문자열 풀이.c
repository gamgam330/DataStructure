#define _CRT_SECURE_NO_WARNINGS			//1-3번 문제 문자열 풀이(완성)
#include <stdio.h>
#include <string.h>
#include <math.h>

int cal(char** cal);
int main(void) {
	char* birth[10] = { "990330", "000330", "981100", "990100","970510","001210","000430","010210","020610","030710" };
	int result = 0;
	result = cal(&birth);
	printf("월생의 수는 : %d", result);
}

int cal(char** cal) {
	int count = 0; 
	char tmp[10][2] = {'0',};
	int ret;
	char m[2];
	printf("구하고자 하는 월을 입력하세요. (1~12월까지 입력) : ");
	scanf("%c%c", &m[0], &m[1]);
	for (int i = 0; i < 10; i++) {
		for (int j = 2; j < 4; j++) {
			tmp[i][j-2] = cal[i][j];
		}
	}
	/*for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%c", tmp[i][j]);
		}
		printf("\n");
	}*/
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 1; j++) {
			if (tmp[i][j] != m[j]) {
				
			}
			else
				if (tmp[i][j + 1] != m[j + 1]) {
					
				}
				else
					count++;
		}
	}
	return count;
}