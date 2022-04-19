#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 10
#define MAX_STACK_SIZE 100

typedef struct {
    int r;
    int c;
} element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType* s) {
    s->top = -1;
}

int is_empty(StackType* s) {
    return (s->top == -1);
}

int is_full(StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "�� �ٸ� ���� �����ϴ�.\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

element here = { 1, 0 };
char maze[MAZE_SIZE][MAZE_SIZE] = {
   { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
   { 'e', '0', '0', '0', '0', '1', '1', '1', '1', '1'},
   { '1', '0', '0', '0', '0', '1', '1', '1', '1', '1'},
   { '1', '0', '1', '0', '0', '0', '0', '0', '0', 'x'},
   { '1', '0', '1', '0', '0', '1', '1', '1', '1', '0'},
   { '1', '1', '1', '1', '0', '0', '0', '0', '0', '0'},
   { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
   { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
   { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
   { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

// ��ġ�� ���ÿ� ����
void push_loc(StackType* s, int r, int c)
{
    if (r < 0 || c < 0) {                                              //row�� col���� �����̸� �迭�� �������.
        return;
    }
    if (maze[r][c] != '1' && maze[r][c] != '.') {                      //���� ��ġ�� 1�� .�� �ƴҶ� �� ��ǥ�� push
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }

}

//�̷θ� ȭ�鿡 ���
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {                           //���� �ƽ� ������ ��ŭ ������ ������ø����
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    element ro[MAX_STACK_SIZE];
    int r, c, cnt = 0;
    StackType s;
    init_stack(&s);;

    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;
        maze[r][c] = '.';
        ro[cnt].r = r;
        ro[cnt++].c = c;
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);                         //�����¿� Ȯ��
        if (is_empty(&s)) {                             //���� �Ա��� ã���� ������ �����̶�� ����
            printf("����\n");
            return 0;
        }
        else
            here = pop(&s);                             //������ �ƴ϶�� pop���� ���� ��ǥ�� �̵�
    }
    for (int i = 0; i < cnt; i++) {
        printf("��� : %d, %d \n", ro[i].r, ro[i].c);
    }
    printf("\n�� ��θ� ���� ��ã�� ����\n");
    cnt = 0;

    if (!is_empty(&s)) {
        here = pop(&s);
        while (maze[here.r][here.c] != 'x') {
            r = here.r;                                 //���� row�� r�� ����
            c = here.c;                                 //���� col�� c�� ����
            if (maze[r][c] == '.') {                    //�̹� ������ ��θ� �����ٸ� �پ�ѱ�
                if (!is_empty(&s)) {                    //������ �ƴ϶�� �ϳ� �� ������ �پ�ѱ�
                    pop(&s);
                }
                else {                                  //�����̶�� ��� ����ϰ� �ٸ��� ���°����� ��
                    for (int i = 0; i < cnt; i++) {
                        printf("��� : %d, %d \n", ro[i].r, ro[i].c);
                    }
                    printf("�� �ٸ� ���� �����ϴ�.\n\n");
                    return 0;
                }
            }
            else {                                      //���� ������ ���� �ƴ϶��
                maze[r][c] = '.';                       //��� ������ �濡 . ����
                ro[cnt].r = r;                          //ro������ ��θ� ����ϱ� ���� ����
                ro[cnt++].c = c;
                maze_print(maze);
                push_loc(&s, r - 1, c);
                push_loc(&s, r + 1, c);
                push_loc(&s, r, c - 1);
                push_loc(&s, r, c + 1);                 //������ġ���� �����¿츦 Ȯ�������� 1�̳� .�� �ƴϸ� push
                if (is_empty(&s)) {                     //�Ա��� ã�� ���ϰ� ������ �����̸� ���� ���̻� ���°��� ��
                    printf("�� ���� ���� �����ϴ�.\n");
                    return 0;
                }
                else {                                  //������ ������ �ƴ϶�� ���þȿ� ���� ���� ��ǥ�� �ҷ���.
                    here = pop(&s);
                }

            }
        }
        for (int i = 0; i < cnt; i++) {                 //�ⱸ�� ã�� x�� ������ while���� Ż���ϰ� ��� ���
            printf("��� : %d, %d \n", ro[i].r, ro[i].c);
        }
        printf("\n�� �ٸ� ���� �ֽ��ϴ�.\n");
    }
    else {
        for (int i = 0; i < cnt; i++) {
            printf("��� : %d, %d \n", ro[i].r, ro[i].c);
        }
        printf("�� �ٸ� ���� �����ϴ�.");
    }
}