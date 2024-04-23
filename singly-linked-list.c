/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------이한결-------------------2021041055---------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<      \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* back = NULL;
	while(p != NULL) {
		back = p;
		p = p->link;
		free(back);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));		// 추가할 노드
    listNode* a = h->first;						// node를 가르키는 포인터
    listNode* back = NULL;						// key가 큰 값이 나오기 이전 노드
    node->key = key;							
    while(a != NULL && a->key <= key) {			// a가 널이 아니고 key 가 key보다 작을때까지
        back = a;								
        a = a->link;
    }
    if (back == NULL) {							// back이 null이면 첫번째 값이 a
        node->link = h->first;
        h->first = node;
    } else {									// 아니면 back 뒤에 추가
        back->link = node;
        node->link = a;
    }
    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	if (h->first == NULL) {
        return -1; // 리스트가 비어있는 경우
    }
	listNode* node = (listNode*)malloc(sizeof(listNode));	// 추가할 노드
	listNode* a = h->first;									// node를 가리킬 포인터
	while(a -> link != NULL){								// a가 마지막 노드가 되면 종료
		a = a -> link;
	}
	a -> link = node;										// a뒤에 node변수 추가
	node -> key = key;										// 노드의 key 값 초기화
	node -> link = NULL;									// 노드의 link 초기화
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if (h->first == NULL) {
        return -1; // 리스트가 비어있는 경우
    }
	listNode* a = h->first;
	h->first = h->first->link;				// first가 두번째 노드를 가르키도록 변경
	free(a);								// 메모리 해제
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if (h->first == NULL) {
        return -1; // 리스트가 비어있는 경우
    }
	listNode* a = h->first;					// node를 가리키는 포인터
	listNode* back = NULL;					// key와 값이 같기전 포인터
	int check = 0;
	while (a->link != NULL && a->key != key){
		back = a;
		a = a->link;
		if (a->key == key) check = 1;
	}
	if (check == 1) return 0; 				// Key 가 존재 안할 경우
	if (back == NULL){						// back이 null 이면 첫번째 값이 a
		h->first = a->link;
		free(a);
	}
	else
	{
		back->link = a->link;				// 아니면 back뒤에 a뒤의 노드가 오게 설정
		free(a);
	}
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if (h->first == NULL) {
        return -1; // 리스트가 비어있는 경우
    }
	listNode* a = h->first;					// node를 가리키는 포인터
	listNode* back = NULL;					// 마지막 포인터 이전 포인터
	while (a->link != NULL){
		back = a;
		a = a->link;
	}
	back->link = NULL;
	free(a);								// 메모리 해제
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if (h->first == NULL) {
        return -1; // 리스트가 비어있는 경우
    }
	listNode* a = h->first;					// 노드를 가리킬 포인터
	listNode* temp1 = h->first;				// 노드의 link를 바꿔줄 포인터 (앞 포인터)
	listNode* temp2 = NULL;					// 노드의 link를 바꿔줄 포인터 (뒤 포인터)
	int i = 0;
	while(a != NULL){
		temp2 = temp1;
		temp1 = a;
		a = a->link;						// 각각 뒤에 오는 노드를 가르키도록 설정
		temp1 -> link = temp2;				// 앞뒤 순서를 바꿔줌
		if(i == 0) temp2 -> link = NULL; i = 1;		// 첫번째 노드의 link는 NULL값을 가르키기 때문에 i변수를 이용해 첫번째 노드라는 것을 알게끔 설정
	}
	h->first = temp1; 						// first가 가르키는 값은 마지막 노드가 됨
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

