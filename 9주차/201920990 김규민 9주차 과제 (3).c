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
            if (strcmp(tmp->music_name, Newnode->music_name) <= 0) {            //���ο��尡 ���� ���� �� ���� ��� �ΰ��� ����
                if (tmp->link == NULL || strcmp(tmp->link->music_name, Newnode->music_name) >= 0) {   //�ٵ� ���࿡ NULL���̸� ������ �����ȳ��� �Ϸ��� NULL���϶� �� ���������� �ְ� �ؾ���
                    Newnode->link = tmp->link;                      //�� ��尪��ũ å�� ���´�� �������.
                    tmp->link = Newnode;                            //�� ����� ��ũ���� ���� ����� ��ũ�� �Ű��ְ�, �� ���� ���� ��Ī�ϵ��� �ϸ��.
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
    printf("��ġ�� �������ּ��� : ");
    scanf("%d", &num);
    if (num == 1) {                                                     //����ڰ� ù��°�� �ְ� ������. ���� ó���� ���� �ִ� ��� ���.
        Newnode->link = head;
        head = Newnode;
    }
    else {
        if (head != NULL) {
            Node* tmp = head;
            for (int i = 0; i < num - 2; tmp = tmp->link) {         //����ڰ� �Է��� ������ ���󰡸� ����ڰ� �ְ����ϴ� �� ����� ���� ����.
                i++;                                                //�ѹ� �Ѿ�°� ���� head�� �޾ұ� ������ �ѹ� �Ѿ�� pre�� ������ �ްԵ�.
            }
            Newnode->link = tmp->link;                      //���������� ��ݸ��� ��� ����
            tmp->link = Newnode;
        }
        else {
            head = Newnode;                                 //���� �� �ص尡 ��ݸ��� ��尡��
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
    printf("\n����Ʈ����� ������ :%d�� �Դϴ�.\n", cnt);
}

void list_display(Node* head) {
    while (head != NULL) {                              //ù��° ������ ����
        printf("\n�뷡���� : %s\n", head->music_name);
        printf("\n������ �̸� : %s\n", head->maker_name);
        printf("\n�帣 : %c\n", head->genre);
        printf("\n��ǥ�⵵ : %d\n", head->year);
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
        printf("���ϴ� ���α׷��� ���ڸ� �Է��ϼ���.\n0. ���α׷� ����\n1. ���ǻ���\n2. Ư����ġ�� ���� ����\n3. ����Ʈ ��� ���� ���\n4. ���� ���");
        printf("\n------------------------------------------\n\n");
        scanf("%d", &num);
        switch (num)
        {
        case 0: {
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        }
        case 1: {
            printf("\n\n------�������� �뷡 ����------\n\n");
            printf("�뷡 ������ �Է��ϼ��� : ");
            scanf("%s", music_name);
            getchar();
            printf("������ �̸��� �Է��ϼ��� : ");
            scanf("%s", maker_name);
            getchar();
            printf("��ǥ�⵵�� �Է��ϼ��� : ");
            scanf("%d", &year1);
            getchar();
            printf("�帣�� �Է��ϼ���(b, c, h, j, t) : ");
            scanf("%c", &genre1);
            getchar();
            head = insert_sort(head, music_name, maker_name, genre1, year1);
            break;
        }
        case 2: {
            printf("\n\n------Ư����ġ ���� ����------\n\n");
            printf("�뷡 ������ �Է��ϼ��� : ");
            scanf("%s", music_name);
            getchar();
            printf("������ �̸��� �Է��ϼ��� : ");
            scanf("%s", maker_name);
            getchar();
            printf("��ǥ�⵵�� �Է��ϼ��� : ");
            scanf("%d", &year1);
            getchar();
            printf("�帣�� �Է��ϼ���(b, c, h, j, t) : ");
            scanf("%c", &genre1);
            getchar();
            head = insert_node(head, music_name, maker_name, genre1, year1);
            break;
        }
        case 3: {
            printf("\n\n------����Ʈ ��� ���� ���------\n\n");
            list_length(head);
            break;
        }
        case 4: {
            printf("\n\n------���� ���------\n\n");
            list_display(head);
            break;
        }
        default:
            printf("�߸��Է��ϼ˽��ϴ�.");
            break;
        }
    }
}