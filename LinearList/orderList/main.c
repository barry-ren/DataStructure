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
 * 操作结果：构造一个空的顺序表 L
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
 * 初始条件：线性表 L存在
 * 操作结果：销毁线性表 L
 * @param L
 */
void DestroyList(SqList *L) {
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listSize = 0;
}

/**
 * 初始条件：线性表 L 存在
 * 操作结果：将 L 置为空表
 * @param L
 */
void ClearList(SqList *L) {
    L->length = 0;
}

/**
 * 初始条件：线性表 L 存在
 * 操作结果：若 L 为空表，返回 TRUE，否则返回 FALSE
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
 * 初始条件：线性表 L 存在
 * 操作结果：返回 L 中的数据元素个数
 * @param L
 * @return
 */
int ListLength(SqList L) {
    return L.length;
}

/**
 * 初始条件：线性表 L 存在，且 1 <= i <= ListLength(L)
 * 操作结果：用 e 返回 L 中第 i 个元素的值
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
 * 初始条件：线性表 L 存在
 * 操作结果：返回 L 中第一个值与元素 e 相同的元素在 L 中的位置。若元素不存在，则返回 0
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
 * 初始条件：线性表 L 存在
 * 操作结果：若 cur_e 是 L 中的元素，且不是第一个，则用 pre_e 返回其前驱，否则失败，pre_e 无定义
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
 * 初始条件：线性表 L 存在
 * 操作结果：若 cur_e 是 L 中的元素，且不是最后一个，则用 next_e 返回其后驱，否则失败，next_e 无定义
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
 * 初始条件：线性表 L 存在，且 1 <= i <= ListLength(L) + 1
 * 操作结果：在 L 中第 i 个元素前插入新的元素 e，L 的长度加 1
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
 * 初始条件：线性表 L 存在且非空，且 1 <= i <= ListLength(L)
 * 操作结果：删除 L 中的第 i 个元素并用 e 返回其值，L 的长度减 1
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
 * 初始条件：线性表 L 存在
 * 操作结果：对线性表进行遍历，在遍历过程中对每个结点访问一次，遍历过程中调用 vi() 操作元素
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

/*--------------------主函数------------------------*/

/**
 * 测试程序
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