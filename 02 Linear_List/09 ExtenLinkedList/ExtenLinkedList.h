//
//文件夹: 02 Linear_List/09 ExtenLinkedList
//文件名: ExtenLinkedList
//内　容：扩展的单链表相关操作列表
//Author Huangcp
//Date 2019/9/10 上午 12:59
//Version 1.0
//

#ifndef DATA_STRUCTURE_EXTENLINKEDLIST_H
#define DATA_STRUCTURE_EXTENLINKEDLIST_H

#include <stdlib.h>                        //提供malloc、realloc、free、exit原型
#include "../../01 Introduction/Status.h"        //**▲01 绪论**//
#include "../../01 Introduction/Scanf.h"        //**▲01 绪论**//

/*	扩展的单链表类型定义	*/
#ifndef DATA_STRUCTURE_POLYNOMIAL_H                    //在多项式操作中，此类型需重新定义
typedef int LElemType_E;
#endif
typedef struct ELNode                    //结点类型
{
    LElemType_E data;
    struct ELNode *next;
} ELNode;
typedef ELNode *Link;                    //指向结构的指针
typedef ELNode *PositionPtr;
typedef struct                            //链表类型
{
    Link head, tail;                    //分别指向线性链表中的头结点和尾结点
    int len;                            //指示线性链表中数据元素的个数
} ELinkList;

/*	扩展的单链表函数列表 */
/*━━━━━━━━━━━━┓
┃(01)分配由p指向e的结点。┃
┗━━━━━━━━━━━━*/
Status MakeNode_E(Link *p, LElemType_E e);

/*━━━━━━━━━━━┓
┃(02)释放p指向的结点。 ┃
┗━━━━━━━━━━━*/
void FreeNode_E(Link *p);

/*━━━━━━━━━━━━━━┓
┃(03)初始化一个空的线性链表。┃
┗━━━━━━━━━━━━━━*/
Status InitList_E(ELinkList *L);

/*━━━━━━━━━━━━┓
┃(04)重置线性链表L为空。 ┃
┗━━━━━━━━━━━━*/
void ClearList_E(ELinkList *L);

/*━━━━━━━━━━┓
┃(05)销毁线性链表L。 ┃
┗━━━━━━━━━━*/
void DestroyList_E(ELinkList *L);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(06)h指向L中的一个结点，将h当做头结点，将s插入到“第一个结点”之前。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void InsFirst_E(ELinkList *L, Link h, Link s);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(07)h指向L中的一个结点，将h当做头结点，删除“第一个结点”，并用q接收。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
Status DelFirst_E(ELinkList *L, Link h, Link *q);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(08)将s所指的一串结点链接在L的最后一个结点之后，并改变L的尾指针。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void Append_E(ELinkList *L, Link s);

/*━━━━━━━━━━━━━━━━━━━━┓
┃(09)删除L的尾结点并用q接收，改变尾指针。┃
┗━━━━━━━━━━━━━━━━━━━━*/
Status Remove_E(ELinkList *L, Link *q);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(10)将s所指结点插入p所指结点之前,并将p指向新插入的结点。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void InsBefore_E(ELinkList *L, Link *p, Link s);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(11)将s所指结点插入p所指结点之后,并将p指向新插入的结点。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void InsAfter_E(ELinkList *L, Link *p, Link s);

/*━━━━━━━━━━━━━━━┓
┃(12)用e更新p指向的结点中的值。┃
┗━━━━━━━━━━━━━━━*/
void SetCurElem_E(Link p, LElemType_E e);

/*━━━━━━━━━━━┓
┃(13)返回p结点中的值。 ┃
┗━━━━━━━━━━━*/
LElemType_E GetCurElem_E(Link p);

/*━━━━━┓
┃(14)判空。┃
┗━━━━━*/
Status ListEmpty_E(ELinkList L);

/*━━━━━┓
┃(15)求长。┃
┗━━━━━*/
int ListLength_E(ELinkList L);

/*━━━━━━━━━━━━━━━━━┓
┃(16)以指针形式返回L头结点的位置。 ┃
┗━━━━━━━━━━━━━━━━━*/
PositionPtr GetHead_E(ELinkList L);

/*━━━━━━━━━━━━━━━━━━━━┓
┃(17)以指针形式返回L最后一个结点的位置。 ┃
┗━━━━━━━━━━━━━━━━━━━━*/
PositionPtr GetLast_E(ELinkList L);

/*━━━━━━━━━━━━━━┓
┃(18)返回p指向的结点的前驱。 ┃
┗━━━━━━━━━━━━━━*/
PositionPtr PriorPos_E(ELinkList L, Link p);

/*━━━━━━━━━━━━━━┓
┃(19)返回p指向的结点的后继。 ┃
┗━━━━━━━━━━━━━━*/
PositionPtr NextPos_E(Link p);

/*━━━━━━━━━━━━━━━━━━━━┓
┃(20)将*p指向L中第i个结点,i=0时为头结点。┃
┗━━━━━━━━━━━━━━━━━━━━*/
Status LocatePos_E(ELinkList L, int i, Link *p);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(21)返回L中指向第一个与e满足Compare关系的元素指针。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━*/
PositionPtr LocateElem_E(ELinkList L, LElemType_E e, Status(Compare)(LElemType_E, LElemType_E));

/*━━━━━┓
┃(22)访问。┃
┗━━━━━*/
Status ListTraverse_E(ELinkList L, void(Visit)(LElemType_E));

/*━━━━━━━━━━━━━━━━━━━┓
┃(23)算法2.20：在L第i个位置之前插入e。 ┃
┗━━━━━━━━━━━━━━━━━━━*/
Status ListInsert_L_E(ELinkList *L, int i, LElemType_E e);

/*━━━━━━━━━━━━━━━━━━┓
┃(24)删除L第i个位置的值，并用e接收。 ┃
┗━━━━━━━━━━━━━━━━━━*/
Status ListDelete_L_E(ELinkList *L, int i, LElemType_E *e);


Status MakeNode_E(Link *p, LElemType_E e) {
    *p = (Link) malloc(sizeof(ELNode));        //申请空间 	
    if (!(*p))
        exit(OVERFLOW);

    (*p)->data = e;
    (*p)->next = NULL;

    return OK;
}

void FreeNode_E(Link *p)                    //释放空间 
{
    free(*p);
    *p = NULL;
}

Status InitList_E(ELinkList *L) {
    Link p;

    p = (Link) malloc(sizeof(ELNode));
    if (!p)
        exit(OVERFLOW);
    p->next = NULL;

    (*L).head = (*L).tail = p;
    (*L).len = 0;

    return OK;
}

void ClearList_E(ELinkList *L) {
    Link p, q;

    p = (*L).head->next;

    while (p) {
        q = p->next;
        free(p);
        p = q;
    }

    (*L).head->next = NULL;
    (*L).tail = (*L).head;
    (*L).len = 0;
}

void DestroyList_E(ELinkList *L) {
    ClearList_E(L);

    free((*L).head);

    (*L).head = (*L).tail = NULL;
}


void InsFirst_E(ELinkList *L, Link h, Link s) {
    s->next = h->next;
    h->next = s;

    if (h == (*L).tail)                    //若h为尾结点 
        (*L).tail = h->next;

    (*L).len++;
}

Status DelFirst_E(ELinkList *L, Link h, Link *q) {
    *q = h->next;

    if (*q)                                //链表非空 
    {
        h->next = (*q)->next;
        if (!h->next)                    //h后只有一个结点 
            (*L).tail = h;

        (*L).len--;                        //并不释放被删结点所占空间 

        return OK;
    }

    return ERROR;
}

void Append_E(ELinkList *L, Link s) {
    int count = 0;

    (*L).tail->next = s;

    while (s)                            //考虑s为空的情况 
    {
        (*L).tail = s;
        s = s->next;
        count++;
    }

    (*L).len += count;
}

Status Remove_E(ELinkList *L, Link *q) {
    Link p;

    if (!(*L).len) {
        *q = NULL;
        return ERROR;
    }

    *q = (*L).tail;

    p = (*L).head;                        //寻找尾结点的前驱 
    while (p->next != (*L).tail)
        p = p->next;
    p->next = NULL;
    (*L).tail = p;

    (*L).len--;

    return OK;
}

void InsBefore(ELinkList *L, Link *p, Link s) {
    Link q;

    q = PriorPos_E(*L, *p);                //寻找p的前驱 
    if (!q)                                //若p无前驱（只有一个结点） 
        q = (*L).head;

    s->next = *p;
    q->next = s;
    *p = s;

    (*L).len++;                            //修改len，需用到*L 			
}

void InsAfter(ELinkList *L, Link *p, Link s) {
    if (*p == (*L).tail)
        (*L).tail = s;

    s->next = (*p)->next;
    (*p)->next = s;
    *p = s;

    (*L).len++;
}

void SetCurElem_E(Link p, LElemType_E e) {
    p->data = e;
}

LElemType_E GetCurElem_E(Link p) {
    return p->data;
}

Status ListEmpty_E(ELinkList L) {
    if (L.len)
        return FALSE;
    else
        return TRUE;
}

int ListLength_E(ELinkList L) {
    return L.len;
}

PositionPtr GetHead_E(ELinkList L) {
    return L.head;
}

PositionPtr GetLast_E(ELinkList L) {
    return L.tail;
}

PositionPtr PriorPos_E(ELinkList L, Link p) {
    Link q;

    q = L.head->next;
    if (q == p)                            //首结点无前驱 
        return NULL;
    else {
        while (q->next != p)                //寻找p的前驱 
            q = q->next;

        return q;
    }
}

PositionPtr NextPos_E(Link p) {
    return p->next;
}

Status LocatePos_E(ELinkList L, int i, Link *p) {
    int count = 0;
    *p = L.head;                        //i=0时返回头指针 

    if (i < 0 || i > L.len)
        return ERROR;

    while (count < i) {
        count++;
        *p = (*p)->next;
    }

    return OK;
}

PositionPtr LocateElem_E(ELinkList L, LElemType_E e, Status(Compare)(LElemType_E, LElemType_E)) {
    Link p = L.head->next;

    while (p && !(Compare(e, p->data)))
        p = p->next;

    return p;
}

Status ListTraverse_E(ELinkList L, void(Visit)(LElemType_E)) {
    Link p;
    int j;

    p = L.head->next;

    for (j = 1; j <= L.len; j++) {
        Visit(p->data);
        p = p->next;
    }

    return OK;
}

/*═════╗
║ 算法2.20 ║ 
╚═════*/
/* 算法2.9的改写 */
Status ListInsert_L_E(ELinkList *L, int i, LElemType_E e) {
    Link h, s;

    if (!LocatePos_E(*L, i - 1, &h))        //定位第i-1个结点位置 
        return ERROR;                    //i值不合法

    if (!MakeNode_E(&s, e))                //创建结点 
        return ERROR;                    //内存申请失败

    InsFirst_E(L, h, s);

    return OK;
}

/* 算法2.10的改写，调用了本文档中定义的函数 */
Status ListDelete_L_E(ELinkList *L, int i, LElemType_E *e) {
    Link p, q;

    if (i < 1 || i > (*L).len)
        return ERROR;

    LocatePos_E(*L, i - 1, &p);
    DelFirst_E(L, p, &q);

    *e = q->data;
    free(q);
    q = NULL;

    return OK;
}

#endif //DATA_STRUCTURE_EXTENLINKEDLIST_H
