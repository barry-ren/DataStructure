#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE 0

typedef int Status;
typedef int SElemType;

typedef struct StackNode {
    SElemType data;  //数据域
    struct StackNode *next;  //指针域
}StackNode, *LinkStack;

Status InitStack(LinkStack *S);
Status DestroyStack(LinkStack *S);
Status ClearStack(LinkStack *S);
Status StackEmpty(LinkStack S);
int StackLength(LinkStack S);
Status GetTop(LinkStack S, SElemType *e);
Status Push(LinkStack *S, SElemType e);
Status Pop(LinkStack *S, SElemType *e);
void StackTraverse(LinkStack S, void(*vi)(SElemType));

/**
 * 操作结果：构造一个空栈 S
 * @param L
 * @return
 */
Status InitStack(LinkStack *S) {
    S = NULL;  //构造一个空栈，栈顶指针置空
    return OK;
}

/**
 * 初始条件：栈 S 存在
 * 操作结果：栈 S 被销毁
 * @param S
 * @return
 */
Status DestroyStack(LinkStack *S) {
    LinkStack p;
    while (*S) {  //未到栈底
        p = (*S)->next;
        free(*S);  //释放栈顶空间
        *S = p;
    }
    return OK;
}

/**
 * 初始条件：栈 S 存在
 * 操作结果：将栈 S 清空
 * @param S
 */
Status ClearStack(LinkStack *S) {
    LinkStack q, p = (*S)->next;  // p 指向栈顶元素
    while (p) {  //未到栈底
        q = p->next;
        free(p);
        p = q;
    }
    (*S) = NULL;
    return OK;
}

/**
 * 初始条件：栈 S 存在
 * 操作结果：若 S 是空栈，返回 true，否则返回 false
 * @param S
 * @return
 */
Status StackEmpty(LinkStack S) {
    if (S == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 初始条件：栈 S 存在
 * 操作结果：返回栈 S 长度
 * @param S
 * @return
 */
int StackLength(LinkStack S) {
    int i = 0;  //计数器
    LinkStack p = S;  //p指向栈顶元素
    while (p) {  //未到栈底
        i++;
        p = p->next;
    }
    return i;
}

/**
 * 初始条件：栈 S 存在且非空
 * 操作结果；用 e 返回栈 S 的栈顶元素，不修改栈顶指针
 * @param S
 * @return
 */
Status GetTop(LinkStack S, SElemType *e) {
    if (S) {  //S 非空
        *e = S->data;
        return OK;
    }
    return ERROR;
}

/**
 * 初始条件：栈 S 存在
 * 操作结果：插入元素 e 为新的栈顶元素
 * @param L
 * @param e
 * @return
 */
Status Push(LinkStack *S, SElemType e) {
    LinkStack p;
    p = (LinkStack)malloc(sizeof(struct StackNode));  //生成新结点
    p->data = e;
    p->next = *S;  //将新结点插入栈顶
    *S = p;  //修改栈顶指针
    return OK;
}

/**
 * 初始条件：栈 S 存在且非空
 * 操作结果：删除栈顶元素，并用 e 返回且值
 * @param S
 * @param e
 * @return
 */
Status Pop(LinkStack *S, SElemType *e) {
    LinkStack p;
    if (!S) {
        return ERROR;
    }
    *e = (*S)->data;  //返回栈顶元素
    p = *S;  //p 临时保存栈顶空间，以备释放
    *S = (*S)->next;  //修改栈顶指针
    free(p);  //释放原栈栈顶空间
    return OK;
}

/**
 * 初始条件：栈 S 存在且非空
 * 操作结果：从栈底到栈顶依次对 S 中的每个元素进行访问
 * @param S
 * @param vi
 */
void StackTraverse(LinkStack S, void(*vi)(SElemType)) {
    LinkStack p = S;  //p 指向栈顶
    while (p) {
        vi(p->data);
        p = p->next;
    }
    printf("\n");
}

void vi(SElemType e) {
    printf("%d ", e);
}

/**
 * 主函数，测试程序
 * @return
 */
int main() {
    LinkStack s = NULL;
    SElemType e;

    InitStack(&s);
    printf("栈的长度：%d\n", StackLength(s));
    printf("栈是否为空：%d\n", StackEmpty(s));
    Push(&s, 3);
    Push(&s, 4);
    Push(&s, 5);
    Push(&s, 6);
    StackTraverse(s,vi);
    printf("栈的长度：%d\n", StackLength(s));
    printf("栈是否为空：%d\n", StackEmpty(s));
    GetTop(s, &e);
    printf("栈顶元素：%d\n", e);
    printf("栈的长度：%d\n", StackLength(s));
    Pop(&s, &e);
    StackTraverse(s, vi);
    ClearStack(&s);
    printf("栈的长度：%d\n", StackLength(s));
    printf("栈是否为空：%d\n", StackEmpty(s));

    DestroyStack(&s);
}