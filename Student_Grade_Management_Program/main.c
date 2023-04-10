#include <stdio.h>
#include <stdlib.h>

/* 구조체 선언 */
// 학생의 데이터를 담는 구조체를 새로운 타입 element로 정의
typedef struct student {
    int num;
    char name[20]; // 이름은 4글자까지 가능
    int kor, math, eng, com;
} element;

// 이중 연결리스트의 자기참조구조체 구현
typedef struct DListNode {
    struct DListNode *llink;
    struct DListNode *rlink;
    element data;
} DListNode;

/* 초기화 */
// 처음에 노드를 초기화
void init(DListNode *phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

/* Insert_node */
// 새로운 노드를 받아 before 노드 다음에 삽입
DListNode *dinsert_node(DListNode *before, DListNode *new_node) {
    // new_node의 링크 필드 먼저 생성
    new_node->llink = before;
    new_node->rlink = before->rlink;
    before->rlink->llink = new_node; // aaa의 llink에는 new_node 주소를 저장
    before->rlink = new_node; // before의 rlink에는 new_node 주소를 저장
    // return new_node;
}

/* Search */
// 학생 번호에 입력 받아 노드 탐색 후 출력
void search(DListNode *head, element data) {
    DListNode *p;

    for (p = head->rlink; p != head; p = p->rlink) {
        if (p->data.num == data.num) {
            printf("%6d %10s %6d %6d %6d %6d\n",
                   p->data.num, p->data.name, p->data.kor, p->data.math, p->data.eng, p->data.com);
            return;
        }
    }
    printf("%d 번 학생의 번호 검색 실패\n\n", data.num);
}

// 특정 학생 삭제하는 함수
void delete(DListNode *phead, element data) {
    DListNode *p;

    for (p = phead->rlink; p != phead; p = p->rlink) {
        if (p == phead) return;
        p->llink->rlink = p->rlink;
        p->rlink->llink = p->llink;
        free(p);
        return;
    }
    printf("%d 번 학생의 번호 검색 실패\n\n", data.num);
}

/* Sort */
// 이중 연결리스트를 정렬
void sort_dinsert(DListNode *head) {
    DListNode *p, *q;
    element tmp;
    // 오른쪽으로 이동하여 작은 값 찾으며 정렬
    for (p = head->rlink; p->rlink != head; p = p->rlink) {
        for (q = p->rlink; q != head; q = q->rlink) {
            if (q->data.num < p->data.num) {
                tmp = p->data;
                p->data = q->data;
                q->data = tmp;
            }
        }
    }
}

/* Display */
// 연결 리스트 전체 출력
void display(DListNode *phead) {
    printf("====================================================\n");
    printf("|번 호|  이 름  |  언어  |  수리  |  영어  |  컴퓨터  |\n");
    printf("====================================================\n");

    for (DListNode *p = phead->rlink; p != phead; p = p->rlink) {
        printf("|%3d | %5s  | %4d  | %4d  | %4d  | %5d  |\n",
               p->data.num, p->data.name, p->data.kor, p->data.math, p->data.eng, p->data.com);
    }
    printf("====================================================\n");
}

/* Free_node */
// 동적 할당된 메모리 반환
void free_node(DListNode *phead) {
    DListNode *p = phead->rlink, *next;
    while (p != phead) {
        next = p;
        free(p);
        p = p->rlink;
    }
}

int main() {
    FILE *fp;
    DListNode *head = (DListNode *) malloc(sizeof(DListNode)); // 헤드 노드 생성(데이터 필드는 empty)
    DListNode *tmp; // 임시로 데이터를 입력 받는 노드
    element dat; // 데이터 임시로 입력 받는 구조체
    int flag; // 입력 받는 메뉴

    // 연결 리스트 초기화
    init(head);

    // 파일 열기
    fp = fopen("data.txt", "rt");
    if (fp == NULL) {
        printf("File not found\n");
        return 0;
    }

    // 파일로부터 데이터 입력 받아 tmp 노드에 저장후 노드 삽입
    while (!feof(fp)) {
        fscanf(fp, "%d %s %d %d %d %d",
               &dat.num, dat.name, &dat.kor, &dat.math, &dat.eng, &dat.com);
        printf("%6d %10s %6d %6d %6d %6d\n",
               dat.num, dat.name, dat.kor, dat.math, dat.eng, dat.com);
        tmp = (DListNode *) malloc(sizeof(DListNode)); // create_node 함수 구현 대신 파일 내에서 생성
        tmp->data = dat;

        dinsert_node(head, tmp); // head에 새로 만든 tmp를 insert
    }

    // 메뉴 선택하여 조건에 맞게 함수 호출
    while (1) {
        printf("\n종료(0) 학생 데이터 입력(1) 학생 검색(2) 학생 삭제(3) 목록 보기(4)\n");
        printf("메뉴 입력 : ");
        scanf("%d", &flag);

        switch (flag) {
            case 0: // 종료
                exit(1);
                break;

            case 1: // 데이터 입력 받아 새로운 노드 추가 후 삽입
                tmp = (DListNode *) malloc(sizeof(DListNode));

                printf("추가할 학생 번호 : ");
                scanf("%d", &dat.num);
                printf("이름 : ");
                scanf("%s", dat.name);
                printf("국어 : ");
                scanf("%d", &dat.kor);
                printf("수학 : ");
                scanf("%d", &dat.math);
                printf("영어 : ");
                scanf("%d", &dat.eng);
                printf("컴퓨터 : ");
                scanf("%d", &dat.com);

                tmp->data = dat; // 새로운 노드의 데이터 필드에 입력 받은 dat 구조체를 대입
                dinsert_node(head, tmp); // 노드 맨 앞에 삽입
                break;

            case 2: // 학생 번호 입력 받아 리스트에서 탐색 후 출력
                printf("검색할 학생 번호 : ");
                scanf("%d", &dat.num);
                search(head, dat); // 학생 번호 찾아 출력
                break;

            case 3: // 학생 번호 입력 받아 리스트에서 탐색 후 삭제
                printf("삭제할 학생 번호 : ");
                scanf("%d", &dat.num);
                delete(head, dat);
                break;

            case 4: // 리스트 정렬하여 출력
                printf("\n<정렬된 목록 보기>\n\n");
                sort_dinsert(head); // 목록을 학생 번호 순대로 정렬
                display(head); // 출력
                break;

            default:
                break;
        }
    }
    free_node(head);
    fclose(fp);
}