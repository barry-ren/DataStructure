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

typedef struct LNode {
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

/**
 * 操作结果：构造一个空的线性表L
 * @param L
 */
void InitList(LinkList *L) {
    *L = (LinkList)malloc(sizeof(struct LNode));
    if (!*L) {
        exit(OVERFLOW);
    }
    (*L)->next = *L;
}

/**
 * 初始条件：线性表 L存在
 * 操作结果：销毁线性表 L
 * @param L
 */
void DestroyList(LinkList *L) {
    LinkList q, p = (*L)->next;
    while (p != *L) {
        q = p->next;
        free(p);
        p = q;
    }
    free(*L);
    *L = NULL;
}

/**
 * 初始条件：线性表 L 存在
 * 操作结果：将 L 置为空表
 * @param L
 */
void ClearList(LinkList *L) {
    LinkList p, q;
    *L = (*L)->next;
    p = (*L)->next;
    while (p != *L) {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = *L;
}

/**
 * 初始条件：线性表 L 存在
 * 操作结果：若 L 为空表，返回 TRUE，否则返回 FALSE
 * @param L
 * @return
 */
Status ListEmpty(LinkList L) {
    if (L->next == L) {
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
int ListLength(LinkList L) {
    int i = 0;
    LinkList p = L->next;
    while (p != L) {
        i++;
        p = p->next;
    }
    return i;
}

/**
 * 初始条件：线性表 L 存在，且 1 <= i <= ListLength(L)
 * 操作结果：用 e 返回 L 中第 i 个元素的值
 * @param L
 * @param i
 * @param e
 * @return
 */
Status GetElem(LinkList L, int i, ElemType *e) {
    LinkList p = L->next->next;
    int j = 1;
    if (i < 0 || i > ListLength(L)) {
        return ERROR;
    }
    while (j < i) {
        p = p->next;
        ++j;
    }
    *e = p->data;
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
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
    int i = 0;
    LinkList p = L->next->next;
    while (p != L->next) {
        i++;
        if (compare(p->data, e)) {
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
 * 初始条件：线性表 L 存在
 * 操作结果：若 cur_e 是 L 中的元素，且不是第一个，则用 pre_e 返回其前驱，否则失败，pre_e 无定义
 * @param L
 * @param cur_e
 * @param pre_e
 * @return
 */
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e) {
    LinkList q, p = L->next->next;
    q = p->next;
    while (q != L->next) {
        if (q->data == cur_e) {
            *pre_e = p->data;
            return OK;
        }
        p = q;
        q = q->next;
    }
    return INFEASIBLE;
}

/**
 * 初始条件：线性表 L 存在
 * 操作结果：若 cur_e 是 L 中的元素，且不是最后一个，则用 next_e 返回其后驱，否则失败，next_e 无定义
 * @param L
 * @param cur_e
 * @param pre_e
 * @return
 */
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e) {
    LinkList p = L->next->next;
    while (p != L) {
        if (p->data == cur_e) {
            *next_e = p->next->data;
            return OK;
        }
        p = p->next;
    }
    return INFEASIBLE;
}

/**
 * 初始条件：线性表 L 存在，且 1 <= i <= ListLength(L) + 1
 * 操作结果：在 L 中第 i 个元素前插入新的元素 e，L 的长度加 1
 * @param L
 * @param i
 * @param e
 * @return
 */
Status ListInsert(LinkList *L, int i, ElemType e) {
    int j = 0;
    LinkList p = *L, s;
    if (i <= 0 || i > ListLength(*L) + 1) {
        return ERROR;
    }
    while (j < i - 1) {
        p = p->next;
        j++;
    }
    s = (LinkList)malloc(sizeof(struct LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

/**
 * 初始条件：线性表 L 存在且非空，且 1 <= i <= ListLength(L)
 * 操作结果：删除 L 中的第 i 个元素并用 e 返回其值，L 的长度减 1
 * @param S
 * @param i
 * @param e
 * @return
 */
Status ListDelete(LinkList *L, int i, ElemType *e) {
    int j = 0;
    LinkList q, p = (*L)->next;
    if (i < 0 || i > ListLength(*L)) {
        return ERROR;
    }
    while (j < i - 1) {
        p = p->next;
        ++j;
    }
    *e = p->next->data;
    q = p->next;
    p->next = q->next;
    free(q);
    return OK;
}

/**
 * 初始条件：线性表 L 存在
 * 操作结果：对线性表进行遍历，在遍历过程中对每个结点访问一次，遍历过程中调用 vi() 操作元素
 * @param L
 * @param vi
 */
void TraverseList(LinkList L, void(*vi)(ElemType)) {
    LinkList p = L->next;
    while (p != L) {
        vi(p->data);
        p = p->next;
    }
    printf("\n");
}

void vi(ElemType e) {
    printf("%d ", e);
}

/**
 * 操纵结果：前插法创建含 n 个元素的单链表
 * @param L
 * @param n
 */
void CreateList_H(LinkList *L, int n) {
    InitList(L);
    LinkList p;
    for (int i = 0; i < n; ++i) {
        p = (LinkList)malloc(sizeof(struct LNode));
        scanf("%d",&p->data);
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

/**
 * 操纵结果：后插法创建含 n 个元素的单链表
 * @param L
 * @param n
 */
void CreateList_R(LinkList *L, int n) {
    InitList(L);
    LinkList p, r = (*L)->next;
    for (int i = 0; i < n; ++i) {
        p = (LinkList)malloc(sizeof(struct LNode));
        if (!p) {
            exit(OVERFLOW);
        }
        scanf("%d", &p->data);
        p->next = *L;
        r->next = p;
        r = p;
    }
}

/*--------------------主函数------------------------*/

/**
 * 测试程序
 * @return
 */
int main() {  // 测试程序只测试函数是否有逻辑错误
    LinkList list;
    int temp;
    ElemType *e;

    CreateList_H(&list, 3);
//    CreateList_R(&list, 3);
    printf("%d\n", ListEmpty(list));
    printf("%d\n", ListLength(list));
    TraverseList(list, vi);
    temp = ListInsert(&list, 1, 99);
    TraverseList(list, vi);
    temp = ListInsert(&list, 5, 100);
    TraverseList(list, vi);
    temp = GetElem(list, 3, e);
    printf("%d\n", *e);
    temp = PriorElem(list, 4, e);
    printf("%d\n", *e);
    temp = NextElem(list, 6, e);
    printf("%d\n", *e);
    printf("%d\n", LocateElem(list, 6, compare));
    temp = ListDelete(&list, 4, e);
    TraverseList(list, vi);
    ClearList(&list);
    printf("%d\n", ListLength(list));

    DestroyList(&list);
}