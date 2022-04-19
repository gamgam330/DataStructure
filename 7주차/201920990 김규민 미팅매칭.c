#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<windows.h>

#define MAX_QUEUE_SIZE 20
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

typedef struct {
    char name[10];
    int number;
} element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType;

// 오류 함수
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);        //모듈러를 활용해 배열의 rear + 1의값이 front와 같다면 full 한칸 비워두는 프로그램임
}

int is_empty(QueueType* q) {
    return (q->rear == q->front);
}

void enqueue(QueueType* q, element item) {
    if (is_full(q)) {
        fprintf(stderr, "큐 포화 에러\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q)) {
        fprintf(stderr, "큐 공백 에러\n");
        return;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element peek(QueueType* q)
{
    if (is_empty(q))
        error("큐가 공백상태입니다");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

// 출력 함수
void queue_print(QueueType* q) {
    printf("QUEUE(front=%d rear=%d) ", q->front, q->rear);
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            //printf("%d | ", q->data[i]);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}

int main(void) {
    QueueType male, female;
    init_queue(&male);
    init_queue(&female);
    int male_num = 1, female_num = 1;
    int count = 0;

    while (count < 100) {
        int gender = rand() % 2;      //gender==0이면 여자 gender==1이면 남자

        if (gender == 0) {            //여자일때
            element tmp;
            tmp.number = female_num++;

            sprintf(tmp.name, "여%d", tmp.number);           //여NUM 을 tmp.name에 tmp.number과 함께 저장 이게 큐에 학생 이름이 입력된다. 라는 조건에 충족

            if (!is_empty(&male)) {                          //만약에 여자가 생성됐는데 남자가 공백이 아니라면 매칭성공 매칭성공 시 큐에서 삭제기때문에 enqueue시킬 필요 없음
                element male_a = dequeue(&male);             //전에 enqueue됐던 남자의 정보를 불러옴
                printf("-----------------------------\n");
                printf("%s 입장 - %s/%s 매칭\n\n", tmp.name, tmp.name, male_a.name);        //현재 여자의 정보와 불러온 남자의 정보를 출력
                printf("여자 : "); queue_print(&female);                                    //여자 큐의 rear과 front값 출력
            }
            else {
                enqueue(&female, tmp);                       //만약 남자가 공백이라면 enqueue 시키고 대기
                printf("-----------------------------\n");
                printf("%s 입장 - 대기\n\n", tmp.name);
                printf("여자 : "); queue_print(&female);
            }
        }
        else if (gender == 1) {
            element tmp;
            tmp.number = male_num++;

            sprintf(tmp.name, "남%d", tmp.number);

            if (!is_empty(&female)) {
                element female_a = dequeue(&female);
                printf("-----------------------------\n");
                printf("%s 입장 - %s/%s 매칭\n\n", tmp.name, tmp.name, female_a.name);
                printf("남자 : "); queue_print(&male);
            }
            else {
                enqueue(&male, tmp);
                printf("-----------------------------\n");
                printf("%s 입장 - 대기\n\n", tmp.name);
                printf("남자 : "); queue_print(&male);
            }
        }
        count++;
        Sleep(150);
    }
    return 0;
}