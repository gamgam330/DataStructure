#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define _CRT_SECURE_NO_WARNINGS


typedef struct Node {
    char music_name[30];
    char maker_name[30];
    char genre;
    int year;
    int play_time;
    struct Node* Rlink;
    struct Node* Llink;
}Node;

void init(Node* head) {
    head->Rlink = head->Llink = head;                                   //이중연결리스트 초기화 (head노드 하나 생성!)
}

Node* insert_sort(Node* head, char* mn, char* Mn, char g, int y, int play_time) {
    Node* tmp = head->Rlink;
    Node* Newnode = (Node*)malloc(sizeof(Node));
    strcpy(Newnode->music_name, mn);
    strcpy(Newnode->maker_name, Mn);
    Newnode->play_time = play_time;
    Newnode->genre = g;
    Newnode->year = y;

    if (tmp == head || strcmp(tmp->music_name, Newnode->music_name) >= 0) {
        Newnode->Llink = head;
        Newnode->Rlink = head->Rlink;
        head->Rlink->Llink = Newnode;
        head->Rlink = Newnode;
        return head;
    }
    else {
        while (tmp != head) {
            if (strcmp(tmp->music_name, Newnode->music_name) <= 0) {                                    //새로운노드가 들어가기 전과 그 다음 노드 두개를 비교함
                if (tmp->Rlink == NULL || strcmp(tmp->Rlink->music_name, Newnode->music_name) >= 0) {   //근데 만약에 NULL값이면 오류남 오류안나게 하려면 NULL값일때 맨 마지막값에 넣게 해야함
                    Newnode->Llink = tmp;                                                               //전 노드값링크 책에 나온대로 넣으면됨.
                    Newnode->Rlink = tmp->Rlink;
                    tmp->Rlink->Llink = Newnode;
                    tmp->Rlink = Newnode;                                                               //전 노드의 링크값을 현재 노드의 링크로 옮겨주고, 전 노드는 나를 지칭하도록 하면됨.
                    return head;
                }
            }
            tmp = tmp->Rlink;
        }
    }
}


void list_length(Node* head) {
    int cnt = 0;
    Node* p = head->Rlink;
    while (p != head) {
        cnt++;
        p = p->Rlink;
    }
    printf("\n리스트노드의 갯수는 :%d개 입니다.\n", cnt);
}

Node* serch_music(Node* head, char* m) {
    Node* p = head->Rlink;
    while (p != head) {
        if (strcmp(p->music_name, m) == 0) {
            return p;
        }
        p = p->Rlink;
    }
    return NULL;
}

void list_display(Node* head) {
    Node* p = head->Rlink;
    if (p == head) {
        printf("리스트가 비었습니다.");
        return;
    }
    else {
        while (p != head) {                              //첫번째 값부터 시작
            printf("\n노래제목 : %s\n", p->music_name);
            printf("\n제작자 이름 : %s\n", p->maker_name);
            printf("\n장르 : %c\n", p->genre);
            printf("\n발표년도 : %d\n", p->year);
            printf("----------------------------");
            p = p->Rlink;
        }
    }
}

Node* remove_music(Node* head) {
    char music_Name[30];
    Node* tmp = head->Rlink;
    printf("삭제할 노래의 제목을 입력하시오. :");
    scanf("%s", music_Name);
    getchar();
    if (head == NULL) {
        printf("삭제할 노래가 없습니다.\n");
        return;
    }
    while (tmp != head) {
        if (strcmp(music_Name, tmp->music_name) == 0) {
            tmp->Llink->Rlink = tmp->Rlink;                                //그림 그려보니 섹션 안나눠도됨. 어차피 해드는 비어있는값이라.
            tmp->Rlink->Llink = tmp->Llink;
            free(tmp);
            return head;
            printf("삭제되었습니다.\n\n");
        }
        tmp = tmp->Rlink;
    }
    printf("입력한 노래가 없습니다.\n");
    return head;
}

void search_recently(Node* head) {
    Node* p = head->Rlink;
    Node* max = head;
    while (p != head) {
        if (p->year > max->year) {
            max = p;
        }
        p = p->Rlink;
    }
    printf("\n가장 최근곡은\n");
    printf("\n노래제목 : %s\n", max->music_name);
    printf("\n제작자 이름 : %s\n", max->maker_name);
    printf("\n장르 : %c\n", max->genre);
    printf("\n발표년도 : %d\n", max->year);
    printf("----------------------------");
}


void search_genre(Node* head) {
    printf("\n탐색할 음악의 장르를 입력하시오:");
    char music_genre;
    Node* p = head->Rlink;
    scanf(" %c", &music_genre);
    getchar();
    while (p != head) {
        if (p->genre == music_genre) {
            printf("\n노래제목 : %s\n", p->music_name);
            printf("\n제작자 이름 : %s\n", p->maker_name);
            printf("\n장르 : %c\n", p->genre);
            printf("\n발표년도 : %d\n", p->year);
            printf("----------------------------");
        }
        p = p->Rlink;
    }
}

void play(Node* cur) {
    int cnt = cur->play_time;                                       //각 곡의 play_time을 cnt 변수에 대입
    printf("%s 재생시작\n", cur->music_name);
    printf("\n제작자 이름 : %s\n", cur->maker_name);
    printf("\n장르 : %c\n", cur->genre);
    printf("\n발표년도 : %d\n", cur->year);
    while (cnt != 0) {                                              //while문을 이용해 cnt변수가 0이 될때까지 sleep 함수를 이용해 딜레이
        printf("%d\n", cnt--);
        Sleep(300);
    }
    printf("%d\n", cnt);                                           //마지막 0출력
}

int main(void) {
    Node* head = (Node*)malloc(sizeof(Node));
    Node* cur = head->Rlink;
    init(head);
    int year1, play_time;
    char num;
    char music_name[30], genre1, maker_name[30];
    while (1) {
        printf("\n\n------------------------------------------\n");
        printf("원하는 프로그램의 숫자를 입력하세요.\n0. 프로그램 종료\n1. 음악삽입\n2. 리스트 노드 갯수 계산\n3. 음악 출력\n");
        printf("4. 음악 삭제\n");
        printf("5. 음악검색\n");
        printf("6. 최신곡\n");
        printf("7. 장르 검색\n");
        printf("f. 첫번째 곡 재생\n");
        printf("l. 마지막 곡 재생\n");
        printf(">. 오른쪽으로 이동\n");
        printf("<. 왼쪽으로 이동\n");
        printf("\n------------------------------------------\n\n");
        scanf("%c", &num);
        switch (num)
        {
        case '0': {
            printf("프로그램을 종료합니다.\n저장된 데이터가 모두 삭제됩니다.");
            free(head);
            return 0;
        }
        case '1': {
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
            printf("노래 길이:");
            scanf("%d", &play_time);
            getchar();
            head = insert_sort(head, music_name, maker_name, genre1, year1, play_time);
            break;
        }
        case '2': {
            printf("\n\n------리스트 노드 갯수 계산------\n\n");
            getchar();
            list_length(head);
            break;
        }
        case '3': {
            printf("\n\n------음악 출력------\n\n");
            getchar();
            list_display(head);
            break;
        }
        case '4': {
            printf("\n\n------음악 삭제------\n\n");
            getchar();
            head = remove_music(head);
            break;
        }
        case '5': {
            char Music[30];
            printf("찾고자하는 음악의 제목을 입력하시오 : ");
            scanf("%s", Music);
            getchar();
            printf("\n\n------음악검색------\n\n");
            Node* boolen = serch_music(head, Music);
            if (boolen == NULL) {
                printf("찾고자 하는 음악이 없습니다.");
            }
            else {
                printf("\n노래제목 : %s\n", boolen->music_name);
                printf("\n제작자 이름 : %s\n", boolen->maker_name);
                printf("\n장르 : %c\n", boolen->genre);
                printf("\n발표년도 : %d\n", boolen->year);
                printf("----------------------------");
            }
            break;
        }
        case '6': {
            printf("\n\n------최신 음악------\n\n");
            getchar();
            search_recently(head);
            break;
        }
        case '7': {
            printf("\n\n------음악 장르 검색------\n\n");
            getchar();
            search_genre(head);
            break;
        }
        case 'f': {
            printf("\n\n------첫 곡 재생------\n\n");
            getchar();
            cur = head->Rlink;                                              //head->Rlink 값이 처음임.
            play(cur);
            break;
        }
        case 'l': {
            printf("\n\n------마지막 곡 재생------\n\n");
            getchar();
            cur = head->Llink;
            play(cur);
            break;
        }
        case '>': {
            printf("\n\n------오른쪽으로 이동------\n\n");
            getchar();
            cur = cur->Rlink;                                               //cur로 해야하는 이유는 누적해서 계속 이동해야하기때문.
            if (cur == head) {
                cur = cur->Rlink;
            }
            play(cur);
            break;
        }
        case '<': {
            printf("\n\n------왼쪽으로 이동------\n\n");
            getchar();
            cur = cur->Llink;
            if (cur == head)
                cur = cur->Llink;
            play(cur);
            break;
        }
        }
    }

}