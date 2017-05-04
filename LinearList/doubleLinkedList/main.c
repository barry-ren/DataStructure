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
 * 操作结果：构造一个空的双向链表 L
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
 * 初始条件：双向链表 L存在
 * 操作结果：销毁双向链表 L
 * @param L
 */
void DestroyList(DuLinkList *L) {
    DuLinkList q, p = (*L)->next; //p 指向第一个节点
    while (p != *L) {
        q = p->next;
        free(p);
        p = q;
    }
    free(*L);
    *L = NULL;
}

/**
 * 初始条件：双向链表 L 存在
 * 操作结果：将 L 置空
 * @param L
 */
void ClearList(DuLinkList L) {
    DuLinkList q, p = L->next; //p 指向第一个节点
    while (p != L) { //p 没有到表头
        q = p->next;
        free(p);
        p = q;
    }
    L->next = L->prior = L; //头节点两个指针均指向本身
}

/**
 * 初始条件：双向链表 L 存在
 * 操作结果：若 L 为空表，返回 TRUE，否则返回 FALSE
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
 * 初始条件：双向链表表 L 存在
 * 操作结果：返回 L 中的数据元素个数
 * @param L
 * @return
 */
int ListLength(DuLinkList L) {
    int i = 0;
    DuLinkList p = L->next; //p 指向第一个节点
    while (p != L) { //p 没有到表头
        i++;
        p = p->next;
    }
    return i;
}

/**
 * 初始条件：双向链表表 L 存在，且 1 <= i <= ListLength(L)
 * 操作结果：用 e 返回 L 中第 i 个元素的值
 * @param L
 * @param i
 * @param e
 * @return
 */
Status GetElem(DuLinkList L, int i, ElemType *e) {
    DuLinkList p = L->next; //p 指向第一个节点
    int j = 1; //计数器
    while (p != L && j < i) { //顺指针向后查询，直到 p 指向第 i 个元素或 p 指向头结点
        p = p->next;
        ++j;
    }
    if (p == L || j > i) { //第 i 个元素不存在
        return ERROR;
    }
    *e = p->data; //取得第 i 个元素
    return OK;
}

/**
 * 初始条件：双向链表 L 存在
 * 操作结果：返回 L 中第一个值与元素 e 相同的元素在 L 中的位置。若元素不存在，则返回 0
 * @param L
 * @param e
 * @param compare
 * @return
 */
int LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
    int i = 0;
    DuLinkList p = L->next; //p 指向第一个节点
    while (p != L) { //p 没有到表头
        i++;
        if (compare(p->data, e)) { //找到该元素
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
 * 初始条件：双向链表 L 存在
 * 操作结果：若 cur_e 是 L 中的元素，且不是第一个，则用 pre_e 返回其前驱，否则失败，pre_e 无定义
 * @param L
 * @param cur_e
 * @param pre_e
 * @return
 */
Status PriorElem(DuLinkList L, ElemType cur_e, ElemType *pre_e) {
    DuLinkList p = L->next->next; //p 指向第二个元素
    while (p != L) {
        if (p->data == cur_e) {
            *pre_e = p->prior->data; //返回前驱
            return OK;
        }
        p = p->next;
    }
    return INFEASIBLE;
}

/**
 * 初始条件：双向链表表 L 存在
 * 操作结果：若 cur_e 是 L 中的元素，且不是最后一个，则用 next_e 返回其后驱，否则失败，next_e 无定义
 * @param L
 * @param cur_e
 * @param pre_e
 * @return
 */
Status NextElem(DuLinkList L, ElemType cur_e, ElemType *next_e) {
    DuLinkList p = L->next->next; //p 指向第二个元素
    while (p != L) {
        if (p->prior->data == cur_e) {
            *next_e = p->data; //返回后驱
            return OK;
        }
        p = p->next;
    }
    return INFEASIBLE;
}

/**
 * 返回 L 中第 i 个元素的地址，若 i = 0 返回头结点，若 i 不存在，返回 NULL
 * @param L
 * @param i
 * @return
 */
DuLinkList GetElemP(DuLinkList L, int i) {
    DuLinkList p = L; //p 指向头结点
    if (i < 0 || i > ListLength(L)) { //i 值不合法
        return NULL;
    }
    for (int j = 1; j <= i; j++) {
        p = p->next;
    }
    return p;
}

/**
 * 初始条件：双向链表 L 存在，且 1 <= i <= ListLength(L) + 1
 * 操作结果：在 L 中第 i 个元素前插入新的元素 e，L 的长度加 1
 * @param L
 * @param i
 * @param e
 * @return
 */
Status ListInsert(DuLinkList L, int i, ElemType e) {
    DuLinkList p, s;
    if (i < 1 || i > (ListLength(L) + 1)) { //i 值不合法
        return ERROR;
    }
    p = GetElemP(L, i - 1);
    if (!p) { //在 L 中确定第 i 个元素的前驱位置指针 p
        return ERROR; // p = NULL 时，第 i 个元素不存在
    }
    s = (DuLinkList)malloc(sizeof(struct DuLNode));
    if (!s) {
        exit(OVERFLOW);
    }
    s->data = e;
    s->prior = p; //在 i - 1 个元素后插入
    s->next = p->next;
    p->next->prior = s;
    p->next = s;
    return OK;
}

/**
 * 初始条件：双向链表 L 存在且非空，且 1 <= i <= ListLength(L)
 * 操作结果：删除 L 中的第 i 个元素并用 e 返回其值，L 的长度减 1
 * @param S
 * @param i
 * @param e
 * @return
 */
Status ListDelete(DuLinkList L, int i, ElemType *e) {
    DuLinkList p;
    p = GetElemP(L, i);
    if (!p) { //在 L 中确定第 i 个元素的位置指针 p
        return ERROR; //p = NULL 是，第 i 个元素不存在，也就是 i 值不合法
    }
    *e = p->data;
    p->prior->next = p->next; //修改被删除结点的前驱结点的后继指针
    p->next->prior = p->prior; //修改被删除结点的后继结点的前驱指针
    free(p);
    return OK;
}

/**
 * 初始条件：双向链表 L 存在
 * 操作结果：由头结点出发，对链表进行遍历，在遍历过程中对每个结点访问一次，遍历过程中调用 vi() 操作元素
 * @param L
 * @param vi
 */
void TraverseList(DuLinkList L, void(*vi)(ElemType)) {
    DuLinkList p = L->next; //p 指向第一个元素
    while (p != L) { //遍历
        vi(p->data);
        p = p->next;
    }
    printf("\n");
}

void vi(ElemType e) {
    printf("%d ", e);
}

/**
 * 操纵结果：前插法创建含 n 个元素的双向链表
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
 * 操纵结果：后插法创建含 n 个元素的单链表
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

/*--------------------主函数------------------------*/

/**
 * 测试程序
 * @return
 */
int main() {  // 测试程序只测试函数是否有逻辑错误
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