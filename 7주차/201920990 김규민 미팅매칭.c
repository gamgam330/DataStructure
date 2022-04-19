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

// ���� �Լ�
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);        //��ⷯ�� Ȱ���� �迭�� rear + 1�ǰ��� front�� ���ٸ� full ��ĭ ����δ� ���α׷���
}

int is_empty(QueueType* q) {
    return (q->rear == q->front);
}

void enqueue(QueueType* q, element item) {
    if (is_full(q)) {
        fprintf(stderr, "ť ��ȭ ����\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q)) {
        fprintf(stderr, "ť ���� ����\n");
        return;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element peek(QueueType* q)
{
    if (is_empty(q))
        error("ť�� ��������Դϴ�");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

// ��� �Լ�
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
        int gender = rand() % 2;      //gender==0�̸� ���� gender==1�̸� ����

        if (gender == 0) {            //�����϶�
            element tmp;
            tmp.number = female_num++;

            sprintf(tmp.name, "��%d", tmp.number);           //��NUM �� tmp.name�� tmp.number�� �Բ� ���� �̰� ť�� �л� �̸��� �Էµȴ�. ��� ���ǿ� ����

            if (!is_empty(&male)) {                          //���࿡ ���ڰ� �����ƴµ� ���ڰ� ������ �ƴ϶�� ��Ī���� ��Ī���� �� ť���� �����⶧���� enqueue��ų �ʿ� ����
                element male_a = dequeue(&male);             //���� enqueue�ƴ� ������ ������ �ҷ���
                printf("-----------------------------\n");
                printf("%s ���� - %s/%s ��Ī\n\n", tmp.name, tmp.name, male_a.name);        //���� ������ ������ �ҷ��� ������ ������ ���
                printf("���� : "); queue_print(&female);                                    //���� ť�� rear�� front�� ���
            }
            else {
                enqueue(&female, tmp);                       //���� ���ڰ� �����̶�� enqueue ��Ű�� ���
                printf("-----------------------------\n");
                printf("%s ���� - ���\n\n", tmp.name);
                printf("���� : "); queue_print(&female);
            }
        }
        else if (gender == 1) {
            element tmp;
            tmp.number = male_num++;

            sprintf(tmp.name, "��%d", tmp.number);

            if (!is_empty(&female)) {
                element female_a = dequeue(&female);
                printf("-----------------------------\n");
                printf("%s ���� - %s/%s ��Ī\n\n", tmp.name, tmp.name, female_a.name);
                printf("���� : "); queue_print(&male);
            }
            else {
                enqueue(&male, tmp);
                printf("-----------------------------\n");
                printf("%s ���� - ���\n\n", tmp.name);
                printf("���� : "); queue_print(&male);
            }
        }
        count++;
        Sleep(150);
    }
    return 0;
}