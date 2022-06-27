#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS


typedef struct Node {
    char music_name[30];
    char maker_name[30];
    char genre;
    int year;
    struct Node* link;
}Node;

Node* insert_sort(Node* head, char* mn, char * Mn ,char g, int y) {
    Node* tmp = head;
    Node* Newnode = (Node*)malloc(sizeof(Node));
    Newnode->link = NULL;
    strcpy(Newnode->music_name, mn);
    strcpy(Newnode->maker_name, Mn);
    Newnode->genre = g;
    Newnode->year = y;

    if (head == NULL || strcmp(tmp->music_name, Newnode->music_name) >= 0) {
        Newnode->link = head;
        head = Newnode;
        return head;
    }
    else {
        while (tmp != NULL) {
            if (strcmp(tmp->music_name, Newnode->music_name) <= 0) {            //새로운노드가 들어가기 전과 그 다음 노드 두개를 비교함
                if (tmp->link == NULL || strcmp(tmp->link->music_name, Newnode->music_name) >= 0) {   //근데 만약에 NULL값이면 오류남 오류안나게 하려면 NULL값일때 맨 마지막값에 넣게 해야함
                    Newnode->link = tmp->link;                      //전 노드값링크 책에 나온대로 넣으면됨.
                    tmp->link = Newnode;                            //전 노드의 링크값을 현재 노드의 링크로 옮겨주고, 전 노드는 나를 지칭하도록 하면됨.
                    return head;
                }
            }
            tmp = tmp->link;                                        
        }
    }
}

Node* insert_node(Node* head, char* mn, char* Mn, char g, int y) {
    Node* Newnode = (Node*)malloc(sizeof(Node));
    Newnode->link = NULL;
    strcpy(Newnode->music_name, mn);
    strcpy(Newnode->maker_name, Mn);
    Newnode->genre = g;
    Newnode->year = y;
    int num;
    printf("위치를 지정해주세요 : ");
    scanf("%d", &num);
    if (num == 1) {                                                     //사용자가 첫번째에 넣고 싶을때. 제일 처음에 집어 넣는 방법 사용.
        Newnode->link = head;
        head = Newnode;
    }
    else {
        if (head != NULL) {
            Node* tmp = head;
            for (int i = 0; i < num - 2; tmp = tmp->link) {         //사용자가 입력한 전까지 따라가면 사용자가 넣고자하는 전 노드의 값이 나옴.
                i++;                                                //한번 넘어가는게 맞음 head를 받았기 때문에 한번 넘어가면 pre의 정보를 받게됨.
            }
            Newnode->link = tmp->link;                      //마지막값에 방금만든 노드 연결
            tmp->link = Newnode;
        }
        else {
            head = Newnode;                                 //값이 비어서 해드가 방금만든 노드가됨
        }
    }

    return head;
}

void list_length(Node* head) {
    int cnt = 0;
    while (head != NULL) {
        cnt++;
        head = head->link;
    }
    printf("\n리스트노드의 갯수는 :%d개 입니다.\n", cnt);
}

void list_display(Node* head) {
    while (head != NULL) {                              //첫번째 값부터 시작
        printf("\n노래제목 : %s\n", head->music_name);
        printf("\n제작자 이름 : %s\n", head->maker_name);
        printf("\n장르 : %c\n", head->genre);
        printf("\n발표년도 : %d\n", head->year);
        printf("----------------------------");
        head = head->link;
    }
}

int main(void) {
    Node* head = NULL;
    int num, year1;
    char music_name[30], genre1, maker_name[30];
    while (1) {
        printf("\n\n------------------------------------------\n");
        printf("원하는 프로그램의 숫자를 입력하세요.\n0. 프로그램 종료\n1. 음악삽입\n2. 특정위치에 음악 삽입\n3. 리스트 노드 갯수 계산\n4. 음악 출력");
        printf("\n------------------------------------------\n\n");
        scanf("%d", &num);
        switch (num)
        {
        case 0: {
            printf("프로그램을 종료합니다.\n");
            return 0;
        }
        case 1: {
            printf("\n\n------오름차순 노래 삽입------\n\n");
            printf("노래 제목을 입력하세요 : ");
            scanf("%s", music_name);
            getchar();
            printf("제작자 이름을 입력하세요 : ");
            scanf("%s", maker_name);
            getchar();
            printf("발표년도를 입력하세요 : ");
            scanf("%d", &year1);
            getchar();
            printf("장르를 입력하세요(b, c, h, j, t) : ");
            scanf("%c", &genre1);
            getchar();
            head = insert_sort(head, music_name, maker_name, genre1, year1);
            break;
        }
        case 2: {
            printf("\n\n------특정위치 음악 삽입------\n\n");
            printf("노래 제목을 입력하세요 : ");
            scanf("%s", music_name);
            getchar();
            printf("제작자 이름을 입력하세요 : ");
            scanf("%s", maker_name);
            getchar();
            printf("발표년도를 입력하세요 : ");
            scanf("%d", &year1);
            getchar();
            printf("장르를 입력하세요(b, c, h, j, t) : ");
            scanf("%c", &genre1);
            getchar();
            head = insert_node(head, music_name, maker_name, genre1, year1);
            break;
        }
        case 3: {
            printf("\n\n------리스트 노드 갯수 계산------\n\n");
            list_length(head);
            break;
        }
        case 4: {
            printf("\n\n------음악 출력------\n\n");
            list_display(head);
            break;
        }
        default:
            printf("잘못입력하셧습니다.");
            break;
        }
    }
}