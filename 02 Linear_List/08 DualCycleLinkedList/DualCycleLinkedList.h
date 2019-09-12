//
//文件夹: 02 Linear_List/08 DualCycleLinkedList
//文件名: DualCycleLinkedList
//内　容：双向循环链表相关操作列表
//Author Huangcp
//Date 2019/9/10 上午 12:55
//Version 1.0
//

#ifndef DATA_STRUCTURE_DUALCYCLELINKEDLIST_H
#define DATA_STRUCTURE_DUALCYCLELINKEDLIST_H

#include <stdlib.h>                        //提供malloc、realloc、free、exit原型
#include "../../01 Introduction/Status.h"        //**▲01 绪论**//

/* 双循环链表类型定义 */
typedef int LElemType_DC;
typedef struct DuLNode {
    LElemType_DC data;
    struct DuLNode *prior;
    struct DuLNode *next;
} DuLNode;
typedef DuLNode *DuLinkList;            //指向双循环链表结构的指针

/*	双循环链表函数列表	*/

/*━━━━━━━━━━┓
┃(01)初始化双链表L。 ┃
┗━━━━━━━━━━*/
Status InitList_DuL(DuLinkList *L);

/*━━━━━━┓
┃(02)置空L。 ┃
┗━━━━━━*/
Status ClearList_DuL(DuLinkList L);

/*━━━━━━┓
┃(03)销毁L。 ┃
┗━━━━━━*/
void DestroyList_DuL(DuLinkList *L);

/*━━━━━━━━━━┓
┃(04)判断L是否为空。 ┃
┗━━━━━━━━━━*/
Status ListEmpty_DuL(DuLinkList L);

/*━━━━━━━━━━┓
┃(05)返回L元素个数。 ┃
┗━━━━━━━━━━*/
int ListLength_DuL(DuLinkList L);

/*━━━━━━━━━━━━━━━━━┓
┃(06)用e接收L中第i个结点的元素值。 ┃
┗━━━━━━━━━━━━━━━━━*/
Status GetElem_DuL(DuLinkList L, int i, LElemType_DC *e);

/*━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(07)返回L中第一个与e满足Compare关系的元素位序。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━*/
int LocateElem_DuL(DuLinkList L, LElemType_DC e, Status (Compare)(LElemType_DC, LElemType_DC));

/*━━━━━━━━━━━━━━┓
┃(08)用pre_e接收cur_e的前驱。┃
┗━━━━━━━━━━━━━━*/
Status PriorElem_DuL(DuLinkList L, LElemType_DC cur_e, LElemType_DC *pre_e);

/*━━━━━━━━━━━━━━━┓
┃(09)用next_e接收cur_e的后继。 ┃
┗━━━━━━━━━━━━━━━*/
Status NextElem_DuL(DuLinkList L, LElemType_DC cur_e, LElemType_DC *next_e);

/*━━━━━━━━━━━━━━━━┓
┃(10)返回L中指向第i个结点的指针。┃
┗━━━━━━━━━━━━━━━━*/
DuLinkList GetElemPtr_DuL(DuLinkList L, int i);

/*━━━━━━━━━━━━━━━━━━━┓
┃(11)算法2.18：在L第i个位置之前插入e。 ┃
┗━━━━━━━━━━━━━━━━━━━*/
Status ListInsert_DuL(DuLinkList L, int i, LElemType_DC e);

/*━━━━━━━━━━━━━━━━━━━━━━━┓
┃(12)算法2.19：删除L第i个位置的值，并用e接收。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━*/
Status ListDelete_DuL(DuLinkList L, int i, LElemType_DC *e);

/*━━━━━━━━━━━┓
┃(13)用Visit函数访问L。┃
┗━━━━━━━━━━━*/
void ListTraverse_DuL(DuLinkList L, void(Visit)(LElemType_DC));


Status InitList_DuL(DuLinkList *L) {
    *L = (DuLinkList) malloc(sizeof(DuLNode));
    if (!(*L))
        exit(OVERFLOW);

    (*L)->next = (*L)->prior = *L;

    return OK;
}

Status ClearList_DuL(DuLinkList L) {
    DuLinkList p, q;

    p = L->next;

    while (p != L) {
        q = p->next;
        free(p);
        p = q;
    }

    L->next = L->prior = L;

    return OK;
}

void DestroyList_DuL(DuLinkList *L) {
    ClearList_DuL(*L);

    free(*L);

    *L = NULL;
}

Status ListEmpty_DuL(DuLinkList L) {
    if (L && L->next == L && L->prior == L)
        return TRUE;
    else
        return FALSE;
}

int ListLength_DuL(DuLinkList L) {
    DuLinkList p;
    int count = 0;

    if (L) {
        count = 0;
        p = L;                    //p指向头结点

        while (p->next != L)        //p没到表头
        {
            count++;
            p = p->next;
        }
    }

    return count;
}

Status GetElem_DuL(DuLinkList L, int i, LElemType_DC *e) {
    DuLinkList p;
    int count;

    if (L) {
        count = 1;
        p = L->next;

        while (p != L && count < i) {
            count++;
            p = p->next;
        }

        if (p != L) {
            *e = p->data;
            return OK;
        }
    }

    return ERROR;
}

int LocateElem_DuL(DuLinkList L, LElemType_DC e, Status(Compare)(LElemType_DC, LElemType_DC)) {
    DuLinkList p;
    int count;

    if (L) {
        count = 1;
        p = L->next;

        while (p != L && !Compare(e, p->data)) {
            count++;
            p = p->next;
        }

        if (p != L)
            return count;
    }

    return 0;
}

Status PriorElem_DuL(DuLinkList L, LElemType_DC cur_e, LElemType_DC *pre_e) {
    DuLinkList p;

    if (L) {
        p = L->next;

        while (p != L && p->data != cur_e)
            p = p->next;

        if (p != L && p->prior != L)                //p不为首结点
        {
            *pre_e = p->prior->data;
            return OK;
        }
    }

    return ERROR;
}

Status NextElem_DuL(DuLinkList L, LElemType_DC cur_e, LElemType_DC *next_e) {
    DuLinkList p;

    if (L) {
        p = L->next;

        while (p != L && p->data != cur_e)
            p = p->next;

        if (p != L && p->next != L) {
            *next_e = p->next->data;
            return OK;
        }
    }


    return ERROR;
}

DuLinkList GetElemPtr_DuL(DuLinkList L, int i) {
    int count;
    DuLinkList p;

    if (L && i > 0) {
        count = 1;
        p = L->next;

        while (p != L && count < i) {
            count++;
            p = p->next;
        }

        if (p != L)
            return p;
    }

    return NULL;
}

/*═════╗
║ 算法2.18 ║
╚═════*/
/* 与课本双链表插入算法略有不同，根源在于GetElemP_DuL不同 */
Status ListInsert_DuL(DuLinkList L, int i, LElemType_DC e) {
    DuLinkList p, s;

    if (i < 1 || i > ListLength_DuL(L) + 1)    //先对i做出限制
        return ERROR;

    p = GetElemPtr_DuL(L, i);            //确定第i个结点指针
    if (!p)                                //此处若p=NULL，说明i = ListLength_DuL(L)+1
        p = L;                            //令p指向头指针

    s = (DuLinkList) malloc(sizeof(DuLNode));
    if (!s)
        exit(OVERFLOW);
    s->data = e;

    s->prior = p->prior;
    p->prior->next = s;
    s->next = p;
    p->prior = s;

    return OK;
}

/*═════╗
║ 算法2.19 ║
╚═════*/
Status ListDelete_DuL(DuLinkList L, int i, LElemType_DC *e) {
    DuLinkList p;

    if (!(p = GetElemPtr_DuL(L, i)))        //i值不合法
        return ERROR;

    *e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;

    free(p);

    return OK;
}

void ListTraverse_DuL(DuLinkList L, void(Visit)(LElemType_DC)) {
    DuLinkList p;

    p = L->next;                    //p指向头结点，正向访问链表

    while (p != L) {
        Visit(p->data);
        p = p->next;
    }
}

#endif //DATA_STRUCTURE_DUALCYCLELINKEDLIST_H
