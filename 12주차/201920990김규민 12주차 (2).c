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


//�ƽ�ã��
int max = 0;
TreeNode* maxNode;
TreeNode* postorder_max(TreeNode* root) {
    if (root != NULL) {
        if (max < root->data) {                                     //�ƽ��� ���� �ٸ� max������ �����ϸ鼭 ����ؼ� �ƽ����� ��
            max = root->data;                                       //���� �ƽ����� ã�� ����ؼ� ������ �Ǹ�
            maxNode = root;                                         //���ŵ����� root�� ���ο� Ʈ���� maxNode�� ����
        }
        postorder_max(root->left);                                  //������ �����.
        postorder_max(root->right);

    }
    return maxNode;                                                 //�������� maxNode�� ��ȯ�ǵ���
}


//�ڽ�1��
int count = 0;
int find(TreeNode* root) {
    if (root != NULL) {
        find(root->left);                                           //������ ���
        find(root->right);

        if (root->left == NULL && root->right != NULL) {            //���� root�� �ڽ��� �����ʸ� �ְų�
            count++;
            return;
        }
        else if (root->left != NULL && root->right == NULL) {       //���ʸ� ������
            count++;                                                //count ��������
            return;
        }
    }                                                               //�����̱� ������ ���� �Ʒ����� ���� ���� ���鼭 �ö���Ե�.
    return count;                   
}

//�������� ã��
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
    TreeNode* NewNode = (TreeNode*)malloc(sizeof(TreeNode*));       //���ο� Ʈ���� ����
    if (root != NULL) {
        NewNode->data = root->data;                                 //������ �Ѱ��ֱ�
        NewNode->left = connect(root->left);                        //root�� ������ ��ͽ��� ���ο� ��� ����
        NewNode->right = connect(root->right);                      //�����ʵ� ����
    }
    else return NULL;                                               //���� NULL���̶�� NULL����

    return NewNode;                                                 //�������� NewNode�� �Ѱ��ֱ�
}

int main(void) {
    TreeNode* root;
    TreeNode* root1;
    TreeNode* root2;
    char cha, cha1;
    printf("���� Ʈ���� ���� Ʈ���� �����Ͻÿ� (F/S/T) : ");
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
        printf("�߸� �Է��ϼ̽��ϴ�.\n");
        printf("���� Ʈ���� �����Ͻÿ� (F/S/T) : ");
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
        printf("�߸� �Է��ϼ̽��ϴ�.\n");
        printf("���� Ʈ���� �����Ͻÿ� (F/S/T) : ");
        scanf("%c", &cha1);
    }
    while (1) {
        printf("0. ���α׷� ����\n");
        printf("1. ������ȸ, ������ȸ, ������ȸ ���\n");
        printf("2. ������ �����Ͱ� 1�� ���� ��Ű��\n");
        printf("3. ��� �� �ִ밪 ���ϱ�\n");
        printf("4. �ڽ��� �ϳ��� ��� ���ϱ�\n");
        printf("5. �ΰ��� ����Ʈ���� �������� �Ǵ�\n");
        printf("6. ����Ʈ���� �����Ͽ� ������ Ʈ���� ��ȯ\n");
        printf("7. ������ ����Ʈ�� ���\n");
        printf("���ϴ� ���α׷��� �Է��Ͻÿ� : ");
        int n;
        scanf("%d", &n);
        switch (n)
        {
        case 0: {
            printf("���α׷��� �����մϴ�.");
            return 0;
        }
        case 1: {
            printf("������ȸ : ");
            inorder(root);
            printf("\n");
            printf("������ȸ : ");
            preorder(root);
            printf("\n");
            printf("������ȸ : ");
            postorder(root);
            printf("\n\n");
            break;
        }
        case 2: {
            printf("�� ��� 1�� ���ϱ� :\n");
            preorder_add(root);
            printf("������ȸ : ");
            preorder(root);
            printf("\n\n");

            break;
        }
        case 3: {
            TreeNode* max = (TreeNode*)malloc(sizeof(TreeNode*));
            max = postorder_max(root);                                                              //max Ʈ���� ������ �Ǿ��⶧����
            printf("max�� : %d\n", max->data);                                                      //����� max->data�� ��
            printf("\n\n");
            break;
        }
        case 4: {
            int cnt = find(root);
            printf("�ڽ��� �ϳ��� ����� ������ [%d]�� �Դϴ�.\n\n", cnt);
            break;
        }
        case 5: {
            int cnt1 = identical(root, root1);
            if (cnt1) {
                printf("\n�� ����Ʈ���� �����մϴ�.\n\n");
            }
            else {
                printf("\n�� ����Ʈ���� �������� �ʽ��ϴ�.\n\n");
            }
            break;
        }
        case 6: {
            root2 = connect(root);
            int cnt1 = identical(root, root2);
            if (cnt1) {
                printf("\n������ Ʈ���� ������ �� ����Ʈ���� �����մϴ�.\n\n");
            }
            else {
                printf("\n������ Ʈ���� ������ �� ����Ʈ���� �������� �ʽ��ϴ�.\n\n");
            }
            break;
        }
        case 7: {
            printf("������ȸ : ");
            inorder(root2);
            printf("\n");
            printf("������ȸ : ");
            preorder(root2);
            printf("\n");
            printf("������ȸ : ");
            postorder(root2);
            printf("\n\n");
        }
        default:
            break;
        }
    }
}