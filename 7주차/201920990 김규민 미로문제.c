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
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "또 다른 길이 없습니다.\n");
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

// 위치를 스택에 삽입
void push_loc(StackType* s, int r, int c)
{
    if (r < 0 || c < 0) {                                              //row와 col값이 음수이면 배열을 벗어난것임.
        return;
    }
    if (maze[r][c] != '1' && maze[r][c] != '.') {                      //현재 위치가 1과 .이 아닐때 그 좌표를 push
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }

}

//미로를 화면에 출력
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {                           //변수 맥스 사이즈 만큼 돌렸음 포문중첩으로
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
        push_loc(&s, r, c + 1);                         //싱하좌우 확인
        if (is_empty(&s)) {                             //만약 입구를 찾기전 스택이 공백이라면 실패
            printf("실패\n");
            return 0;
        }
        else
            here = pop(&s);                             //공백이 아니라면 pop으로 다음 좌표로 이동
    }
    for (int i = 0; i < cnt; i++) {
        printf("경로 : %d, %d \n", ro[i].r, ro[i].c);
    }
    printf("\n의 경로를 지나 길찾기 성공\n");
    cnt = 0;

    if (!is_empty(&s)) {
        here = pop(&s);
        while (maze[here.r][here.c] != 'x') {
            r = here.r;                                 //현재 row값 r에 대입
            c = here.c;                                 //현재 col값 c에 대입
            if (maze[r][c] == '.') {                    //이미 지나간 경로를 만난다면 뛰어넘기
                if (!is_empty(&s)) {                    //공백이 아니라면 하나 더 팝으로 뛰어넘기
                    pop(&s);
                }
                else {                                  //공백이라면 경로 출력하고 다른길 없는것으로 끝
                    for (int i = 0; i < cnt; i++) {
                        printf("경로 : %d, %d \n", ro[i].r, ro[i].c);
                    }
                    printf("또 다른 길이 없습니다.\n\n");
                    return 0;
                }
            }
            else {                                      //만약 지나간 길이 아니라면
                maze[r][c] = '.';                       //방금 지나간 길에 . 대입
                ro[cnt].r = r;                          //ro변수는 경로를 출력하기 위한 변수
                ro[cnt++].c = c;
                maze_print(maze);
                push_loc(&s, r - 1, c);
                push_loc(&s, r + 1, c);
                push_loc(&s, r, c - 1);
                push_loc(&s, r, c + 1);                 //현재위치에서 상하좌우를 확인했을때 1이나 .이 아니면 push
                if (is_empty(&s)) {                     //입구를 찾지 못하고 스택이 공백이면 길이 더이상 없는것임 끝
                    printf("또 따른 길이 없습니다.\n");
                    return 0;
                }
                else {                                  //스택이 공백이 아니라면 스택안에 값을 현재 좌표로 불러옴.
                    here = pop(&s);
                }

            }
        }
        for (int i = 0; i < cnt; i++) {                 //출구를 찾아 x를 만나면 while문을 탈출하고 경로 출력
            printf("경로 : %d, %d \n", ro[i].r, ro[i].c);
        }
        printf("\n또 다른 길이 있습니다.\n");
    }
    else {
        for (int i = 0; i < cnt; i++) {
            printf("경로 : %d, %d \n", ro[i].r, ro[i].c);
        }
        printf("또 다른 길이 없습니다.");
    }
}