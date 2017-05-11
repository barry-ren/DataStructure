#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE 0

typedef int Status;
typedef int QElemType;

typedef struct QNode {
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
    QueuePtr front;  //��ͷָ��
    QueuePtr rear;  //��βָ��
}LinkQueue;

Status InitQueue(LinkQueue *);
Status DestroyQueue(LinkQueue *);
Status ClearQueue(LinkQueue *);
Status QueueEmpty(LinkQueue );
int QueueLength(LinkQueue);
Status GetHead(LinkQueue, QElemType *);
Status EnQueue(LinkQueue *, QElemType);
Status DeQueue(LinkQueue *, QElemType *);
void QueueTraverse(LinkQueue , void(*vi)(QElemType));

/**
 * �������������һ���ն��� Q
 * @param Q
 * @return
 */
Status InitQueue(LinkQueue *Q) {
    if (!(Q->front = Q->rear = (QueuePtr)malloc(sizeof(struct QNode)))) {
        exit(OVERFLOW);
    }
    Q->front->next = NULL;
    return OK;
}

/**
 * ��ʼ���������� Q ����
 * ������������� Q ������
 * @param Q
 * @return
 */
Status DestroyQueue(LinkQueue *Q) {
    while (Q->front) {  //ָ���βʱ����ѭ��
        Q->rear = Q->front->next;  // ��βָ��ָ���ͷָ�����һ�����
        free(Q->front);  //�ͷŶ�ͷ���
        Q->front = Q->rear;  //�޸Ķ�ͷָ��
    }
    return OK;
}

/**
 * ��ʼ���������� Q ����
 * �����������ն��� Q
 * @param Q
 * @return
 */
Status ClearQueue(LinkQueue *Q) {
    QueuePtr p, q;
    Q->rear = Q->front;  //��βָ��ָ��ͷ���
    p = Q->front->next;  //p ָ����е�һ��Ԫ��
    Q->front->next = NULL;  //��ͷָ�� next ���ÿ�
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    return OK;

}

/**
 * ��ʼ���������� Q ����
 * ����������� Q Ϊ�ն��У��򷵻� true�����򷵻� false
 * @param Q
 * @return
 */
Status QueueEmpty(LinkQueue Q) {
    if (Q.front->next == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * ��ʼ���������� Q ����
 * ������������� Q ��Ԫ�ظ����������г���
 * @param Q
 * @return
 */
int QueueLength(LinkQueue Q) {
    int i = 0;  //������
    QueuePtr p = Q.front->next;  //p ָ���ͷԪ��
    while (p) {
        i++;
        p = p->next;
    }
    return i;
}

/**
 * ��ʼ���������� Q �����ҷǿ�
 * ������������� Q �ж�ͷԪ��
 * @param Q
 * @param e
 * @return
 */
Status GetHead(LinkQueue Q, QElemType *e) {
    if (Q.front != Q.rear) {
        *e = Q.front->next->data;
        return OK;
    }
    return INFEASIBLE;
}

/**
 * ��ʼ���������� Q ����
 * ���������������Ԫ�� e Ϊ Q ���¶�βԪ��
 * @param Q
 * @param e
 * @return
 */
Status EnQueue(LinkQueue *Q, QElemType e) {
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(struct QNode));  //�����½��
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;  //���½����뵽��β
    Q->rear = p;  //�޸Ķ�βָ��
    return OK;
}

/**
 * ��ʼ���������� Q �����ҷǿ�
 * ���������ɾ�� Q �Ķ�ͷԪ�أ����� e ����
 * @param Q
 * @param e
 * @return
 */
Status DeQueue(LinkQueue *Q, QElemType *e) {
    QueuePtr p;
    if (Q->front == Q->rear) {  //�ж��Ƿ�Ϊ�ն���
        return ERROR;
    }
    p = Q->front->next;  //p ָ���ͷԪ��
    *e = p->data;
    Q->front->next = p->next;  //�޸�ͷָ��
    if (Q->rear == p) {  //���ɾ�����Ƕ������һ��Ԫ��
        Q->rear = Q->front;  //��βָ��ָ��ͷ���
    }
    free(p);
    return OK;
}

/**
 * ��ʼ���������� Q �����ҷǿ�
 * ����������Ӷ�ͷ����β�����ζԱ���������ÿ��Ԫ��
 * @param Q
 * @param vi
 */
void QueueTraverse(LinkQueue Q, void(*vi)(QElemType)) {
    QueuePtr p = Q.front->next;  //p ָ���ͷԪ��
    while (p) {
        vi(p->data);  //����
        p = p->next;
    }
    printf("\n");
}

/**
 * ��������
 * @param e
 */
void vi(QElemType e) {
    printf("%d ",e);
}

/**
 * �����������Գ���
 * @return
 */
int main() {
    LinkQueue q;
    QElemType e;

    InitQueue(&q);
    printf("���еĳ��ȣ�%d\n", QueueLength(q));
    printf("�����Ƿ�Ϊ�գ�%d\n", QueueEmpty(q));
    EnQueue(&q, 3);
    EnQueue(&q, 4);
    EnQueue(&q, 5);
    EnQueue(&q, 6);
    QueueTraverse(q, vi);
    printf("���еĳ��ȣ�%d\n", QueueLength(q));
    printf("�����Ƿ�Ϊ�գ�%d\n", QueueEmpty(q));
    GetHead(q, &e);
    printf("���е�ͷԪ�أ�%d\n", e);
    DeQueue(&q, &e);
    QueueTraverse(q, vi);
    ClearQueue(&q);
    printf("���еĳ��ȣ�%d\n", QueueLength(q));
    printf("�����Ƿ�Ϊ�գ�%d\n", QueueEmpty(q));

    DestroyQueue(&q);
}