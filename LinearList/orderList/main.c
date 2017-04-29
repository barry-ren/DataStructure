#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 10
#define LIST_INCREMENT 2

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE 0

typedef int Status;
typedef int ElemType;

typedef struct {
    ElemType *elem;
    int length;
    int listSize;
}SqList;

/**
 * �������������һ���յ�˳��� L
 * @param L
 */
void InitList(SqList *L) {
    L->elem = malloc(LIST_INIT_SIZE * sizeof(SqList));
    if (!L->elem) {
        exit(OVERFLOW);
    }
    L->length = 0;
    L->listSize = LIST_INIT_SIZE;
}

/**
 * ��ʼ���������Ա� L����
 * ����������������Ա� L
 * @param L
 */
void DestroyList(SqList *L) {
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listSize = 0;
}

/**
 * ��ʼ���������Ա� L ����
 * ����������� L ��Ϊ�ձ�
 * @param L
 */
void ClearList(SqList *L) {
    L->length = 0;
}

/**
 * ��ʼ���������Ա� L ����
 * ����������� L Ϊ�ձ����� TRUE�����򷵻� FALSE
 * @param L
 * @return
 */
Status ListEmpty(SqList L) {
    if (L.length == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * ��ʼ���������Ա� L ����
 * ������������� L �е�����Ԫ�ظ���
 * @param L
 * @return
 */
int ListLength(SqList L) {
    return L.length;
}

/**
 * ��ʼ���������Ա� L ���ڣ��� 1 <= i <= ListLength(L)
 * ����������� e ���� L �е� i ��Ԫ�ص�ֵ
 * @param L
 * @param i
 * @param e
 * @return
 */
Status GetElem(SqList L, int i, ElemType *e) {
    if (i < 1|| i > L.length) {
        return ERROR;
    }
    *e = *(L.elem + i - 1);
    return OK;
}

/**
 * ��ʼ���������Ա� L ����
 * ������������� L �е�һ��ֵ��Ԫ�� e ��ͬ��Ԫ���� L �е�λ�á���Ԫ�ز����ڣ��򷵻� 0
 * @param L
 * @param e
 * @param compare
 * @return
 */
int LocateElem(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
    ElemType *p;
    int i = 1;
    p = L.elem;
    while (i <= L.length && !compare(*p++, e)) {
        ++i;
    }
    if (i < L.length) {
        return i;
    } else {
        return 0;
    }
}

Status compare(ElemType e1, ElemType e2) {
    if (e1 == e2) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * ��ʼ���������Ա� L ����
 * ����������� cur_e �� L �е�Ԫ�أ��Ҳ��ǵ�һ�������� pre_e ������ǰ��������ʧ�ܣ�pre_e �޶���
 * @param L
 * @param cur_e
 * @param pre_e
 * @return
 */
Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e) {
    int i = 2;
    ElemType *p = L.elem + 1;
    while (i < L.length && *p != cur_e) {
        p++;
        i++;
    }
    if (i > L.length) {
        return INFEASIBLE;
    } else {
        *pre_e = *(--p);
        return OK;
    }
}

/**
 * ��ʼ���������Ա� L ����
 * ����������� cur_e �� L �е�Ԫ�أ��Ҳ������һ�������� next_e ���������������ʧ�ܣ�next_e �޶���
 * @param L
 * @param cur_e
 * @param next_e
 * @return
 */
Status NextElem(SqList L, ElemType cur_e, ElemType *next_e) {
    int i = 1;
    ElemType *p = L.elem;
    while (i < L.length - 1 && *p != cur_e) {
        p++;
        i++;
    }
    if (i == L.length) {
        return INFEASIBLE;
    } else {
        *next_e = *++p;
        return OK;
    }
}

/**
 * ��ʼ���������Ա� L ���ڣ��� 1 <= i <= ListLength(L) + 1
 * ����������� L �е� i ��Ԫ��ǰ�����µ�Ԫ�� e��L �ĳ��ȼ� 1
 * @param L
 * @param i
 * @param e
 * @return
 */
Status ListInsert(SqList *L, int i, ElemType e) {
    ElemType *newBase, *p, *q;
    if (i < 1 || i > L->length + 1) {
        return ERROR;
    }
    if (L->length == L->listSize) {
        newBase = realloc(L->elem, (LIST_INIT_SIZE + LIST_INCREMENT) * sizeof(SqList));
        if (!newBase) {
            exit(OVERFLOW);
        }
        L->elem = newBase;
        L->listSize += LIST_INCREMENT;
    }
    q = L->elem + i - 1;
    for (p = L->elem + L->length - 1; p >= q; --p) {
        *(p + 1) = *p;
    }
    *q = e;
    ++L->length;
    return OK;
}

/**
 * ��ʼ���������Ա� L �����ҷǿգ��� 1 <= i <= ListLength(L)
 * ���������ɾ�� L �еĵ� i ��Ԫ�ز��� e ������ֵ��L �ĳ��ȼ� 1
 * @param L
 * @param i
 * @param e
 * @return
 */
Status ListDelete(SqList *L, int i, ElemType *e) {
    ElemType *p, *q;
    if (i < 1 || i > L->length) {
        return ERROR;
    }
    p = L->elem + i - 1;
    *e = *p;
    q = L->elem + L->length - 1;
    for (++p; p <= q; ++p) {
        *(p - 1) = *p;
    }
    --L->length;
    return OK;
}

/**
 * ��ʼ���������Ա� L ����
 * ��������������Ա���б������ڱ��������ж�ÿ��������һ�Σ����������е��� vi() ����Ԫ��
 * @param L
 * @param vi
 */
void TraverseList(SqList L, void(*vi)(ElemType *)) {
    ElemType *p = L.elem;
    for (int i = 0; i < L.length; ++i) {
        vi(p);
        ++p;
    }
    printf("\n");
}

void vi(ElemType *e) {
    printf("%d ", *e);
}

/*--------------------������------------------------*/

/**
 * ���Գ���
 * @return
 */
int main() {
    SqList S;
    int temp;
    ElemType *e;

    InitList(&S);
    printf("%d\n", ListEmpty(S));
    printf("%d\n", ListLength(S));
    temp = ListInsert(&S, 1, 4);
    temp = ListInsert(&S, 2, 8);
    temp = ListInsert(&S, 3, 9);
    temp = ListInsert(&S, 3, 3);
    TraverseList(S, vi);
    temp = GetElem(S, 3, e);
    printf("%d\n", *e);
    temp = PriorElem(S, 3, e);
    printf("%d\n", *e);
    temp = NextElem(S, 3, e);
    printf("%d\n", *e);
    printf("%d\n", LocateElem(S, 8, compare));
    temp = ListDelete(&S, 4, e);
    TraverseList(S, vi);
    ClearList(&S);
    printf("%d\n", ListLength(S));

    DestroyList(&S);
}