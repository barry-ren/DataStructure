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
    SElemType data;  //������
    struct StackNode *next;  //ָ����
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
 * �������������һ����ջ S
 * @param L
 * @return
 */
Status InitStack(LinkStack *S) {
    S = NULL;  //����һ����ջ��ջ��ָ���ÿ�
    return OK;
}

/**
 * ��ʼ������ջ S ����
 * ���������ջ S ������
 * @param S
 * @return
 */
Status DestroyStack(LinkStack *S) {
    LinkStack p;
    while (*S) {  //δ��ջ��
        p = (*S)->next;
        free(*S);  //�ͷ�ջ���ռ�
        *S = p;
    }
    return OK;
}

/**
 * ��ʼ������ջ S ����
 * �����������ջ S ���
 * @param S
 */
Status ClearStack(LinkStack *S) {
    LinkStack q, p = (*S)->next;  // p ָ��ջ��Ԫ��
    while (p) {  //δ��ջ��
        q = p->next;
        free(p);
        p = q;
    }
    (*S) = NULL;
    return OK;
}

/**
 * ��ʼ������ջ S ����
 * ����������� S �ǿ�ջ������ true�����򷵻� false
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
 * ��ʼ������ջ S ����
 * �������������ջ S ����
 * @param S
 * @return
 */
int StackLength(LinkStack S) {
    int i = 0;  //������
    LinkStack p = S;  //pָ��ջ��Ԫ��
    while (p) {  //δ��ջ��
        i++;
        p = p->next;
    }
    return i;
}

/**
 * ��ʼ������ջ S �����ҷǿ�
 * ����������� e ����ջ S ��ջ��Ԫ�أ����޸�ջ��ָ��
 * @param S
 * @return
 */
Status GetTop(LinkStack S, SElemType *e) {
    if (S) {  //S �ǿ�
        *e = S->data;
        return OK;
    }
    return ERROR;
}

/**
 * ��ʼ������ջ S ����
 * �������������Ԫ�� e Ϊ�µ�ջ��Ԫ��
 * @param L
 * @param e
 * @return
 */
Status Push(LinkStack *S, SElemType e) {
    LinkStack p;
    p = (LinkStack)malloc(sizeof(struct StackNode));  //�����½��
    p->data = e;
    p->next = *S;  //���½�����ջ��
    *S = p;  //�޸�ջ��ָ��
    return OK;
}

/**
 * ��ʼ������ջ S �����ҷǿ�
 * ���������ɾ��ջ��Ԫ�أ����� e ������ֵ
 * @param S
 * @param e
 * @return
 */
Status Pop(LinkStack *S, SElemType *e) {
    LinkStack p;
    if (!S) {
        return ERROR;
    }
    *e = (*S)->data;  //����ջ��Ԫ��
    p = *S;  //p ��ʱ����ջ���ռ䣬�Ա��ͷ�
    *S = (*S)->next;  //�޸�ջ��ָ��
    free(p);  //�ͷ�ԭջջ���ռ�
    return OK;
}

/**
 * ��ʼ������ջ S �����ҷǿ�
 * �����������ջ�׵�ջ�����ζ� S �е�ÿ��Ԫ�ؽ��з���
 * @param S
 * @param vi
 */
void StackTraverse(LinkStack S, void(*vi)(SElemType)) {
    LinkStack p = S;  //p ָ��ջ��
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
 * �����������Գ���
 * @return
 */
int main() {
    LinkStack s = NULL;
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