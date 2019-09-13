//
//文件夹: 02 Linear_List/02 SequenceList
//文件名: SequenceList
//内　容：顺序表相关操作列表
//Author Huangcp
//Date 2019/9/9 下午 11:50
//Version 1.0
//


#ifndef DATA_STRUCTURE_SEQUENCELIST_H
#define DATA_STRUCTURE_SEQUENCELIST_H

#include <stdio.h>
#include <stdlib.h>                        //提供malloc、realloc、free、exit原型
#include "../../01 Introduction/Status.h"        //**01 Introduction**//

/* 宏定义 */
#define LIST_INIT_SIZE 100                //顺序表存储空间的初始分配量
#define LISTINCREMENT  10                //顺序表存储空间的分配增量

/* 顺序表类型定义 */
/*lelemtype*/
#ifndef LELEMTYPE_SQ
#define LELEMTYPE_SQ
typedef int LElemType_Sq;
#endif

typedef struct {
    LElemType_Sq *elem;                    //存储空间基址（指向第一个结点的指针）
    int length;                            //当前顺序表长度
    int listsize;                        //当前分配的存储容量
} SqList;                                //顺序表0号单元正常使用


/* 顺序表函数列表 */
/**
(01)算法2.3：初始化空顺序表L。
**/
Status InitList_Sq(SqList *L);

/**
(02)清空顺序表L。 
**/
void ClearList_Sq(SqList *L);

/**
(03)销毁顺序表L。 
**/
void DestroyList_Sq(SqList *L);

/**
(04)判断顺序表L是否为空。 
**/
Status ListEmpty_Sq(SqList L);

/**
(05)返回顺序表L中元素个数。 
**/
int ListLength_Sq(SqList L);

/**
(06)用e接收顺序表L中第i个元素。 
**/
Status GetElem_Sq(SqList L, int i, LElemType_Sq *e);

/**
(07)算法2.6：返回顺序表L中首个与e满足Compare关系的元素位序。
**/
int LocateElem_Sq(SqList L, LElemType_Sq e, Status(Compare)(LElemType_Sq, LElemType_Sq));

/**
(08)用pre_e接收cur_e的前驱。      
**/
Status PriorElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *pre_e);

/**
(09)用next_e接收cur_e的后继。     
**/
Status NextElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *next_e);

/**
(10)算法2.4：在顺序表L的第i个位置上插入e。
**/
Status ListInsert_Sq(SqList *L, int i, LElemType_Sq e);

/**
(11)算法2.5：删除顺序表L上第i个位置的元素，并用e返回。
**/
Status ListDelete_Sq(SqList *L, int i, LElemType_Sq *e);

/**
(12)用visit函数访问顺序表L。
**/
Status ListTraverse_Sq(SqList L, void (Visit)(LElemType_Sq));


/**
算法2.3  
**/
Status InitList_Sq(SqList *L) {
    (*L).elem = (LElemType_Sq *) malloc(LIST_INIT_SIZE * sizeof(LElemType_Sq));
    if (!(*L).elem)
        exit(OVERFLOW);                //分配内存失败

    (*L).length = 0;                    //初始化顺序表长度为0
    (*L).listsize = LIST_INIT_SIZE;        //顺序表初始内存分配量

    return OK;                            //初始化成功	 
}

void ClearList_Sq(SqList *L) {
    (*L).length = 0;
}

void DestroyList_Sq(SqList *L) {
    free((*L).elem);

    (*L).elem = NULL;                    //释放内存后置空指针 
    (*L).length = 0;
    (*L).listsize = 0;
}

Status ListEmpty_Sq(SqList L) {
    return L.length == 0 ? TRUE : FALSE;
}

int ListLength_Sq(SqList L) {
    return L.length;
}

Status GetElem_Sq(SqList L, int i, LElemType_Sq *e) {
    if (i < 1 || i > L.length)
        return ERROR;                    //i值不合法
    else
        *e = L.elem[i - 1];

    return OK;
}

/**
算法2.6  
**/
int LocateElem_Sq(SqList L, LElemType_Sq e, Status(Compare)(LElemType_Sq, LElemType_Sq)) {
    int i = 1;                            //i的初值为第一个元素的位序

    while (i <= L.length && !Compare(e, L.elem[i - 1]))
        ++i;

    if (i <= L.length)
        return i;
    else
        return 0;
}

Status PriorElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *pre_e) {
    int i = 1;

    if (L.elem[0] != cur_e)                //第一个结点无前驱 
    {
        while (i < L.length && L.elem[i] != cur_e)
            ++i;

        if (i < L.length) {
            *pre_e = L.elem[i - 1];
            return OK;
        }
    }

    return ERROR;
}

Status NextElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *next_e) {
    int i = 0;

    while (i < L.length && L.elem[i] != cur_e)
        ++i;

    if (i < L.length - 1)                    //最后一个结点无后继 
    {
        *next_e = L.elem[i + 1];
        return OK;
    }

    return ERROR;
}

/**
算法2.4  
**/
Status ListInsert_Sq(SqList *L, int i, LElemType_Sq e) {
    LElemType_Sq *newbase;
    LElemType_Sq *p, *q;

    if (i < 1 || i > (*L).length + 1)
        return ERROR;                    //i值不合法

    if ((*L).length >= (*L).listsize)    //若存储空间已满，需开辟新空间 
    {
        newbase = (LElemType_Sq *) realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(LElemType_Sq));
        if (!newbase)
            exit(OVERFLOW);

        (*L).elem = newbase;
        (*L).listsize += LISTINCREMENT;
    }

    q = &(*L).elem[i - 1];                //q为插入位置 

    for (p = &(*L).elem[(*L).length - 1]; p >= q; --p)
        *(p + 1) = *p;                    //插入位置及之后的元素右移 

    *q = e;                                //插入e 
    (*L).length++;                        //表长增1

    return OK;
}

/**
算法2.5  
**/
Status ListDelete_Sq(SqList *L, int i, LElemType_Sq *e) {
    LElemType_Sq *p, *q;

    if (i < 1 || i > (*L).length)
        return ERROR;                    //i值不合法

    p = &(*L).elem[i - 1];                //p为被删除元素的位置 
    *e = *p;
    q = (*L).elem + (*L).length - 1;        //表尾元素位置 

    for (++p; p <= q; ++p)
        *(p - 1) = *p;                    //被删元素之后的元素左移 

    (*L).length--;                        //表长减1

    return OK;
}

Status ListTraverse_Sq(SqList L, void(Visit)(LElemType_Sq)) {
    int i;

    for (i = 0; i < L.length; i++)
        Visit(L.elem[i]);

    return OK;
}

#endif //DATA_STRUCTURE_SEQUENCELIST_H
