#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE 0

typedef int Status;
typedef int ElemType;

typedef struct DuLNode {
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode, *DuLinkList;

/**
 * �������������һ���յ�˫������ L
 * @param L
 */
void InitList(DuLinkList *L) {
    *L = (DuLinkList)malloc(sizeof(struct DuLNode));
    if (*L) {
        (*L)->next = (*L)->prior = *L;
    } else {
        exit(OVERFLOW);
    }

}

/**
 * ��ʼ������˫������ L����
 * �������������˫������ L
 * @param L
 */
void DestroyList(DuLinkList *L) {
    DuLinkList q, p = (*L)->next; //p ָ���һ���ڵ�
    while (p != *L) {
        q = p->next;
        free(p);
        p = q;
    }
    free(*L);
    *L = NULL;
}

/**
 * ��ʼ������˫������ L ����
 * ����������� L �ÿ�
 * @param L
 */
void ClearList(DuLinkList L) {
    DuLinkList q, p = L->next; //p ָ���һ���ڵ�
    while (p != L) { //p û�е���ͷ
        q = p->next;
        free(p);
        p = q;
    }
    L->next = L->prior = L; //ͷ�ڵ�����ָ���ָ����
}

/**
 * ��ʼ������˫������ L ����
 * ����������� L Ϊ�ձ����� TRUE�����򷵻� FALSE
 * @param L
 * @return
 */
Status ListEmpty(DuLinkList L) {
    if (L->next == L && L->prior == L) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * ��ʼ������˫������� L ����
 * ������������� L �е�����Ԫ�ظ���
 * @param L
 * @return
 */
int ListLength(DuLinkList L) {
    int i = 0;
    DuLinkList p = L->next; //p ָ���һ���ڵ�
    while (p != L) { //p û�е���ͷ
        i++;
        p = p->next;
    }
    return i;
}

/**
 * ��ʼ������˫������� L ���ڣ��� 1 <= i <= ListLength(L)
 * ����������� e ���� L �е� i ��Ԫ�ص�ֵ
 * @param L
 * @param i
 * @param e
 * @return
 */
Status GetElem(DuLinkList L, int i, ElemType *e) {
    DuLinkList p = L->next; //p ָ���һ���ڵ�
    int j = 1; //������
    while (p != L && j < i) { //˳ָ������ѯ��ֱ�� p ָ��� i ��Ԫ�ػ� p ָ��ͷ���
        p = p->next;
        ++j;
    }
    if (p == L || j > i) { //�� i ��Ԫ�ز�����
        return ERROR;
    }
    *e = p->data; //ȡ�õ� i ��Ԫ��
    return OK;
}

/**
 * ��ʼ������˫������ L ����
 * ������������� L �е�һ��ֵ��Ԫ�� e ��ͬ��Ԫ���� L �е�λ�á���Ԫ�ز����ڣ��򷵻� 0
 * @param L
 * @param e
 * @param compare
 * @return
 */
int LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
    int i = 0;
    DuLinkList p = L->next; //p ָ���һ���ڵ�
    while (p != L) { //p û�е���ͷ
        i++;
        if (compare(p->data, e)) { //�ҵ���Ԫ��
            return i;
        }
        p = p->next;
    }
    return 0;
}

Status compare(ElemType e1, ElemType e2) {
    if (e1 == e2) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * ��ʼ������˫������ L ����
 * ����������� cur_e �� L �е�Ԫ�أ��Ҳ��ǵ�һ�������� pre_e ������ǰ��������ʧ�ܣ�pre_e �޶���
 * @param L
 * @param cur_e
 * @param pre_e
 * @return
 */
Status PriorElem(DuLinkList L, ElemType cur_e, ElemType *pre_e) {
    DuLinkList p = L->next->next; //p ָ��ڶ���Ԫ��
    while (p != L) {
        if (p->data == cur_e) {
            *pre_e = p->prior->data; //����ǰ��
            return OK;
        }
        p = p->next;
    }
    return INFEASIBLE;
}

/**
 * ��ʼ������˫������� L ����
 * ����������� cur_e �� L �е�Ԫ�أ��Ҳ������һ�������� next_e ���������������ʧ�ܣ�next_e �޶���
 * @param L
 * @param cur_e
 * @param pre_e
 * @return
 */
Status NextElem(DuLinkList L, ElemType cur_e, ElemType *next_e) {
    DuLinkList p = L->next->next; //p ָ��ڶ���Ԫ��
    while (p != L) {
        if (p->prior->data == cur_e) {
            *next_e = p->data; //���غ���
            return OK;
        }
        p = p->next;
    }
    return INFEASIBLE;
}

/**
 * ���� L �е� i ��Ԫ�صĵ�ַ���� i = 0 ����ͷ��㣬�� i �����ڣ����� NULL
 * @param L
 * @param i
 * @return
 */
DuLinkList GetElemP(DuLinkList L, int i) {
    DuLinkList p = L; //p ָ��ͷ���
    if (i < 0 || i > ListLength(L)) { //i ֵ���Ϸ�
        return NULL;
    }
    for (int j = 1; j <= i; j++) {
        p = p->next;
    }
    return p;
}

/**
 * ��ʼ������˫������ L ���ڣ��� 1 <= i <= ListLength(L) + 1
 * ����������� L �е� i ��Ԫ��ǰ�����µ�Ԫ�� e��L �ĳ��ȼ� 1
 * @param L
 * @param i
 * @param e
 * @return
 */
Status ListInsert(DuLinkList L, int i, ElemType e) {
    DuLinkList p, s;
    if (i < 1 || i > (ListLength(L) + 1)) { //i ֵ���Ϸ�
        return ERROR;
    }
    p = GetElemP(L, i - 1);
    if (!p) { //�� L ��ȷ���� i ��Ԫ�ص�ǰ��λ��ָ�� p
        return ERROR; // p = NULL ʱ���� i ��Ԫ�ز�����
    }
    s = (DuLinkList)malloc(sizeof(struct DuLNode));
    if (!s) {
        exit(OVERFLOW);
    }
    s->data = e;
    s->prior = p; //�� i - 1 ��Ԫ�غ����
    s->next = p->next;
    p->next->prior = s;
    p->next = s;
    return OK;
}

/**
 * ��ʼ������˫������ L �����ҷǿգ��� 1 <= i <= ListLength(L)
 * ���������ɾ�� L �еĵ� i ��Ԫ�ز��� e ������ֵ��L �ĳ��ȼ� 1
 * @param S
 * @param i
 * @param e
 * @return
 */
Status ListDelete(DuLinkList L, int i, ElemType *e) {
    DuLinkList p;
    p = GetElemP(L, i);
    if (!p) { //�� L ��ȷ���� i ��Ԫ�ص�λ��ָ�� p
        return ERROR; //p = NULL �ǣ��� i ��Ԫ�ز����ڣ�Ҳ���� i ֵ���Ϸ�
    }
    *e = p->data;
    p->prior->next = p->next; //�޸ı�ɾ������ǰ�����ĺ��ָ��
    p->next->prior = p->prior; //�޸ı�ɾ�����ĺ�̽���ǰ��ָ��
    free(p);
    return OK;
}

/**
 * ��ʼ������˫������ L ����
 * �����������ͷ����������������б������ڱ��������ж�ÿ��������һ�Σ����������е��� vi() ����Ԫ��
 * @param L
 * @param vi
 */
void TraverseList(DuLinkList L, void(*vi)(ElemType)) {
    DuLinkList p = L->next; //p ָ���һ��Ԫ��
    while (p != L) { //����
        vi(p->data);
        p = p->next;
    }
    printf("\n");
}

void vi(ElemType e) {
    printf("%d ", e);
}

/**
 * ���ݽ����ǰ�巨������ n ��Ԫ�ص�˫������
 * @param L
 * @param n
 */
void CreateList_H(DuLinkList *L, int n) {
    InitList(L);
    DuLinkList p;
    for (int i = 0; i < n; ++i) {
        p = (DuLinkList)malloc(sizeof(struct DuLNode));
        if (!p) {
            exit(OVERFLOW);
        }
        scanf("%d",&p->data);
        p->prior = *L;
        p->next = (*L)->next;
        (*L)->next->prior = p;
        (*L)->next = p;
    }
}

/**
 * ���ݽ������巨������ n ��Ԫ�صĵ�����
 * @param L
 * @param n
 */
void CreateList_R(DuLinkList *L, int n) {
    InitList(L);
    DuLinkList p, r = (*L)->next;
    for (int i = 0; i < n; ++i) {
        p = (DuLinkList)malloc(sizeof(struct DuLNode));
        if (!p) {
            exit(OVERFLOW);
        }
        scanf("%d", &p->data);
        p->prior = r;
        p->next = *L;
        r->next->prior = p;
        r->next = p;
        r = p;
    }
}

/*--------------------������------------------------*/

/**
 * ���Գ���
 * @return
 */
int main() {  // ���Գ���ֻ���Ժ����Ƿ����߼�����
    DuLinkList  list;
    int temp;
    ElemType *e;

//    CreateList_H(&list, 3);
    CreateList_R(&list, 3);
    printf("%d\n", ListEmpty(list));
    printf("%d\n", ListLength(list));
    TraverseList(list, vi);
    temp = ListInsert(list, 1, 99);
    TraverseList(list, vi);
    temp = ListInsert(list, 5, 100);
    TraverseList(list, vi);
    temp = GetElem(list, 3, e);
    printf("%d\n", *e);
    temp = PriorElem(list, 5, e);
    printf("%d\n", *e);
    temp = NextElem(list, 5, e);
    printf("%d\n", *e);
    printf("%d\n", LocateElem(list, 6, compare));
    temp = ListDelete(list, 4, e);
    TraverseList(list, vi);
    ClearList(list);
    printf("%d\n", ListLength(list));

    DestroyList(&list);
}