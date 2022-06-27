#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELEMENT 30

typedef struct {
	char id[20];
	int amount;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}

void print_list(HeapType* h) {
	printf("\n==========�Ŀ��� ����Ʈ==========\n");
	for (int i = 1; i <= h->heap_size; i++) {
		printf("�Ŀ��� : [%s], �Ŀ��� : [%d]��", h->heap[i].id, h->heap[i].amount);
		printf("\n=================================\n");
	}
}

void insert_max_heap(HeapType* h) {
	element e1;
	printf("\n====================\n");
	printf("�Ŀ����� �̸��� �Է��Ͻÿ� : ");
	scanf("%s", e1.id);
	getchar();
	printf("�Ŀ����� �Է��Ͻÿ� : ");
	scanf("%d", &e1.amount);
	printf("====================\n");


	//���Խ���
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (e1.amount > h->heap[i / 2].amount)) {					//���������� �߿ö���°Ŷ� �ֻ��� root���� �ö���ų�
		h->heap[i] = h->heap[i / 2];									//�߰��ϰ��� �ϴ� �켱���� ���� �߰��� ��� �θ����� �켱�������� Ŭ������
		i /= 2;															//�߰��ϰ��� �ϴ� ���� �θ𰡵�
	}
	h->heap[i] = e1;													//while���� �ϳ��� �ɷ� ������ �ȴٸ� i �� �����ڸ��� �߰��ϰ����ϴ� �� �߰�.
}

element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;
	element null1 = { NULL, NULL };

	if (h->heap_size <= 0) {
		printf("���̻� ������ ��尡 �����ϴ�.");
		return null1;
	}

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	//������ ���� ���°Ŷ� �ƽ������ 1������ �۾����� �׳� ����ϸ��.
	while (child <= h->heap_size) {
		//���� child�� �������� �������� �۰ų� ������ �����ʰ��� �� ũ�� if������ ����
		if ((child < h->heap_size) && (h->heap[child].amount < h->heap[child + 1].amount))
			//������ ���簡 �� ũ�ϱ� �����ʰ� �񱳸� �ؾ���. �׷��� child + 1�� ����� �� ū���� �������� ����Ҽ�����.
			child++;
		//delete�� ����� �ϳ� �ٿ���. ��������Ʈ���� ������ ���� ��� ���Ұ���.
		//������ ��尡 ��ó�� root��尡 ������ �� root����� �ڽ��� �켱������ ���� �Ǵ� ���� �켱������ ���Ұ���.
		//������ ����� �켱������ �Ǵٸ� ���ڸ��� �±� ������ ����.
		if (temp.amount >= h->heap[child].amount) break;

		//�켱������ �ڽĺ��� �۾Ҵٸ� �켱������ ū �ڽ� ���� �θ����� �ڸ� ü����.
		h->heap[parent] = h->heap[child];
		//���� ���� �Űܾ� �� ���� parent�� child�� �ڸ��� �ֱ⶧���� parent�� child�� ���� �̷��� parent�� ������ ����� ��ġ�� ������ parent�� ���� ���ϰ��� �ϴ� ��ġ��� �̾߱� �ؾ���.
		parent = child;
		//�������� child�ڸ����� �� �Ʒ� �ڽ��� �����ϹǷ� child *= 2�� ���־����
		child *= 2;
	}

	//������ �񱳰� ��� ������ �ڱ��ڸ��� ã�Ҵٸ� ���� ���������ִ� ���� parent�ڸ��� �̵��ϰԵ�.
	h->heap[parent] = temp;
	//�켱���� ���ϳ��� ��. ����� ���� return
	return item;
}

int main(void) {
	int n;
	HeapType* heap;
	HeapType* heap1;

	heap = create();
	heap1 = create();

	init(heap);
	init(heap1);

	while (1) {
		printf("\n0. ���α׷� ����\n");
		printf("1. �Ŀ��� �߰�\n");
		printf("2. �Ŀ��� ����\n");
		printf("���ϴ� ���α׷��� �����Ͻÿ� : ");
		scanf("%d", &n);
		switch (n)
		{
		case 0: {
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 1: {
			insert_max_heap(heap);
			print_list(heap);
			break;
		}
		case 2: {
			element e1;
			e1 = delete_max_heap(heap);
			printf("\n====================\n");
			printf("�ְ��Ŀ��ڴ� [%s] �Դϴ�.\n", e1.id);
			printf("�Ŀ����� [%d] �Դϴ�.\n", e1.amount);
			printf("====================\n\n");
			print_list(heap);
			break;
		}
		default:
			break;
		}
	}
}