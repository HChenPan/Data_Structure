//
//文件夹: 03 Stack_Queue/08 CylSeqQueue
//文件名: CylSeqQueue
//内　容：循环队列相关操作列表
//Author Huangcp
//Date 2019/9/10 下午 11:22
//Version 1.0
//

#ifndef DATA_STRUCTURE_CYLSEQQUEUE_H
#define DATA_STRUCTURE_CYLSEQQUEUE_H

#include <stdio.h>
#include <stdlib.h>						//提供malloc、realloc、free、exit原型
#include "../../01 Introduction/Status.h"		//**▲01 绪论**//

/* 宏定义 */
#define MAXQSIZE 1000					//最大队列长度

/* 循环队列类型定义 */
typedef int QElemType_CSq;
typedef struct							//队列的顺序存储结构
{
    QElemType_CSq *base;				//初始化的动态分配存储空间
    int front;							//头指针，若队列不空，指向队头元素
    int rear;							//尾指针，若队列不空，指向队列尾元素的下一个位置
}CSqQueue;

/* 循环队列函数列表 */
/*━━━━━━━━━━━┓
┃(01)初始化循环队列Q。 ┃
┗━━━━━━━━━━━*/
Status InitQueue_CSq(CSqQueue *Q);

/*━━━━━━┓
┃(02)置空Q。 ┃
┗━━━━━━*/
void ClearQueue_CSq(CSqQueue *Q);

/*━━━━━━┓
┃(03)销毁Q。 ┃
┗━━━━━━*/
void DestroyQueue_CSq(CSqQueue *Q);

/*━━━━━━━━━━┓
┃(04)判断Q是否为空。 ┃
┗━━━━━━━━━━*/
Status QueueEmpty_CSq(CSqQueue Q);

/*━━━━━━━━━━┓
┃(05)返回Q元素个数。 ┃
┗━━━━━━━━━━*/
int QueueLength_CSq(CSqQueue Q);

/*━━━━━━━━━━━┓
┃(06)用e获取队头元素。 ┃
┗━━━━━━━━━━━*/
Status GetHead_CSq(CSqQueue Q, QElemType_CSq *e);

/*━━━━━━━━┓
┃(07)元素e入队。 ┃
┗━━━━━━━━*/
Status EnQueue_CSq(CSqQueue *Q, QElemType_CSq e);

/*━━━━━━━━┓
┃(08)元素e出队。 ┃
┗━━━━━━━━*/
Status DeQueue_CSq(CSqQueue *Q, QElemType_CSq *e);

/*━━━━━━━┓
┃(09)访问队列。┃
┗━━━━━━━*/
void QueueTraverse_CSq(CSqQueue Q, void(Visit)(QElemType_CSq));


Status InitQueue_CSq(CSqQueue *Q)
{
    (*Q).base = (QElemType_CSq *)malloc(MAXQSIZE*sizeof(QElemType_CSq));
    if(!(*Q).base)
        exit(OVERFLOW);

    (*Q).front = (*Q).rear = 0;

    return OK;
}

void ClearQueue_CSq(CSqQueue *Q)
{
    (*Q).front = (*Q).rear = 0;
}

void DestroyQueue_CSq(CSqQueue *Q)
{
    if((*Q).base)
        free((*Q).base);

    (*Q).base = NULL;
    (*Q).front = (*Q).rear = 0;
}

Status QueueEmpty_CSq(CSqQueue Q)
{
    if(Q.front==Q.rear) 						//队列空的标志
        return TRUE;
    else
        return FALSE;
}

int QueueLength_CSq(CSqQueue Q)
{
    return (Q.rear-Q.front+MAXQSIZE) % MAXQSIZE;//队列长度
}

Status GetHead_CSq(CSqQueue Q, QElemType_CSq *e)
{
    if(Q.front==Q.rear)							//队列空
        return ERROR;

    *e = Q.base[Q.front];

    return OK;
}

Status EnQueue_CSq(CSqQueue *Q, QElemType_CSq e)
{
    if(((*Q).rear+1)%MAXQSIZE == (*Q).front)	//队列满
        return ERROR;

    (*Q).base[(*Q).rear] = e;
    (*Q).rear = ((*Q).rear+1)%MAXQSIZE;

    return OK;
}

Status DeQueue_CSq(CSqQueue *Q, QElemType_CSq *e)
{
    if((*Q).front==(*Q).rear)					//队列空
        return ERROR;

    *e = (*Q).base[(*Q).front];
    (*Q).front = ((*Q).front+1)%MAXQSIZE;

    return OK;
}

void QueueTraverse_CSq(CSqQueue Q, void(Visit)(QElemType_CSq))
{
    int i = Q.front;

    while(i!=Q.rear)
    {
        Visit(Q.base[i]);
        i = (i+1)%MAXQSIZE;
    }
}

#endif //DATA_STRUCTURE_CYLSEQQUEUE_H
