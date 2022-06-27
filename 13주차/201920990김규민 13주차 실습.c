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

        printf("Ű���� : [%s]    ���� �� : [%d]\n", root->data.keyword, root->data.count);
        fprintf(fp2, "Ű���� : [%s]    ���� �� : [%d]\n", root->data.keyword, root->data.count);

        if (max < root->data.count) {
            max = root->data.count;
            strcpy(maxkey, root->data.keyword);
        }

        inorder(root->right, fp2); 
    }
}


TreeNode* min_value_node(TreeNode* root) {                        //������������ �������� �ߵ��� ����.
    TreeNode* current = root;
    while (current->left != NULL) {
        current = current->left;                                    //NULL�� ���� ���� ������
    }
    return current;
}

TreeNode* max_value_node(TreeNode* root) {                        //����ū���� ���������� �ߵ��� ����.
    TreeNode* current = root;
    while (current->right != NULL) {
        current = current->right;                                    //NULL�� ���� ���� ū��
    }
    return current;
}

TreeNode* delete_node(TreeNode* root, char* ch) {
    if (root == NULL) {
        return root;
    }
    if (compare(ch, root->data.keyword) < 0) {                           //�Է��� ���ܾ ��Ʈ�� ���ܾ�� ������ leftŽ��
        root->left = delete_node(root->left, ch);
    }
    else if (compare(ch, root->data.keyword) > 0) {                        //�Է��� ���ܾ ��Ʈ�� ���ܾ�� Ŭ�� rightŽ��
        root->right = delete_node(root->right, ch);
    }
    else if (compare(ch, root->data.keyword) == 0) {                                                //�Է��� ���ܾ ��Ʈ�� ���ܾ�� �����Ҷ� ���� ����
        if (root->left == NULL) {                              //���ʰ��� ����ֱ� ������
            TreeNode* tmp = root->right;                        //�����ʰ� ������� ����
            free(root);                                       //�ܸ���� �̰ų� Ȥ�� �ڳడ 1���� ��带 return �ؼ� ��������
            return tmp;
        }
        else if (root->right == NULL) {
            TreeNode* tmp = root->left;
            free(root);
            return tmp;
        }
        TreeNode* tmp = min_value_node(root->right);               //������ ����Ʈ������ ���� ������.
        root->data = tmp->data;                                 //�����Ʈ ��忡 ������ ����Ʈ�� ���� ������ ����
        root->right = delete_node(root->right, tmp->data.keyword);            //�����Ʈ ����� ������ ����Ʈ������ ��� ������ ���� �������� ����

        /*TreeNode* tmp = max_value_node(root->left);               //���� ����Ʈ������ ���� ū��.
        root->key = tmp->key;                                 //�����Ʈ ��忡 ���� ����Ʈ�� ���� ū�� ����
        root->left = delete_node(root->left, tmp->key);*/            //�����Ʈ ����� ���� ����Ʈ������ ��� ������ ���� �������� ����
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
        printf("0. ���α׷�����\n");
        printf("1. �󵵼� �����ϱ�\n");
        printf("2. ������ȸ ���\n");
        printf("3. ��� ����\n");
        printf("���ϴ� ���α׷��� �Է��Ͻÿ� : ");
        scanf("%d", &cnt);
        switch (cnt) {
        case 0: {
            printf("���α׷��� �����մϴ�.\n");
        }
        case 1: {
            if (fp1 == NULL)
                printf("������ ã�� �� �����ϴ�.\n");
            else {
                while (!feof(fp1)) {                                                                        //������ �������� �����Ҷ�����
                    fgets(txt, sizeof(txt), fp1);                                                           //txt ���Ͽ� ���پ� ������.
                    char* ptr = strtok(txt, " ");
                    int i, j;
                    while (ptr != NULL) {
                        for (i = j = 0; ptr[i]; i++) {
                            if ('a' <= ptr[i] && 'z' >= ptr[i])                                                 //��� �ƴ� Ư������ �̸�
                                ptr[j++] = ptr[i];                                                              //������ ��ܼ� �߶�
                        }
                        ptr[j] = 0;                                                                             //�ڿ��� ����������
                        for (int i = 0; i < 11; i++) {
                            if (strcmp(word[i].keyword, ptr) == 0) {
                                frequency = insert(frequency, ptr);
                            }
                        }
                        ptr = strtok(NULL, " ");                                                            //�����ܾ�
                    }
                }
                fclose(fp1);
            }
            inorder(frequency, fp2);
            printf("\n");
            fprintf(fp2, "���� ���� Ű���� : [%s] -> [%d��] \n", maxkey, max);
            printf("���� ���� Ű���� : [%s] -> [%d��] \n", maxkey, max);
            printf("\n");
            fclose(fp2);
            break;
        }
        case 2: {
            printf("======������ȸ �����======\n");
            inorder(frequency, fp2);
            printf("\n");
            fprintf(fp2, "���� ���� Ű���� : [%s] -> [%d��] \n", maxkey, max);
            printf("���� ���� Ű���� : [%s] -> [%d��] \n", maxkey, max);
            printf("\n");
            fclose(fp2);
            break;
        }
        case 3: {
            printf("======������======\n");
            char *CH = malloc(sizeof(char)*10);
            printf("������ ���ܾ �Է��Ͻÿ� : ");
            scanf("%s", CH);
            frequency = delete_node(frequency, CH);
            printf("\n\n");
            break;
        }
        }
    }
}