#include <stdio.h>
#include <stdlib.h>
#include<memory.h>


typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

//                 [15]
//        [20]              [5]
//   [6]      [7]               [33]
//         [8]
//            [9]
//          [10] [11]
//      

TreeNode n1 = { 10 ,NULL ,NULL };
TreeNode n2 = { 11 ,NULL ,NULL };
TreeNode n3 = { 9 ,&n1 ,&n2 };
TreeNode n4 = { 8 ,NULL ,&n3 };
TreeNode n5 = { 7 ,&n4 ,NULL };
TreeNode n6 = { 6 ,NULL ,NULL };
TreeNode n7 = { 20 ,&n6 ,&n5 };
TreeNode n8 = { 33 ,NULL ,NULL };
TreeNode n9 = { 5 ,NULL ,&n8 };
TreeNode n10 = { 15 ,&n7 ,&n9 };
TreeNode* s_root = &n10;

//                 [20]                        
//        [5]                [4]
//                      [3]      [21]
//                   [2]   [7]
//                           [8]
//                              [9]
//                            [16]

TreeNode j_n1 = { 5,  NULL, NULL };
TreeNode j_n2 = { 16, NULL,  NULL };
TreeNode j_n3 = { 9,  &j_n2, NULL };
TreeNode j_n4 = { 8, NULL, &j_n3 };
TreeNode j_n5 = { 7, NULL, &j_n4 };
TreeNode j_n6 = { 2, NULL,  NULL };
TreeNode j_n7 = { 3, &j_n6,  &j_n5 };
TreeNode j_n8 = { 21, NULL,  NULL };
TreeNode j_n9 = { 4, &j_n7,  &j_n8 };
TreeNode j_n10 = { 20, &j_n1,  &j_n9 };
TreeNode* j_root = &j_n10;


//                 [22]                        
//        [31]              [4]
//                              [6]
//                           [5]   [14]
//                             [4]
//                           [3]
//                             [2]
//                           [1]

TreeNode h_n1 = { 31,  NULL, NULL };
TreeNode h_n2 = { 1, NULL,  NULL };
TreeNode h_n3 = { 2,  &h_n2, NULL };
TreeNode h_n4 = { 3, NULL, &h_n3 };
TreeNode h_n5 = { 4, &h_n4, NULL };
TreeNode h_n6 = { 5, NULL,  &h_n5 };
TreeNode h_n7 = { 14, NULL,  NULL };
TreeNode h_n8 = { 6, &h_n6,  &h_n7 };
TreeNode h_n9 = { 4, NULL,  &h_n8 };
TreeNode h_n10 = { 22, &h_n1,  &h_n9 };
TreeNode* h_root = &h_n10;

void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("[%d]", root->data);
        inorder(root->right);
    }
}

void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("[%d]", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}


void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("[%d]", root->data);
    }
}


void preorder_add(TreeNode* root) {
    if (root != NULL) {
        root->data++;
        preorder_add(root->left);
        preorder_add(root->right);
    }
}


//맥스찾기
int max = 0;
TreeNode* maxNode;
TreeNode* postorder_max(TreeNode* root) {
    if (root != NULL) {
        if (max < root->data) {                                     //맥스의 값을 다른 max변수에 저장하면서 계속해서 맥스값을 비교
            max = root->data;                                       //만약 맥스값을 찾아 계속해서 갱신이 되면
            maxNode = root;                                         //갱신됐을때 root를 새로운 트리인 maxNode에 대입
        }
        postorder_max(root->left);                                  //전위로 계산함.
        postorder_max(root->right);

    }
    return maxNode;                                                 //마지막에 maxNode가 반환되도록
}


//자식1개
int count = 0;
int find(TreeNode* root) {
    if (root != NULL) {
        find(root->left);                                           //후위로 계산
        find(root->right);

        if (root->left == NULL && root->right != NULL) {            //현재 root에 자식이 오른쪽만 있거나
            count++;
            return;
        }
        else if (root->left != NULL && root->right == NULL) {       //왼쪽만 있을때
            count++;                                                //count 후위증가
            return;
        }
    }                                                               //후위이기 때문에 제일 아래에서 부터 쭉쭉 보면서 올라오게됨.
    return count;                   
}

//동일한지 찾기
int identical(TreeNode* root, TreeNode* root2) {
    if (root != NULL && root2 != NULL)
        if ((root->data == root2->data)) {
            if (identical(root->left, root2->left) && identical(root->right, root2->right)) {
                return 1;
            }
            else return 0;
        }
        else {
            return 0;
        }
}

TreeNode* connect(TreeNode* root) {
    TreeNode* NewNode = (TreeNode*)malloc(sizeof(TreeNode*));       //새로운 트리를 만들어서
    if (root != NULL) {
        NewNode->data = root->data;                                 //데이터 넘겨주기
        NewNode->left = connect(root->left);                        //root의 왼쪽을 재귀시켜 새로운 노드 저장
        NewNode->right = connect(root->right);                      //오른쪽도 동일
    }
    else return NULL;                                               //만약 NULL값이라면 NULL대입

    return NewNode;                                                 //마지막에 NewNode를 넘겨주기
}

int main(void) {
    TreeNode* root;
    TreeNode* root1;
    TreeNode* root2;
    char cha, cha1;
    printf("사용될 트리와 비교할 트리를 선택하시오 (F/S/T) : ");
    scanf("%c %c", &cha, &cha1);
    if (cha == 'F') {
        root = s_root;
    }
    else if (cha == 'S') {
        root = j_root;
    }
    else if (cha == 'T') {
        root = h_root;
    }
    else {
        printf("잘못 입력하셨습니다.\n");
        printf("사용될 트리를 선택하시오 (F/S/T) : ");
        scanf("%c", &cha);
    }
    if (cha1 == 'F') {
        root1 = s_root;
    }
    else if (cha1 == 'S') {
        root1 = j_root;
    }
    else if (cha1 == 'T') {
        root1 = h_root;
    }
    else {
        printf("잘못 입력하셨습니다.\n");
        printf("사용될 트리를 선택하시오 (F/S/T) : ");
        scanf("%c", &cha1);
    }
    while (1) {
        printf("0. 프로그램 종료\n");
        printf("1. 중위순회, 전위순회, 후위순회 출력\n");
        printf("2. 노드들의 데이터값 1씩 증가 시키기\n");
        printf("3. 노드 중 최대값 구하기\n");
        printf("4. 자식이 하나인 노드 구하기\n");
        printf("5. 두개의 이진트리가 동일한지 판단\n");
        printf("6. 이진트리를 복사하여 동일한 트리를 반환\n");
        printf("7. 복사한 이진트리 출력\n");
        printf("원하는 프로그램을 입력하시오 : ");
        int n;
        scanf("%d", &n);
        switch (n)
        {
        case 0: {
            printf("프로그램을 종료합니다.");
            return 0;
        }
        case 1: {
            printf("중위순회 : ");
            inorder(root);
            printf("\n");
            printf("전위순회 : ");
            preorder(root);
            printf("\n");
            printf("후위순회 : ");
            postorder(root);
            printf("\n\n");
            break;
        }
        case 2: {
            printf("각 노드 1씩 더하기 :\n");
            preorder_add(root);
            printf("전위순회 : ");
            preorder(root);
            printf("\n\n");

            break;
        }
        case 3: {
            TreeNode* max = (TreeNode*)malloc(sizeof(TreeNode*));
            max = postorder_max(root);                                                              //max 트리에 저장이 되었기때문에
            printf("max값 : %d\n", max->data);                                                      //출력을 max->data로 함
            printf("\n\n");
            break;
        }
        case 4: {
            int cnt = find(root);
            printf("자식이 하나인 노드의 갯수는 [%d]개 입니다.\n\n", cnt);
            break;
        }
        case 5: {
            int cnt1 = identical(root, root1);
            if (cnt1) {
                printf("\n두 이진트리가 동일합니다.\n\n");
            }
            else {
                printf("\n두 이진트리가 동일하지 않습니다.\n\n");
            }
            break;
        }
        case 6: {
            root2 = connect(root);
            int cnt1 = identical(root, root2);
            if (cnt1) {
                printf("\n선택한 트리와 복사한 두 이진트리가 동일합니다.\n\n");
            }
            else {
                printf("\n선택한 트리와 복사한 두 이진트리가 동일하지 않습니다.\n\n");
            }
            break;
        }
        case 7: {
            printf("중위순회 : ");
            inorder(root2);
            printf("\n");
            printf("전위순회 : ");
            preorder(root2);
            printf("\n");
            printf("후위순회 : ");
            postorder(root2);
            printf("\n\n");
        }
        default:
            break;
        }
    }
}