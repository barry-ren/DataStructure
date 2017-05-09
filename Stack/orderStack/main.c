#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 2

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int Status;
typedef int SElemType;

typedef struct {
    SElemType *base;  //栈底指针
    SElemType *top;  //栈顶指针
    int stackSize;
}SqStack;

Status InitStack(SqStack *S);
Status DestroyStack(SqStack *S);
Status ClearStack(SqStack *S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S);
Status GetTop(SqStack S, SElemType *e);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
Status StackTraverse(SqStack S, void(*vi)(SElemType));

/**
 * 操作结果：构造一个空栈 S。
 * @param S
 * @return
 */
Status InitStack(SqStack *S) {
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SqStack));  //开辟内存空间
    if (!S->base) {
        exit(OVERFLOW);  //开辟失败
    }
    S->top = S->base;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}

/**
 * 初始条件：栈 S 存在
 * 操作结果：栈 S 被销毁
 * @param S
 * @return
 */
Status DestroyStack(SqStack *S) {
    if (S->base) {
        free(S->base);  //释放栈底指针内存空间
    }
    S->top = S->base = NULL;  //栈底栈顶指针置为 NULL
    S->stackSize = 0;
    return OK;
}

/**
 * 初始条件：栈 S 存在
 * 操作结果：将栈 S 清为空栈
 * @param S
 * @return
 */
Status ClearStack(SqStack *S) {
    S->top = S->base;
    return OK;
}

/**
 * 初始条件：栈 S 存在
 * 操作结果：若 S 为空栈，返回 true，否则返回 false
 * @param S
 * @return
 */
Status StackEmpty(SqStack S) {
    if (S.top == S.base) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 初始条件：栈 S 存在
 * 操作结果：返回 S 中元素的个数，即栈的长度
 * @param S
 * @return
 */
int StackLength(SqStack S) {
    return (int) (S.top - S.base);
}

/**
 * 初始条件：栈 S 存在且非空
 * 操作结果：返回栈顶元素，不修改栈顶指针
 * @param S
 * @return
 */
Status GetTop(SqStack S, SElemType *e) {
    if (S.top != S.base) {
        *e = *(S.top - 1);
        return OK;
    }
    return ERROR;

}

/**
 * 初始条件：栈 S 存在
 * 操作结果：插入元素 e 为新的栈顶元素
 * @param S
 * @param e
 * @return
 */
Status Push(SqStack *S, SElemType e) {
    if ((S->top - S->base) >= S->stackSize) { //判读栈是否满
        S->base = (SElemType *)realloc(S->base, (S->stackSize + STACK_INCREMENT) * sizeof(SqStack));
        if (!S->base) {
            return ERROR;
        }
        S->top = S->base + S->stackSize;
        S->stackSize += STACK_INCREMENT;
    }
    *S->top++ = e;
    return OK;
}

/**
 * 初始条件：栈 S 存在且非空
 * 操作结果：删除 S 的栈顶元素，并用 e 返回其值
 * @param S
 * @param e
 * @return
 */
Status Pop(SqStack *S, SElemType *e) {
    if (S->top == S->base) {  //栈为空
        return ERROR;
    }
    *e = *--S->top;
    return OK;
}

/**
 * 初始条件：栈 S 存在且非空
 * 操作结果：从栈底到栈顶依次对 S 的每个元素进行访问
 * @param S
 * @param vi
 */
Status StackTraverse(SqStack S, void(*vi)(SElemType)) {
    while (S.top > S.base) {  //遍历栈中元素
        vi(*S.base++);
    }
    printf("\n");
    return OK;
}

/**
 * 遍历函数
 * @param e
 */
void vi(SElemType e) {
    printf("%d ", e);
}

/**
 * 主函数，测试程序
 * @return
 */
int main() {
    SqStack s;
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