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
    QElemType *base;  //存储空间基地址
    int front;  //头指针
    int rear;  //尾指针
    int QueueSize;  //队列容量
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
 * 操作结果：构造一个空队列 Q
 * @param e
 * @return
 */
Status InitQueue(SqQueue *Q) {
    Q->base = (QElemType *)malloc(MAX_QUEUE_SIZE * sizeof(SqQueue));
    if (!Q->base) {
        exit(OVERFLOW);
    }
    Q->front = Q->rear = 0;  //头指针尾指针置为零，队列为空
    return OK;
}

/**
 * 初始条件：队列 Q 存在
 * 操作结果：队列 Q 被销毁
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
 * 初始条件：队列 Q 存在
 * 操作结果：清空队列 Q
 * @param Q
 * @return
 */
Status ClearQueue(SqQueue *Q) {
    Q->front = Q->rear = 0;
}

/**
 * 初始条件：队列 Q 存在
 * 操作结果：若 Q 为空队列，则返回 true，否则返回 false
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
 * 初始条件：队列 Q 存在
 * 操作结果：返回 Q 中元素个数，即队列长度
 * @param Q
 * @return
 */
int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

/**
 * 初始条件：队列 Q 存在且非空
 * 操作结果：返回 Q 中队头元素
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
 * 初始条件：队列 Q 存在
 * 操作结果：插入入元素 e 为 Q 的新队尾元素
 * @param Q
 * @param e
 * @return
 */
Status EnQueue(SqQueue *Q, QElemType e) {
    if ((Q->rear + 1) % MAX_QUEUE_SIZE == Q->front) {
        return ERROR;  //队尾指针在循环意义上加 1 后等于头指针，表示队满
    }
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;  //队尾指针加 1
    return OK;
}

/**
 * 初始条件：队列 Q 存在且非空
 * 操作结果：删除 Q 的队头元素，且用 e 返回
 * @param Q
 * @param e
 * @return
 */
Status DeQueue(SqQueue *Q, QElemType *e) {
    if (Q->front == Q->rear) {
        return ERROR;
    }
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAX_QUEUE_SIZE;  //队头指针加 1
    return OK;
}

/**
 * 初始条件：队列 Q 存在且非空
 * 操作结果：从队头到队尾，依次对遍历队列中每个元素
 * @param Q
 * @param vi
 */
void QueueTraverse(SqQueue Q, void(*vi)(QElemType)) {
    int i = Q.front;
    while (i != Q.rear) {
        vi(Q.base[i]);  //遍历
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf("\n");
}

/**
 * 遍历函数
 * @param e
 */
void vi(QElemType e) {
    printf("%d ",e);
}

/**
 * 主函数，测试程序
 * @return
 */
int main() {
    SqQueue q;
    QElemType e;

    InitQueue(&q);
    printf("队列的长度：%d\n", QueueLength(q));
    printf("队列是否为空：%d\n", QueueEmpty(q));
    EnQueue(&q, 3);
    EnQueue(&q, 4);
    EnQueue(&q, 5);
    EnQueue(&q, 6);
    QueueTraverse(q, vi);
    printf("队列的长度：%d\n", QueueLength(q));
    printf("队列是否为空：%d\n", QueueEmpty(q));
    GetHead(q, &e);
    printf("队列的头元素：%d\n", e);
    DeQueue(&q, &e);
    QueueTraverse(q, vi);
    ClearQueue(&q);
    printf("队列的长度：%d\n", QueueLength(q));
    printf("队列是否为空：%d\n", QueueEmpty(q));

    DestroyQueue(&q);
}

