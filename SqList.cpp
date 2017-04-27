#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef int ElemType;

#define OK 1
#define ERROR 0
#define OVERFLOW -1

#define MAX_SIZE 100
#define INCREMENT 10

typedef struct {
    ElemType *elem;
    int length;
    int size;
}SqList;

Status initList(SqList &L);
int locateElem(const SqList &L, ElemType e);
Status listInsert(SqList &L, int i, ElemType e);
Status listDelete(SqList &L, int i);
void printList(const SqList &L);
/**
 * 初始化顺序表
 * @param L
 * @return
 */
Status initList(SqList &L) {
    L.elem = (ElemType *)malloc(MAX_SIZE * sizeof(SqList));
    if (!L.elem) {
        exit(OVERFLOW);
    }
    L.length = 0;
    int a, b;
    printf("请输入初始化元素的个数：\n");
    scanf("%d", &a);
    printf("请依次输入%d个元素:", a);
    for (int i = 0; i < a; i++) {
        scanf("%d", &L.elem[i]);
    }
    L.length = a;
    L.size = MAX_SIZE;
    return OK;
}

/**
 * 顺序表的查找
 * @param L
 * @param e
 * @return
 */
int locateElem(const SqList &L, ElemType e) {
    for (int i = 0; i < L.length; ++i) {
        if (L.elem[i] == e)  {
            return i + 1;
        }
    }
    return 0;
}

/**
 * 顺序表的插入
 * @param L
 * @param i
 * @param e
 * @return
 */
Status listInsert(SqList &L, int i, ElemType e) {
    if (i < 1 || i > L.length + 1) {
        return ERROR;
    }
    if (L.length == MAX_SIZE) {
        L.elem = (ElemType *)realloc(L.elem, (MAX_SIZE + INCREMENT) * sizeof(SqList));
    }
    for (int j = L.length - 1; j >= i - 1; j--) {
        L.elem[j + 1] = L.elem[j];
        L.size = MAX_SIZE + INCREMENT;
    }
    L.elem[i - 1] = e;
    ++L.length;
    return OK;
}

/**
 * 顺序表的删除，按照位序
 * @param L
 * @param i
 * @param e
 * @return
 */
Status listDelete(SqList &L, int i, ElemType &e) {
    if (i < 1 || i > L.length) {
        return ERROR;
    }
    e =  L.elem[i - 1];
    for (int j = i; j <= L.length - 1; j++) {
        L.elem[j - 1] = L.elem[j];
    }
    --L.length;
    return OK;
}

/**
 * 输出顺序表
 * @param L
 */
void printList(const SqList &L) {
    for (int i = 0; i < L.length; i++) {
        printf("[%d,%d]", i + 1, L.elem[i]);
    }
    printf("\n");
}

int main() {
    SqList S;
    int flag = 1, choose, loc;
    ElemType e;
    Status temp;
    printf("实现顺序结构的线性表。");
    printf("实现查找、插入、删除等基本功能。\n");
    initList(S);
    while (flag) {
        printf("请选择：\n");
        printf("1.显示所有元素\n");
        printf("2.插入一个元素\n");
        printf("3.删除一个元素\n");
        printf("4.查找一个元素\n");
        printf("5.退出程序    \n");
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                printList(S);
                break;
            case 2: {
                printf("请输入要插入的元素和插入位置:\n");
                printf("格式：字符，位置；例如:a,2\n");
                scanf("%d,%d", &e, &loc);
                temp = listInsert(S, loc, e);
                if (temp) {
                    printf("插入成功!\n");
                    printList(S);
                } else {
                    printf("插入失败!\n");
                }
                break;
            }
            case 3: {
                printf("请输入要删除元素的位置:");
                scanf("%d", &loc);
                temp = listDelete(S, loc, e);
                if(temp){
                    printf("删除了一个元素:%d\n", e);
                } else {
                    printf("该元素不存在!\n");
                }
                printList(S);
                break;
            }
            case 4: {
                printf("请输入要查找的元素:");
                scanf("%d", &e);
                loc = locateElem(S, e);
                if (loc != -1) {
                    printf("该元素所在位置:%d\n",loc + 1);
                } else {
                    printf("%d不存在!\n", e);
                }
                break;
            }
            case 5:
                flag = 0;
                printf("程序结束，按任意键退出!\n");
                printList(S);
                break;
            default:
                printf("无效选择，请重新输入：\n");
        }
    }
}
