#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char keyword[20];
    int count;
}element;

typedef struct TreeNode {
    element data;
    struct TreeNode* left, * right;
}TreeNode;

int compare(char* e1, char* e2) {
    return strcmp(e1, e2);
}

TreeNode* new_node(char* key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(temp->data.keyword, key);
    temp->left = temp->right = NULL;
    temp->data.count = 1;
    return temp;
}

TreeNode* insert(TreeNode* node, char* ch) {

    if (node == NULL) return new_node(ch);

    if (compare(ch, node->data.keyword) == 0)
        node->data.count++;
    else if (compare(ch, node->data.keyword) < 0)
        node->left = insert(node->left, ch);
    else if (compare(ch, node->data.keyword) > 0)
        node->right = insert(node->right, ch);

    return node;
}

char maxkey[10]; 
int max = 0; 
void inorder(TreeNode* root, FILE* fp2) {
    if (root != NULL) {
        inorder(root->left, fp2);

        printf("키워드 : [%s]    문자 수 : [%d]\n", root->data.keyword, root->data.count);
        fprintf(fp2, "키워드 : [%s]    문자 수 : [%d]\n", root->data.keyword, root->data.count);

        if (max < root->data.count) {
            max = root->data.count;
            strcpy(maxkey, root->data.keyword);
        }

        inorder(root->right, fp2); 
    }
}


TreeNode* min_value_node(TreeNode* root) {                        //가장작은값은 왼쪽으로 쭉들어가면 있음.
    TreeNode* current = root;
    while (current->left != NULL) {
        current = current->left;                                    //NULL값 전이 가장 작은값
    }
    return current;
}

TreeNode* max_value_node(TreeNode* root) {                        //가장큰값은 오른쪽으로 쭉들어가면 있음.
    TreeNode* current = root;
    while (current->right != NULL) {
        current = current->right;                                    //NULL값 전이 가장 큰값
    }
    return current;
}

TreeNode* delete_node(TreeNode* root, char* ch) {
    if (root == NULL) {
        return root;
    }
    if (compare(ch, root->data.keyword) < 0) {                           //입력한 영단어가 루트의 영단어보다 작을때 left탐색
        root->left = delete_node(root->left, ch);
    }
    else if (compare(ch, root->data.keyword) > 0) {                        //입력한 영단어가 루트의 영단어보다 클때 right탐색
        root->right = delete_node(root->right, ch);
    }
    else if (compare(ch, root->data.keyword) == 0) {                                                //입력한 영단어가 루트의 영단어와 동일할때 삭제 시작
        if (root->left == NULL) {                              //왼쪽값이 비어있기 때문에
            TreeNode* tmp = root->right;                        //오른쪽값 빈공간에 저장
            free(root);                                       //단말노드 이거나 혹은 자녀가 1개인 노드를 return 해서 연결해줌
            return tmp;
        }
        else if (root->right == NULL) {
            TreeNode* tmp = root->left;
            free(root);
            return tmp;
        }
        TreeNode* tmp = min_value_node(root->right);               //오른쪽 서브트리에서 가장 작은값.
        root->data = tmp->data;                                 //현재루트 노드에 오른쪽 서브트리 가장 작은값 복사
        root->right = delete_node(root->right, tmp->data.keyword);            //현재루트 노드의 오른쪽 서브트리에서 방금 복사한 값과 같은값을 제거

        /*TreeNode* tmp = max_value_node(root->left);               //왼쪽 서브트리에서 가장 큰값.
        root->key = tmp->key;                                 //현재루트 노드에 왼쪽 서브트리 가장 큰값 복사
        root->left = delete_node(root->left, tmp->key);*/            //현재루트 노드의 완쪽 서브트리에서 방금 복사한 값과 같은값을 제거
    }
    return root;
}


int main(void) {
    TreeNode* frequency = NULL;
    char txt[256];
    element word[11] = { {"break", 0}, {"case",0}, {"do",0}, {"else",0}, {"for",0}, {"if",0}, {"int",0}, {"return",0}, {"struct",0}, {"switch",0}, {"while",0} };
    FILE* fp1 = fopen("bst_in.txt", "r");
    int num = 0;
    int cnt;
    FILE* fp2 = fopen("bst_out.txt", "w");
    while (1) {
        printf("0. 프로그램종료\n");
        printf("1. 빈도수 저장하기\n");
        printf("2. 중위순회 출력\n");
        printf("3. 노드 삭제\n");
        printf("원하는 프로그램을 입력하시오 : ");
        scanf("%d", &cnt);
        switch (cnt) {
        case 0: {
            printf("프로그램을 종료합니다.\n");
        }
        case 1: {
            if (fp1 == NULL)
                printf("파일을 찾을 수 없습니다.\n");
            else {
                while (!feof(fp1)) {                                                                        //파일의 마지막에 도달할때까지
                    fgets(txt, sizeof(txt), fp1);                                                           //txt 파일에 한줄씩 저장함.
                    char* ptr = strtok(txt, " ");
                    int i, j;
                    while (ptr != NULL) {
                        for (i = j = 0; ptr[i]; i++) {
                            if ('a' <= ptr[i] && 'z' >= ptr[i])                                                 //영어가 아닌 특수문자 이면
                                ptr[j++] = ptr[i];                                                              //앞으로 당겨서 잘라냄
                        }
                        ptr[j] = 0;                                                                             //뒤에값 지워버리기
                        for (int i = 0; i < 11; i++) {
                            if (strcmp(word[i].keyword, ptr) == 0) {
                                frequency = insert(frequency, ptr);
                            }
                        }
                        ptr = strtok(NULL, " ");                                                            //다음단어
                    }
                }
                fclose(fp1);
            }
            inorder(frequency, fp2);
            printf("\n");
            fprintf(fp2, "가장 많은 키워드 : [%s] -> [%d개] \n", maxkey, max);
            printf("가장 많은 키워드 : [%s] -> [%d개] \n", maxkey, max);
            printf("\n");
            fclose(fp2);
            break;
        }
        case 2: {
            printf("======중위순회 재출력======\n");
            inorder(frequency, fp2);
            printf("\n");
            fprintf(fp2, "가장 많은 키워드 : [%s] -> [%d개] \n", maxkey, max);
            printf("가장 많은 키워드 : [%s] -> [%d개] \n", maxkey, max);
            printf("\n");
            fclose(fp2);
            break;
        }
        case 3: {
            printf("======노드삭제======\n");
            char *CH = malloc(sizeof(char)*10);
            printf("삭제할 영단어를 입력하시오 : ");
            scanf("%s", CH);
            frequency = delete_node(frequency, CH);
            printf("\n\n");
            break;
        }
        }
    }
}