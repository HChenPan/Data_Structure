//
//文件夹: 03 Stack_Queue/07 LinkQueue
//文件名: LinkQueue
//内　容：链队相关操作列表
//Author Huangcp
//Date 2019/9/10 下午 11:19
//Version 1.0
//

#ifndef DATA_STRUCTURE_LINKQUEUE_H
#define DATA_STRUCTURE_LINKQUEUE_H

#include <stdio.h>
#include <stdlib.h>                        //提供malloc、realloc、free、exit原型
#include "../../01 Introduction/Status.h"        //**▲01 绪论**//

/* 链队类型定义 */
/* 在模拟银行排队、二叉树三叉链表存储的算法中，QElemType_L需重新定义*/
#if !defined  DATA_STRUCTURE_BANKQUEUING_H     && !defined DATA_STRUCTURE_TRI_BINARYTREE_H

typedef int QElemType_L;

#endif

typedef struct QNode {
    QElemType_L data;
    struct QNode *next;
} QNode;
typedef QNode *QueuePtr;
typedef struct {
    QueuePtr front;                    //头指针
    QueuePtr rear;                    //尾指针
} LinkQueue;                            //队列的链式存储表示

/* 链栈函数列表 */
/*━━━━━━━━━┓
┃(01)初始化链队Q。 ┃
┗━━━━━━━━━*/
Status InitQueue_L(LinkQueue *Q);

/*━━━━━━┓
┃(02)置空Q。 ┃
┗━━━━━━*/
void ClearQueue_L(LinkQueue *Q);

/*━━━━━━┓
┃(03)销毁Q。 ┃
┗━━━━━━*/
void DestroyQueue_L(LinkQueue *Q);

/*━━━━━━━━━━┓
┃(04)判断Q是否为空。 ┃
┗━━━━━━━━━━*/
Status QueueEmpty_L(LinkQueue Q);

/*━━━━━━━━━━┓
┃(05)返回Q元素个数。 ┃
┗━━━━━━━━━━*/
int QueueLength_L(LinkQueue Q);

/*━━━━━━━━━━━┓
┃(06)用e获取队头元素。 ┃
┗━━━━━━━━━━━*/
Status GetHead_L(LinkQueue Q, QElemType_L *e);

/*━━━━━━━━┓
┃(07)元素e入队。 ┃
┗━━━━━━━━*/
Status EnQueue_L(LinkQueue *Q, QElemType_L e);

/*━━━━━━━━┓
┃(08)元素e出队。 ┃
┗━━━━━━━━*/
Status DeQueue_L(LinkQueue *Q, QElemType_L *e);

/*━━━━━━━┓
┃(09)访问队列。┃
┗━━━━━━━*/
void QueueTraverse_L(LinkQueue Q, void(Visit)(QElemType_L));


Status InitQueue_L(LinkQueue *Q) {
    (*Q).front = (*Q).rear = (QueuePtr) malloc(sizeof(QNode));
    if (!(*Q).front)
        exit(OVERFLOW);

    (*Q).front->next = NULL;

    return OK;
}

void ClearQueue_L(LinkQueue *Q) {
    (*Q).rear = (*Q).front->next;

    while ((*Q).rear) {
        (*Q).front->next = (*Q).rear->next;
        free((*Q).rear);
        (*Q).rear = (*Q).front->next;
    }

    (*Q).rear = (*Q).front;
}

void DestroyQueue_L(LinkQueue *Q) {
    while ((*Q).front) {
        (*Q).rear = (*Q).front->next;
        free((*Q).front);
        (*Q).front = (*Q).rear;
    }
}

Status QueueEmpty_L(LinkQueue Q) {
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

int QueueLength_L(LinkQueue Q) {
    int count = 0;
    QueuePtr p = Q.front;

    while (p != Q.rear) {
        count++;
        p = p->next;
    }

    return count;
}

Status GetHead_L(LinkQueue Q, QElemType_L *e) {
    QueuePtr p;

    if (Q.front == Q.rear)
        return ERROR;

    p = Q.front->next;
    *e = p->data;

    return OK;
}

Status EnQueue_L(LinkQueue *Q, QElemType_L e) {
    QueuePtr p;

    p = (QueuePtr) malloc(sizeof(QNode));
    if (!p)
        exit(OVERFLOW);

    p->data = e;
    p->next = NULL;

    (*Q).rear->next = p;
    (*Q).rear = p;

    return OK;
}

Status DeQueue_L(LinkQueue *Q, QElemType_L *e) {
    QueuePtr p;

    if ((*Q).front == (*Q).rear)
        return ERROR;

    p = (*Q).front->next;
    *e = p->data;

    (*Q).front->next = p->next;
    if ((*Q).rear == p)
        (*Q).rear = (*Q).front;

    free(p);

    return OK;
}

void QueueTraverse_L(LinkQueue Q, void (Visit)(QElemType_L)) {
    QueuePtr p;

    p = Q.front->next;

    while (p) {
        Visit(p->data);
        p = p->next;
    }
}

#endif //DATA_STRUCTURE_LINKQUEUE_H
