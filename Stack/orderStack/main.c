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
    SElemType *base;  //ջ��ָ��
    SElemType *top;  //ջ��ָ��
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
 * �������������һ����ջ S��
 * @param S
 * @return
 */
Status InitStack(SqStack *S) {
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SqStack));  //�����ڴ�ռ�
    if (!S->base) {
        exit(OVERFLOW);  //����ʧ��
    }
    S->top = S->base;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}

/**
 * ��ʼ������ջ S ����
 * ���������ջ S ������
 * @param S
 * @return
 */
Status DestroyStack(SqStack *S) {
    if (S->base) {
        free(S->base);  //�ͷ�ջ��ָ���ڴ�ռ�
    }
    S->top = S->base = NULL;  //ջ��ջ��ָ����Ϊ NULL
    S->stackSize = 0;
    return OK;
}

/**
 * ��ʼ������ջ S ����
 * �����������ջ S ��Ϊ��ջ
 * @param S
 * @return
 */
Status ClearStack(SqStack *S) {
    S->top = S->base;
    return OK;
}

/**
 * ��ʼ������ջ S ����
 * ����������� S Ϊ��ջ������ true�����򷵻� false
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
 * ��ʼ������ջ S ����
 * ������������� S ��Ԫ�صĸ�������ջ�ĳ���
 * @param S
 * @return
 */
int StackLength(SqStack S) {
    return (int) (S.top - S.base);
}

/**
 * ��ʼ������ջ S �����ҷǿ�
 * �������������ջ��Ԫ�أ����޸�ջ��ָ��
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
 * ��ʼ������ջ S ����
 * �������������Ԫ�� e Ϊ�µ�ջ��Ԫ��
 * @param S
 * @param e
 * @return
 */
Status Push(SqStack *S, SElemType e) {
    if ((S->top - S->base) >= S->stackSize) { //�ж�ջ�Ƿ���
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
 * ��ʼ������ջ S �����ҷǿ�
 * ���������ɾ�� S ��ջ��Ԫ�أ����� e ������ֵ
 * @param S
 * @param e
 * @return
 */
Status Pop(SqStack *S, SElemType *e) {
    if (S->top == S->base) {  //ջΪ��
        return ERROR;
    }
    *e = *--S->top;
    return OK;
}

/**
 * ��ʼ������ջ S �����ҷǿ�
 * �����������ջ�׵�ջ�����ζ� S ��ÿ��Ԫ�ؽ��з���
 * @param S
 * @param vi
 */
Status StackTraverse(SqStack S, void(*vi)(SElemType)) {
    while (S.top > S.base) {  //����ջ��Ԫ��
        vi(*S.base++);
    }
    printf("\n");
    return OK;
}

/**
 * ��������
 * @param e
 */
void vi(SElemType e) {
    printf("%d ", e);
}

/**
 * �����������Գ���
 * @return
 */
int main() {
    SqStack s;
    SElemType e;

    InitStack(&s);
    printf("ջ�ĳ��ȣ�%d\n", StackLength(s));
    printf("ջ�Ƿ�Ϊ�գ�%d\n", StackEmpty(s));
    Push(&s, 3);
    Push(&s, 4);
    Push(&s, 5);
    Push(&s, 6);
    StackTraverse(s,vi);
    printf("ջ�ĳ��ȣ�%d\n", StackLength(s));
    printf("ջ�Ƿ�Ϊ�գ�%d\n", StackEmpty(s));
    GetTop(s, &e);
    printf("ջ��Ԫ�أ�%d\n", e);
    printf("ջ�ĳ��ȣ�%d\n", StackLength(s));
    Pop(&s, &e);
    StackTraverse(s, vi);
    ClearStack(&s);
    printf("ջ�ĳ��ȣ�%d\n", StackLength(s));
    printf("ջ�Ƿ�Ϊ�գ�%d\n", StackEmpty(s));

    DestroyStack(&s);
}