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

typedef struct {
    QElemType *base;  //�洢�ռ����ַ
    int front;  //ͷָ��
    int rear;  //βָ��
    int QueueSize;  //��������
}SqQueue;

Status InitQueue(SqQueue *);
Status DestroyQueue(SqQueue *);
Status ClearQueue(SqQueue *);
Status QueueEmpty(SqQueue );
int QueueLength(SqQueue);
Status GetHead(SqQueue, QElemType *);
Status EnQueue(SqQueue *, QElemType);
Status DeQueue(SqQueue *, QElemType *);
void QueueTraverse(SqQueue , void(*vi)(QElemType));

/**
 * �������������һ���ն��� Q
 * @param e
 * @return
 */
Status InitQueue(SqQueue *Q) {
    Q->base = (QElemType *)malloc(MAX_QUEUE_SIZE * sizeof(SqQueue));
    if (!Q->base) {
        exit(OVERFLOW);
    }
    Q->front = Q->rear = 0;  //ͷָ��βָ����Ϊ�㣬����Ϊ��
    return OK;
}

/**
 * ��ʼ���������� Q ����
 * ������������� Q ������
 * @param Q
 * @return
 */
Status DestroyQueue(SqQueue *Q) {
    if (Q->base) {
        free(Q->base);
    }
    Q->base = NULL;
    Q->front = Q->rear = 0;
}

/**
 * ��ʼ���������� Q ����
 * �����������ն��� Q
 * @param Q
 * @return
 */
Status ClearQueue(SqQueue *Q) {
    Q->front = Q->rear = 0;
}

/**
 * ��ʼ���������� Q ����
 * ����������� Q Ϊ�ն��У��򷵻� true�����򷵻� false
 * @param Q
 * @return
 */
Status QueueEmpty(SqQueue Q) {
    if (Q.front == Q.rear) {
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
int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

/**
 * ��ʼ���������� Q �����ҷǿ�
 * ������������� Q �ж�ͷԪ��
 * @param Q
 * @param e
 * @return
 */
Status GetHead(SqQueue Q, QElemType *e) {
    if (Q.front == Q.rear) {
        return ERROR;
    }
    *e = Q.base[Q.front];
    return OK;
}

/**
 * ��ʼ���������� Q ����
 * ���������������Ԫ�� e Ϊ Q ���¶�βԪ��
 * @param Q
 * @param e
 * @return
 */
Status EnQueue(SqQueue *Q, QElemType e) {
    if ((Q->rear + 1) % MAX_QUEUE_SIZE == Q->front) {
        return ERROR;  //��βָ����ѭ�������ϼ� 1 �����ͷָ�룬��ʾ����
    }
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;  //��βָ��� 1
    return OK;
}

/**
 * ��ʼ���������� Q �����ҷǿ�
 * ���������ɾ�� Q �Ķ�ͷԪ�أ����� e ����
 * @param Q
 * @param e
 * @return
 */
Status DeQueue(SqQueue *Q, QElemType *e) {
    if (Q->front == Q->rear) {
        return ERROR;
    }
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAX_QUEUE_SIZE;  //��ͷָ��� 1
    return OK;
}

/**
 * ��ʼ���������� Q �����ҷǿ�
 * ����������Ӷ�ͷ����β�����ζԱ���������ÿ��Ԫ��
 * @param Q
 * @param vi
 */
void QueueTraverse(SqQueue Q, void(*vi)(QElemType)) {
    int i = Q.front;
    while (i != Q.rear) {
        vi(Q.base[i]);  //����
        i = (i + 1) % MAX_QUEUE_SIZE;
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
    SqQueue q;
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

