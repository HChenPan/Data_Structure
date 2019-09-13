//
//文件夹: 02 Linear_List/04 SinglyLinkedList
//文件名: SinglyLinkedList
//内　容：单链表相关操作列表
//Author Huangcp
//Date 2019/9/10 上午 12:08
//Version 1.0
//

#ifndef DATA_STRUCTURE_SINGLYLINKEDLIST_H
#define DATA_STRUCTURE_SINGLYLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>                        //提供malloc、realloc、free、exit原型
#include "../../01 Introduction/Scanf.h"        //**▲01 绪论**//
#include "../../01 Introduction/Status.h"        //**▲01 绪论**//

/* 单链表类型定义 */
#ifndef DATA_STRUCTURE_BANKQUEUING_H            /*后续的模拟银行排队算法中，此类型需要重新定义*/
typedef int LElemType_L;

/* 单链表结构体 */
typedef struct LNode {
    LElemType_L data;
    struct LNode *next;
} LNode;
typedef LNode *LinkList;        //指向单链表结点的指针

#endif //DATA_STRUCTURE_BANKQUEUING_H


/* 单链表（带头结点）函数列表 */
/**
(01)初始化单链表L。 
**/
Status InitList_L(LinkList *L);

/**
(02)置空单链表L，头结点保留。 
**/
Status ClearList_L(LinkList L);

/**
(03)销毁单链表L，连同通结点一起销毁。 
**/
void DestroyList_L(LinkList *L);

/**
(04)判断单链表L是否为空。     
**/
Status ListEmpty_L(LinkList L);

/**
(05)返回单链表L元素个数 
**/
int ListLength_L(LinkList L);

/**
(06)算法2.8：用e接收单链表L中第i个元素
**/
Status GetElem_L(LinkList L, int i, LElemType_L *e);

/**
(07)返回单链表L中第一个与e满足Compare关系的元素位序。 
**/
int LocateElem_L(LinkList L, LElemType_L e, Status(Compare)(LElemType_L, LElemType_L));

/**
(08)用pre_e接收cur_e的前驱。
**/
Status PriorElem_L(LinkList L, LElemType_L cur_e, LElemType_L *pre_e);

/**
(09)用next_e接收cur_e的后继。 
**/
Status NextElem_L(LinkList L, LElemType_L cur_e, LElemType_L *next_e);

/**
(10)算法2.9：在单链表L第i个位置之前插入e。
**/
Status ListInsert_L(LinkList L, int i, LElemType_L e);

/**
(11)算法2.10：删除单链表L第i个位置的值，并用e接收。 
**/
Status ListDelete_L(LinkList L, int i, LElemType_L *e);

/**
(12)用Visit函数访问单链表L。
**/
Status ListTraverse_L(LinkList L, void(Visit)(LElemType_L));

/**
(13)算法2.11：头插法建立单链表L(逆序输入)。 
**/
Status CreateList_HL(FILE *fp, LinkList *L, int n);

/**
(14)尾插法建立单链表L(顺序输入)。 
**/
Status CreateList_TL(FILE *fp, LinkList *L, int n);


Status InitList_L(LinkList *L) {
    (*L) = (LinkList) malloc(sizeof(LNode));
    if (!(*L))
        exit(OVERFLOW);
    (*L)->next = NULL;

    return OK;
}

Status ClearList_L(LinkList L)            //保留头结点 
{
    LinkList pre, p;

    if (!L)
        return ERROR;

    pre = L->next;

    while (pre) {
        p = pre->next;
        free(pre);
        pre = p;
    }

    L->next = NULL;

    return OK;
}

void DestroyList_L(LinkList *L)            //销毁所有结点 
{
    LinkList p = *L;

    while (p) {
        p = (*L)->next;
        free(*L);
        (*L) = p;
    }
}

Status ListEmpty_L(LinkList L) {
    if (L != NULL && L->next == NULL)        //链表存在且只有头结点 
        return TRUE;
    else
        return FALSE;
}

int ListLength_L(LinkList L) {
    LinkList p;
    int i;

    if (L) {
        i = 0;
        p = L->next;
        while (p) {
            i++;
            p = p->next;
        }
    }

    return i;
}

/**
 算法2.8 
**/
Status GetElem_L(LinkList L, int i, LElemType_L *e) {
    int j;
    LinkList p = L->next;

    j = 1;
    p = L->next;

    while (p && j < i)                        //p不为空且还未到达i处
    {
        j++;
        p = p->next;
    }

    if (!p || j > i)                        //第i个元素不存在 
        return ERROR;

    *e = p->data;

    return OK;
}

int LocateElem_L(LinkList L, LElemType_L e, Status(Compare)(LElemType_L, LElemType_L)) {
    int i;
    LinkList p;

    i = -1;                                //L不存在时返回-1 

    if (L) {
        i = 0;
        p = L->next;

        while (p) {
            i++;

            if (!Compare(e, p->data)) {
                p = p->next;
                if (p == NULL)        //失配时已经是最后一个结点 
                    i++;
            } else
                break;
        }
    }

    return i;
}

/* 银行排队算法中，此处两个函数不能直接使用，原因是结构不能直接比较 */
#ifndef DATA_STRUCTURE_BANKQUEUING_H

Status PriorElem_L(LinkList L, LElemType_L cur_e, LElemType_L *pre_e) {
    LinkList p, suc;

    if (L) {
        p = L->next;

        if (p->data != cur_e)                //第一个结点无前驱 
        {
            while (p->next)                //若p结点有后继 
            {
                suc = p->next;            //suc指向p的后继
                if (suc->data == cur_e) {
                    *pre_e = p->data;
                    return OK;
                }
                p = suc;
            }
        }
    }

    return ERROR;
}

Status NextElem_L(LinkList L, LElemType_L cur_e, LElemType_L *next_e) {
    LinkList p, suc;

    if (L) {
        p = L->next;

        while (p && p->next) {
            suc = p->next;

            if (suc && p->data == cur_e) {
                *next_e = suc->data;
                return OK;
            }

            if (suc)
                p = suc;
            else
                break;
        }
    }

    return ERROR;
}

#endif

/**
 算法2.9 
**/
Status ListInsert_L(LinkList L, int i, LElemType_L e) {
    LinkList p, s;
    int j;

    p = L;
    j = 0;

    while (p && j < i - 1)                    //寻找第i-1个结点 
    {
        p = p->next;
        ++j;
    }

    if (!p || j > i - 1)
        return ERROR;

    s = (LinkList) malloc(sizeof(LNode));
    if (!s)
        exit(OVERFLOW);
    s->data = e;
    s->next = p->next;
    p->next = s;

    return OK;
}

/**
 算法2.10  
**/
Status ListDelete_L(LinkList L, int i, LElemType_L *e) {
    LinkList pre, p;
    int j;

    pre = L;
    j = 1;

    while (pre->next && j < i)            //寻找第i个结点，并令pre指向其前驱 
    {
        pre = pre->next;
        ++j;
    }

    if (!pre->next || j > i)            //删除位置不合理
        return ERROR;

    p = pre->next;
    pre->next = p->next;
    *e = p->data;
    free(p);

    return OK;
}

Status ListTraverse_L(LinkList L, void(Visit)(LElemType_L)) {
    LinkList p;

    if (!L)
        return ERROR;
    else
        p = L->next;

    while (p) {
        Visit(p->data);
        p = p->next;
    }

    return OK;
}

/**
 算法2.11  
**/
Status CreateList_HL(FILE *fp, LinkList *L, int n) {
    int i;
    LinkList p;
    LElemType_L tmp;

    *L = (LinkList) malloc(sizeof(LNode));
    if (!(*L))
        exit(OVERFLOW);
    (*L)->next = NULL;                            //建立头结点 

    for (i = 1; i <= n; ++i) {
        if (Scanf(fp, "%d", &tmp) == 1) {
            p = (LinkList) malloc(sizeof(LNode));
            if (!p)
                exit(OVERFLOW);
            p->data = tmp;                        //录入数据 
            p->next = (*L)->next;
            (*L)->next = p;
        } else
            return ERROR;
    }

    return OK;
}

Status CreateList_TL(FILE *fp, LinkList *L, int n) {
    int i;
    LinkList p, q;
    LElemType_L tmp;

    *L = (LinkList) malloc(sizeof(LNode));
    if (!(*L))
        exit(OVERFLOW);
    (*L)->next = NULL;

    for (i = 1, q = *L; i <= n; ++i) {
        if (Scanf(fp, "%d", &tmp) == 1) {
            p = (LinkList) malloc(sizeof(LNode));
            if (!p)
                exit(OVERFLOW);
            p->data = tmp;                        //录入数据 
            q->next = p;
            q = q->next;
        } else
            return ERROR;
    }

    q->next = NULL;

    return OK;
}

#endif //DATA_STRUCTURE_SINGLYLINKEDLIST_H
