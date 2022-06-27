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
	printf("\n==========후원자 리스트==========\n");
	for (int i = 1; i <= h->heap_size; i++) {
		printf("후원자 : [%s], 후원금 : [%d]원", h->heap[i].id, h->heap[i].amount);
		printf("\n=================================\n");
	}
}

void insert_max_heap(HeapType* h) {
	element e1;
	printf("\n====================\n");
	printf("후원자의 이름을 입력하시오 : ");
	scanf("%s", e1.id);
	getchar();
	printf("후원금을 입력하시오 : ");
	scanf("%d", &e1.amount);
	printf("====================\n");


	//삽입시작
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (e1.amount > h->heap[i / 2].amount)) {					//마지막부터 쭉올라오는거라 최상위 root까지 올라오거나
		h->heap[i] = h->heap[i / 2];									//추가하고자 하는 우선순위 값이 추가된 노드 부모노드의 우선순위보다 클때까지
		i /= 2;															//추가하고자 하는 것이 부모가됨
	}
	h->heap[i] = e1;													//while에서 하나라도 걸려 나오게 된다면 i 즉 현재자리에 추가하고자하는 값 추가.
}

element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;
	element null1 = { NULL, NULL };

	if (h->heap_size <= 0) {
		printf("더이상 삭제할 노드가 없습니다.");
		return null1;
	}

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	//위에서 부터 보는거라 맥스사이즈가 1번까지 작아지면 그냥 출력하면됨.
	while (child <= h->heap_size) {
		//만약 child가 현재노드의 갯수보다 작거나 형재중 오른쪽값이 더 크면 if문으로 진입
		if ((child < h->heap_size) && (h->heap[child].amount < h->heap[child + 1].amount))
			//오른쪽 형재가 더 크니까 오른쪽과 비교를 해야함. 그래서 child + 1을 해줘야 그 큰값을 기준으로 계산할수있음.
			child++;
		//delete라 사이즈를 하나 줄였음. 완전이진트리라 마지막 값을 들고 비교할것임.
		//마지막 노드가 맨처음 root노드가 됐으니 그 root노드의 자식중 우선순위가 가장 컸던 노드와 우선순위를 비교할것임.
		//마지막 노드의 우선순위가 컸다면 그자리가 맞기 때문에 종료.
		if (temp.amount >= h->heap[child].amount) break;

		//우선순위가 자식보다 작았다면 우선순위가 큰 자식 노드와 부모노드의 자리 체인지.
		h->heap[parent] = h->heap[child];
		//이제 내가 옮겨야 할 값인 parent는 child의 자리에 있기때문에 parent에 child를 대입 이렇게 parent를 마지막 노드의 위치라 생각해 parent를 현재 비교하고자 하는 위치라고 이야기 해야함.
		parent = child;
		//이제부턴 child자리에서 그 아래 자식을 봐야하므로 child *= 2를 해주어야함
		child *= 2;
	}

	//위에서 비교가 모두 끝나고 자기자리를 찾았다면 제일 마지막에있던 노드는 parent자리로 이동하게됨.
	h->heap[parent] = temp;
	//우선순위 제일높은 값. 출력을 위해 return
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
		printf("\n0. 프로그램 종료\n");
		printf("1. 후원자 추가\n");
		printf("2. 후원자 삭제\n");
		printf("원하는 프로그램을 선택하시오 : ");
		scanf("%d", &n);
		switch (n)
		{
		case 0: {
			printf("프로그램을 종료합니다.\n");
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
			printf("최고후원자는 [%s] 입니다.\n", e1.id);
			printf("후원금은 [%d] 입니다.\n", e1.amount);
			printf("====================\n\n");
			print_list(heap);
			break;
		}
		default:
			break;
		}
	}
}